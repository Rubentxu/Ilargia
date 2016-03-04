#ifndef COLLECTIONEXTENSION
#define COLLECTIONEXTENSION

#include <stdexcept>
#include <memory>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
class Entity;


namespace Entitas {
	class CollectionExtension final : public std::enable_shared_from_this<CollectionExtension> {
	public:
		//static std::shared_ptr<Entity> SingleEntity(const std::shared_ptr<ICollection<Entity> > &collection);
	};
}



#endif	//#ifndef COLLECTIONEXTENSION
