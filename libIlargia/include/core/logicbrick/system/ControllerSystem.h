#ifndef PROJECT_ControllerSYSTEM_H
#define PROJECT_ControllerSYSTEM_H

#include "core/logicbrick/controller/Controller.h"

namespace Ilargia {


    class ControllerSystem {
    protected:
        void process(Controller &controller) {
            if (controller.actuators.empty() || controller.sensors.empty()) {
                return;
            }

            boolean doDispatch = false;
            boolean seed = true, last = false, pos = false;


            switch (controller.op) {
                case OP_NOR:
                    controller.isInverter = true;
                case OP_OR:
                    for (Sensor sens : controller.sensors.values()) {
                        pos = sens.positive;
                        if (pos)
                            doDispatch = true;

                        if (doDispatch)
                            break;
                    }

                    if (controller.isInverter)
                        doDispatch = !doDispatch;

                    break;
                case OP_XNOR:
                    controller.isInverter = true;
                case OP_XOR:
                    for (Sensor sens : controller.sensors.values()) {
                        seed = sens.positive;

                        if (seed && last) {
                            doDispatch = false;
                            break;
                        } else if (seed) doDispatch = true;

                        if (!last && seed)
                            last = true;

                        if (controller.op == Op.OP_XNOR && seed)
                            controller.isInverter = true;
                    }
                    if (controller.isInverter)
                        doDispatch = !doDispatch;

                    break;
                case OP_NAND:
                    controller.isInverter = true;
                case OP_AND:
                    for (Sensor sens : controller.sensors.values()) {
                        pos = sens.positive;
                        if (seed) {
                            seed = false;
                            doDispatch = pos;
                        } else
                            doDispatch = doDispatch && pos;

                    }
                    if (controller.isInverter) {
                        doDispatch = !doDispatch;
                    }

                    break;
            }
            if (doDispatch) {
                controller.pulseState = BrickMode.BM_ON;
            } else {
                controller.pulseState = BrickMode.BM_OFF;
            }

        }

    };
}

#endif //PROJECT_SENSORSYSTEM_H
