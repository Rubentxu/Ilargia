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

        bool isPositive(Sensor sensor) {
            bool result = sensor.positive;
            if (sensor.invert) {
                if (!(sensor.tap && !(sensor.pulse == Pulse::PM_TRUE)))
                    result = !result;
            }
            return result;

        }


        virtual bool query(Sensor &sensor, float deltaTime) = 0;

    };

    class AlwaysSensorSystem : public SensorSystem {

        bool query(Sensor &sensor, float deltaTime) override {
            return true;
        }
    };

    class DelaySensorSystem : public SensorSystem {

        bool query(Sensor &sensor, float deltaTime) override {
            DelaySensor& dsensor = static_cast<DelaySensor&>(sensor);
            bool isActive = false;
            if (dsensor.time != -1) dsensor.time += deltaTime;

            if (dsensor.time >= dsensor.delay) {
                if (dsensor.positive && dsensor.time >= (dsensor.delay + dsensor.duration)) {
                    if (dsensor.repeat) {
                        dsensor.time = 0;
                    } else {
                        dsensor.time = -1;
                    }
                } else {
                    isActive = true;
                }

            }
            return isActive;

        }
    };

    class KeyboardSensorSystem : public SensorSystem {

        bool query(Sensor &sensor, float deltaTime) override {
            KeyboardSensor& ksensor = static_cast<KeyboardSensor&>(sensor);
            bool isActive = false;
            if (ksensor.keyCode != -1) {
                isActive = ksensor.keysCodeSignal[ksensor.keyCode];

            }
            return isActive;

        }
    };

    template<typename Body, typename Contact>
    class NearSensorSystem : public SensorSystem {

        bool query(Sensor &sensor, float deltaTime) override {
            NearSensor<Body,Contact>& nsensor = static_cast<NearSensor<Body,Contact>&>(sensor);
            bool isActive = false;

            if (nsensor.distanceContactList.size() > 0) {
                isActive = true;
                if (!nsensor.initContact) nsensor.initContact = true;

            } else if (nsensor.initContact && nsensor.resetDistanceContactList.size > 0) {
                isActive = true;

            } else if (nsensor.initContact) {
                nsensor.initContact = false;

            }
            return isActive;

        }

    };

    template<typename Contact>
    class RadarSensorSystem : public SensorSystem {

        bool query(Sensor &sensor, float deltaTime) override ;
    };
}

#endif //ILARGIA_SENSORSYSTEM_H
