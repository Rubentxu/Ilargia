#include "Entity.h"

namespace Entitas {

	EntityAlreadyHasComponentException::EntityAlreadyHasComponentException(const std::string &message, int index) : Exception(message + std::string(_TEXT("\nEntity already has a component at index ")) + std::to_string(index)) {
	}

	EntityDoesNotHaveComponentException::EntityDoesNotHaveComponentException(const std::string &message, int index) : Exception(message + std::string(_TEXT("\nEntity does not have a component at index ")) + std::to_string(index)) {
	}

	EntityIsNotEnabledException::EntityIsNotEnabledException(const std::string &message) : Exception(message + std::string(_TEXT("\nEntity is not enabled!"))) {
	}

const std::shared_ptr<EntityEqualityComparer> EntityEqualityComparer::comparer = std::make_shared<EntityEqualityComparer>();

	bool EntityEqualityComparer::Equals(const std::shared_ptr<Entity> &x, const std::shared_ptr<Entity> &y) {
		return x == y;
	}

	int EntityEqualityComparer::GetHashCode(const std::shared_ptr<Entity> &obj) {
		return obj->_creationIndex;
	}

	EntityIsAlreadyRetainedByOwnerException::EntityIsAlreadyRetainedByOwnerException(const std::shared_ptr<void> &owner) : Exception(std::string(_TEXT("Entity is already retained by owner: ")) + owner) {
	}

	EntityIsNotRetainedByOwnerException::EntityIsNotRetainedByOwnerException(const std::shared_ptr<void> &owner) : Exception(std::string(_TEXT("Entity is not retained by owner: ")) + owner) {
	}

const std::string EntityExtension::COMPONENT_SUFFIX = _TEXT("Component");

	std::string EntityExtension::RemoveComponentSuffix(const std::shared_ptr<Type> &type) {
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to this .NET String method:
		return type->Name->EndsWith(COMPONENT_SUFFIX) ? type->Name->substr(0, type->Name->Length - COMPONENT_SUFFIX.length()) : type->Name;
	}
}
