#ifndef ILARGIA_SENSORSYSTEM_H
#define ILARGIA_SENSORSYSTEM_H


#include <anax/anax.hpp>
#include <anax/FilterOptions.hpp>
#include <anax/detail/BaseSystem.hpp>
#include <anax/detail/ClassTypeId.hpp>
#include <isdl/Components/SensorComponents.h>
#include <isdl/Components/StateComponent.h>


namespace Ilargia {

    template <class Sensor>
    class SensorSystem : public anax::detail::BaseSystem{

        SensorSystem()
                : anax::detail::BaseSystem(anax::detail::MakeFilter<anax::Requires<Sensor, StateComponent>,
                anax::Excludes<>>()) {}

        template<class T>
        anax::detail::TypeId SystemTypeId()
        {
            return anax::detail::ClassTypeId<anax::detail::BaseSystem>::GetTypeId<T>();
        }

        void processEntity(anax::Entity, float deltaTime) {

        }

    public:

        void update(float deltaTime) {
            for(anax::Entity entity : getEntities()) {
                processEntity(entity, deltaTime);
            }
        }

    };

}


#endif //ILARGIA_SENSORSYSTEM_H
