#include "IMatcherExtension.h"
#include "TriggerOnEvent.h"
#include "IMatcher.h"

namespace Entitas {

	std::shared_ptr<TriggerOnEvent> IMatcherExtension::OnEntityAdded(const std::shared_ptr<IMatcher> &matcher) {
		return std::make_shared<TriggerOnEvent>(matcher, GroupEventType::OnEntityAdded);
	}

	std::shared_ptr<TriggerOnEvent> IMatcherExtension::OnEntityRemoved(const std::shared_ptr<IMatcher> &matcher) {
		return std::make_shared<TriggerOnEvent>(matcher, GroupEventType::OnEntityRemoved);
	}

	std::shared_ptr<TriggerOnEvent> IMatcherExtension::OnEntityAddedOrRemoved(const std::shared_ptr<IMatcher> &matcher) {
		return std::make_shared<TriggerOnEvent>(matcher, GroupEventType::OnEntityAddedOrRemoved);
	}
}
