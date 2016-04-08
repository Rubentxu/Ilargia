#ifndef ILARGIA_SENSORSYSTEM_H
#define ILARGIA_SENSORSYSTEM_H

#include "core/logicbrick/State.h"
#include "core/logicbrick/sensor/Sensor.h"

namespace Ilargia {


    class SensorSystem {
    protected:
        void process(Sensor &sensor, State state, float deltaTime) {

            bool doDispatch = false, freqDispatch = false;
            if (state.isChanged) {
                sensor.firstExec = true;
                sensor.positive = false;
                sensor.firstTap = TapMode::TAP_IN;
                /*  if (sensor instanceof DelaySensor) {
                      ((DelaySensor) sensor).time = 0;
                  }*/

            }

            bool processPulseState = false;
            bool lastPulse = sensor.positive;
            sensor.positive = query(sensor, deltaTime);
            if (sensor.invert) sensor.positive = !sensor.positive;

            if (sensor.firstExec || ((sensor.tick += deltaTime) > sensor.frequency) || sensor.pulse == Pulse::PM_IDLE
                || (lastPulse != sensor.positive)) {
                processPulseState = true;
                if (sensor.tick > sensor.frequency) freqDispatch = true;
                sensor.tick = 0;

            }

            if (processPulseState) {
                if (sensor.pulse == Pulse::PM_IDLE) {
                    doDispatch = lastPulse != sensor.positive;

                } else {
                    if (sensor.pulse == Pulse::PM_TRUE) {
                        doDispatch = (lastPulse != sensor.positive) || sensor.positive;
                    }
                    if (sensor.pulse == Pulse::PM_FALSE) {
                        doDispatch = (lastPulse != sensor.positive) || !sensor.positive;
                    }
                }
            }


            if (sensor.tap) {
                processPulseState = sensor.positive;

                doDispatch = false;
                sensor.pulseState = BrickMode::BM_OFF;

                if (sensor.firstTap == TapMode::TAP_IN && processPulseState) {
                    doDispatch = true;
                    sensor.positive = true;
                    sensor.pulseState = BrickMode::BM_ON;
                    sensor.firstTap = TapMode::TAP_OUT;
                    sensor.lastTap = TapMode::TAP_IN;
                } else if (sensor.lastTap == TapMode::TAP_IN) {
                    sensor.positive = false;
                    doDispatch = true;
                    if (sensor.pulse == Pulse::PM_TRUE) sensor.firstTap = TapMode::TAP_IN;
                    sensor.lastTap = TapMode::TAP_OUT;
                } else {
                    sensor.positive = false;
                    if (!processPulseState)
                        sensor.firstTap = TapMode::TAP_IN;
                }
            } else sensor.pulseState = isPositive(sensor) ? BrickMode::BM_ON : BrickMode::BM_OFF;

            if (sensor.firstExec) {
                sensor.firstExec = false;
            }

            // Dispatch results
            if (doDispatch) {
                sensor.pulseState = BrickMode::BM_ON;
            }

            if (!doDispatch && sensor.pulse == Pulse::PM_TRUE && sensor.positive && freqDispatch) {
                sensor.pulseState = BrickMode::BM_ON;
            } else if (!doDispatch) {
                sensor.pulseState = BrickMode::BM_OFF;
            }

        }


        bool isPositive(Sensor sensor) {
            bool result = sensor.positive;
            if (sensor.invert) {
                if (!(sensor.tap && !(sensor.pulse == Pulse::PM_TRUE)))
                    result = !result;
            }
            return result;

        }

        virtual bool query(Sensor sensor, float deltaTime) = 0;
    };
}

#endif //ILARGIA_SENSORSYSTEM_H
