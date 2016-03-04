#ifndef TRIGGERONEVENT
#define TRIGGERONEVENT

#include <memory>

class IMatcher;
class GroupEventType;

namespace Entitas {
	class TriggerOnEvent {
	public:
		std::shared_ptr<IMatcher> trigger;
		std::shared_ptr<GroupEventType> eventType;

		TriggerOnEvent(const std::shared_ptr<IMatcher> &trigger, const std::shared_ptr<GroupEventType> &eventType);
	};
}



#endif	//#ifndef TRIGGERONEVENT
