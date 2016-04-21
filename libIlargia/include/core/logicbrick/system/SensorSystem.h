#ifndef ILARGIA_SENSORSYSTEM_H
#define ILARGIA_SENSORSYSTEM_H

#include "core/logicbrick/Components.h"
#include "core/logicbrick/LogicBrick.h"

namespace Ilargia {

    class ISensorSystem {
    protected:
        virtual void process(Sensor &sensor, bool isChanged, float deltaTime) = 0;

    };


    class SensorSystem : public ISensorSystem {
    protected:
        virtual void process(Sensor &sensor, bool isChanged, float deltaTime) override;

        bool isPositive(Sensor sensor);

    public:
        virtual bool query(Sensor &sensor, float deltaTime) = 0;

    };

    class AlwaysSensorSystem : public SensorSystem {
    public:
        bool query(Sensor &sensor, float deltaTime) override {
            return true;
        }
    };

    class DelaySensorSystem : public SensorSystem {
    public:
        bool query(Sensor &sensor, float deltaTime) override;
    };

    class KeyboardSensorSystem : public SensorSystem {
    public:
        // Signal Values
        std::vector<bool> keysCodeSignal;

        KeyboardSensorSystem() {
            keysCodeSignal= std::vector<bool>{128};
            std::fill (keysCodeSignal.begin(),keysCodeSignal.end(),false);
        }

        bool query(Sensor &sensor, float deltaTime) override;
    };

    template<typename Body, typename Contact>
    class NearSensorSystem : public SensorSystem {
    public:
        bool query(Sensor &sensor, float deltaTime) override {
            NearSensor<Body,Contact>& nsensor = static_cast<NearSensor<Body,Contact>&>(sensor);
            bool isActive = false;

            if (nsensor.distanceContactList.size() > 0) {
                isActive = true;
                if (!nsensor.initContact) nsensor.initContact = true;

            } else if (nsensor.initContact && nsensor.resetDistanceContactList.size() > 0) {
                isActive = true;

            } else if (nsensor.initContact) {
                nsensor.initContact = false;

            }
            return isActive;

        }

    };

    template<typename Contact>
    class RadarSensorSystem : public SensorSystem {
    public:
        bool query(Sensor &sensor, float deltaTime) override ;
    };
}

#endif //ILARGIA_SENSORSYSTEM_H
