#ifndef ILARGIA_SENSORSYSTEM_H
#define ILARGIA_SENSORSYSTEM_H

#include <anax/anax.hpp>

template <typename SensorComponent, typename Sensor>
class SensorSystem : public anax::System<anax::Requires<SensorComponent>>{

    void processEntity(anax::Entity, float deltaTime) {

    }

public:

    void update(float deltaTime) {
        for(anax::Entity entity : getEntities()) {
            processEntity(entity, deltaTime);
        }
    }

};


#endif //ILARGIA_SENSORSYSTEM_H
