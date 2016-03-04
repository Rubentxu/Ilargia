#include "Pool.h"
#include "Entitas.Entity.h"


namespace Entitas {

	PoolDoesNotContainEntityException::PoolDoesNotContainEntityException(const std::shared_ptr<Entity> &entity, const std::string &message) : Exception(message + std::string(_TEXT("\nPool does not contain entity ")) + entity) {
	}

	EntityIsNotDestroyedException::EntityIsNotDestroyedException(const std::string &message) : Exception(message + std::string(_TEXT("\nEntity is not destroyed yet!"))) {
	}
}
