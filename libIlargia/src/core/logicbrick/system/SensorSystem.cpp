
#include "core/logicbrick/system/SensorSystem.h"

namespace Ilargia {

    void SensorSystem::process(Sensor &sensor, bool isChanged, float deltaTime) {

        bool doDispatch = false, freqDispatch = false;
        if (isChanged) {
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

        if (sensor.firstExec || ((sensor.tick += deltaTime) >= sensor.frequency) || sensor.pulse == Pulse::PM_IDLE
            || (lastPulse != sensor.positive)) {
            processPulseState = true;
            if (sensor.tick > sensor.frequency) freqDispatch = true;
            sensor.tick = 0;

        }

        if (processPulseState) {
            doDispatch = lastPulse != sensor.positive;
            switch (sensor.pulse) {
                case Pulse::PM_TRUE:
                    doDispatch = doDispatch || sensor.positive;
                    break ;
                case Pulse::PM_FALSE:
                    doDispatch = doDispatch || !sensor.positive;
                    break ;
                case Pulse::PM_BOTH:
                    doDispatch = true;
                    break ;
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
                if (sensor.pulse == Pulse::PM_TRUE || sensor.pulse == Pulse::PM_BOTH) sensor.firstTap = TapMode::TAP_IN;
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
        } else if ((sensor.pulse == Pulse::PM_TRUE || sensor.pulse == Pulse::PM_BOTH) && sensor.positive && freqDispatch) {
            sensor.pulseState = BrickMode::BM_ON;
        } else {
            sensor.pulseState = BrickMode::BM_OFF;
        }

    }

    bool SensorSystem::isPositive(Sensor sensor) {
        bool result = sensor.positive;
        if (sensor.invert) {
            if (!(sensor.tap && !(sensor.pulse == Pulse::PM_TRUE)))
                result = !result;
        }
        return result;

    }

    bool DelaySensorSystem::query(Sensor &sensor, float deltaTime) {
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
        dsensor.positive = isActive;
        return isActive;

    }

    bool KeyboardSensorSystem::query(Sensor &sensor, float deltaTime) {
        KeyboardSensor& ksensor = static_cast<KeyboardSensor&>(sensor);
        bool isActive = false;
        if (ksensor.keyCode != -1) {
            isActive = keysCodeSignal[ksensor.keyCode];

        }
        return isActive;

    }

}

