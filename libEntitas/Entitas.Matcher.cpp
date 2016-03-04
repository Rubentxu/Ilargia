#include "Entitas.Matcher.h"
#include "Matcher.h"
#include "Entity.h"
#include "IMatcher.h"

using namespace Entitas;

namespace Entitas {

	const std::vector<int> &Matcher::Getindices() const {
		if(_indices.empty())
			_indices = mergeIndices();
		return _indices;
	}

	const std::vector<int> &Matcher::GetallOfIndices() const {
		return _allOfIndices;
	}

	const std::vector<int> &Matcher::GetanyOfIndices() const {
		return _anyOfIndices;
	}

	const std::vector<int> &Matcher::GetnoneOfIndices() const {
		return _noneOfIndices;
	}

	Matcher::Matcher() {
	}

	std::shared_ptr<IAnyOfMatcher> Matcher::IAllOfMatcher_AnyOf(std::vector<int> &indices) {
		_anyOfIndices = distinctIndices(Getindices());
		_indices.clear();
		return shared_from_this();
	}

	std::shared_ptr<IAnyOfMatcher> Matcher::IAllOfMatcher_AnyOf(std::vector<IMatcher> &matchers) {
		return (std::static_pointer_cast<IAllOfMatcher>(shared_from_this()))->AnyOf(mergeIndices(matchers));
	}

	std::shared_ptr<INoneOfMatcher> Matcher::NoneOf(std::vector<int> &indices) {
		_noneOfIndices = distinctIndices(Getindices());
		_indices.clear();
		return shared_from_this();
	}

	std::shared_ptr<INoneOfMatcher> Matcher::NoneOf(std::vector<IMatcher> &matchers) {
		return NoneOf(mergeIndices(matchers));
	}

	bool Matcher::Matches(const std::shared_ptr<Entity> &entity) {
		auto matchesAllOf = _allOfIndices.empty() || entity->HasComponents(_allOfIndices);
		auto matchesAnyOf = _anyOfIndices.empty() || entity->HasAnyComponent(_anyOfIndices);
		auto matchesNoneOf = _noneOfIndices.empty() || !entity->HasAnyComponent(_noneOfIndices);
		return matchesAllOf && matchesAnyOf && matchesNoneOf;
	}

	std::vector<int> Matcher::mergeIndices() {
		auto totalIndices = (_allOfIndices.size() > 0 ? _allOfIndices.size() : 0) + (_anyOfIndices.size() > 0 ? _anyOfIndices.size() : 0) + (_noneOfIndices.size() > 0 ? _noneOfIndices.size() : 0);

		auto indicesList = std::vector<int>(totalIndices);
		if(_allOfIndices.size() > 0)
			indicesList.insert(indicesList.end(), _allOfIndices.begin(), _allOfIndices.end());
		if(_anyOfIndices.size() > 0)
			indicesList.insert(indicesList.end(), _anyOfIndices.begin(), _anyOfIndices.end());
		if(_noneOfIndices.size() > 0)
			indicesList.insert(indicesList.end(), _noneOfIndices.begin(), _noneOfIndices.end());

		return distinctIndices(indicesList);
	}

	std::vector<int> Matcher::mergeIndices(std::vector<IMatcher> &matchers) {
		auto indices = std::vector<int>(matchers.size());
		for(int i = 0, matchersLength = matchers.size(); i < matchersLength; i++) {
			auto matcher = matchers[i];
			if(matcher->indices->Length != 1)
				throw MatcherException(matcher);
			indices[i] = matcher->indices[0];
		}

		return indices;
	}

	std::vector<std::string> Matcher::getComponentNames(std::vector<IMatcher> &matchers) {
		for(int i = 0, matchersLength = matchers.size(); i < matchersLength; i++) {
			auto matcher = std::dynamic_pointer_cast<Matcher>(matchers[i]);
			if(matcher != nullptr && matcher->componentNames.size() > 0)
				return matcher->componentNames;
		}

		return nullptr;
	}

	void Matcher::setComponentNames(const std::shared_ptr<Matcher> &matcher, std::vector<IMatcher> &matchers) {
		auto componentNames = getComponentNames(matchers);
		if(componentNames.size() > 0)
			matcher->componentNames = componentNames;
	}

	std::vector<int> Matcher::distinctIndices(const std::shared_ptr<IEnumerable<int> > &indices) {
		auto indicesSet = std::unordered_set<int>(indices);
		auto uniqueIndices = std::vector<int>(indicesSet.size());
		indicesSet.CopyTo(uniqueIndices);
		std::sort(uniqueIndices.begin(), uniqueIndices.end());
		return uniqueIndices;
	}

