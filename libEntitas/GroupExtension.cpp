
#include "GroupObserver.h"
#include "Group.h"

namespace Entitas {

	std::shared_ptr<GroupObserver> GroupExtension::CreateObserver(const std::shared_ptr<Group> &group, const std::shared_ptr<GroupEventType> &eventType = GroupEventType::OnEntityAdded) {
		return std::make_shared<GroupObserver>(group, eventType);
	}
}
