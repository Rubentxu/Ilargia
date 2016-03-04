#include "TriggerOnEvent.h"
#include "IMatcher.h"
#include "GroupEventType.h"

namespace Entitas {

	TriggerOnEvent::TriggerOnEvent(const std::shared_ptr<IMatcher> &trigger, const std::shared_ptr<GroupEventType> &eventType) {
		this->trigger = trigger;
		this->eventType = eventType;
	}
}