	bool Matcher::Equals(const std::shared_ptr<void> &obj) {
		if(obj == nullptr || obj->GetType() != GetType() || obj->GetHashCode() != GetHashCode())
			return false;

		auto matcher = std::static_pointer_cast<Matcher>(obj);
		if(!equalIndices(matcher->GetallOfIndices(), _allOfIndices))
			return false;
		if(!equalIndices(matcher->GetanyOfIndices(), _anyOfIndices))
			return false;
		if(!equalIndices(matcher->GetnoneOfIndices(), _noneOfIndices))
			return false;

		return true;
	}

	bool Matcher::equalIndices(std::vector<int> &i1, std::vector<int> &i2) {
		if((i1.empty()) != (i2.empty()))
			return false;
		if(i1.empty())
			return true;
		if(i1.size() != i2.size())
			return false;

		for(int i = 0, indicesLength = i1.size(); i < indicesLength; i++) {
			if(i1[i] != i2[i])
				return false;
		}

		return true;
	}

	int Matcher::GetHashCode() {
		if(!_isHashCached) {
			auto hash = GetType()->GetHashCode();
			hash = applyHash(hash, _allOfIndices, 3, 53);
			hash = applyHash(hash, _anyOfIndices, 307, 367);
			hash = applyHash(hash, _noneOfIndices, 647, 683);
			_hash = hash;
			_isHashCached = true;
		}

		return _hash;
	}

	int Matcher::applyHash(int hash, std::vector<int> &indices, int i1, int i2) {
		if(indices.size() > 0) {
			for(int i = 0, indicesLength = indices.size(); i < indicesLength; i++)
				hash ^= indices[i] * i1;
			hash ^= indices.size() * i2;
		}

		return hash;
	}

	std::shared_ptr<IAllOfMatcher> Matcher::AllOf(std::vector<int> &indices) {
		auto matcher = std::make_shared<Matcher>();
		matcher->_allOfIndices = distinctIndices(Getindices());
		return matcher;
	}

	std::shared_ptr<IAllOfMatcher> Matcher::AllOf(std::vector<IMatcher> &matchers) {
		auto allOfMatcher = std::static_pointer_cast<Matcher>(Matcher::AllOf(mergeIndices(matchers)));
		setComponentNames(allOfMatcher, matchers);
		return allOfMatcher;
	}

	std::shared_ptr<IAnyOfMatcher> Matcher::AnyOf(std::vector<int> &indices) {
		auto matcher = std::make_shared<Matcher>();
		matcher->_anyOfIndices = distinctIndices(Getindices());
		return matcher;
	}

	std::shared_ptr<IAnyOfMatcher> Matcher::AnyOf(std::vector<IMatcher> &matchers) {
		auto anyOfMatcher = std::static_pointer_cast<Matcher>(Matcher::AnyOf(mergeIndices(matchers)));
		setComponentNames(anyOfMatcher, matchers);
		return anyOfMatcher;
	}

	std::string Matcher::ToString() {
		if(_toStringCache == _TEXT("")) {
			auto sb = std::make_shared<StringBuilder>();
			if(_allOfIndices.size() > 0)
				appendIndices(sb, _TEXT("AllOf"), _allOfIndices, componentNames);
			if(_anyOfIndices.size() > 0) {
				if(_allOfIndices.size() > 0)
					sb->Append(_TEXT("."));
				appendIndices(sb, _TEXT("AnyOf"), _anyOfIndices, componentNames);
			}
			if(_noneOfIndices.size() > 0)
				appendIndices(sb, _TEXT(".NoneOf"), _noneOfIndices, componentNames);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			_toStringCache = sb->ToString();
		}

		return _toStringCache;
	}

	void Matcher::appendIndices(const std::shared_ptr<StringBuilder> &sb, const std::string &prefix, std::vector<int> &indexArray, std::vector<std::string> &componentNames) {
		constexpr std::string SEPARATOR = _TEXT(", ");
		sb->Append(prefix);
		sb->Append(_TEXT("("));
		auto lastSeparator = indexArray.size() - 1;
		for(int i = 0, indicesLength = indexArray.size(); i < indicesLength; i++) {
			auto index = indexArray[i];
			if(componentNames.empty())
				sb->Append(index);
			else
				sb->Append(componentNames[index]);

			if(i < lastSeparator)
				sb->Append(SEPARATOR);
		}
		sb->Append(_TEXT(")"));
	}
}
