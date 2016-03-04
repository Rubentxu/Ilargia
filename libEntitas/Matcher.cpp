#include "Matcher.h"
#include "IMatcher.h"

using namespace Entitas;

namespace Entitas {

	MatcherException::MatcherException(const std::shared_ptr<IMatcher> &matcher) : Exception(std::string(_TEXT("matcher.indices.Length must be 1 but was ")) + std::to_string(matcher->indices->Length)) {
	}
}
