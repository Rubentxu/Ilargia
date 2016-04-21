#include "core/logicbrick/system/ControllerSystem.h"

namespace Ilargia {

    bool ControllerSystem::validateSensors(std::unordered_map<std::string, std::unique_ptr<Sensor>> &sensors) {
        bool pulseState = false;
        for (auto &pair : sensors) {
            if (pair.second->pulseState == BrickMode::BM_ON) {
                pulseState = true;
            } else {
                pulseState = false;
                break;
            }
        }
        return pulseState;
    }

    void ConditionalControllerSystem::process(ConditionalController &ccontroller) {

        if (ccontroller.actuators.empty() || ccontroller.sensors.empty()) {
            return;
        }

        bool doDispatch = false;
        bool seed = true, last = false, pos = false;


        switch (ccontroller.op) {
            case Op::OP_NOR:
                ccontroller.isInverter = true;
            case Op::OP_OR:
                for (auto &pair : ccontroller.sensors) {
                    pos = pair.second->positive;
                    if (pos)
                        doDispatch = true;

                    if (doDispatch)
                        break;
                }

                if (ccontroller.isInverter)
                    doDispatch = !doDispatch;

                break;
            case Op::OP_XNOR:
                ccontroller.isInverter = true;
            case Op::OP_XOR:
                for (auto &pair : ccontroller.sensors) {
                    seed = pair.second->positive;

                    if (seed && last) {
                        doDispatch = false;
                        break;
                    } else if (seed) doDispatch = true;

                    if (!last && seed)
                        last = true;

                    if (ccontroller.op == Op::OP_XNOR && seed)
                        ccontroller.isInverter = true;
                }
                if (ccontroller.isInverter)
                    doDispatch = !doDispatch;

                break;
            case Op::OP_NAND:
                ccontroller.isInverter = true;
            case Op::OP_AND:
                for (auto &pair : ccontroller.sensors) {
                    pos = pair.second->positive;
                    if (seed) {
                        seed = false;
                        doDispatch = pos;
                    } else
                        doDispatch = doDispatch && pos;

                }
                if (ccontroller.isInverter) {
                    doDispatch = !doDispatch;
                }

                break;
        }
        if (doDispatch) {
            ccontroller.pulseState = Ilargia::BrickMode::BM_ON;
        } else {
            ccontroller.pulseState = Ilargia::BrickMode::BM_OFF;
        }
        for (auto &pair : ccontroller.actuators) {
            pair.second->isActive = doDispatch;
        }

    }
}
