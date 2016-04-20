#ifndef ILARGIA_ControllerSYSTEM_H
#define ILARGIA_ControllerSYSTEM_H

#include "core/logicbrick/LogicBrick.h"
#include "core/logicbrick/Components.h"

namespace Ilargia {

    class IControllerSystem {
    protected:
        virtual bool validateSensors(std::unordered_map<std::string, std::unique_ptr<Sensor>> &sensors) = 0;

    };

    class ControllerSystem : public IControllerSystem {
    protected:
        virtual bool validateSensors(std::unordered_map<std::string, std::unique_ptr<Sensor>> &sensors) override;

        template<typename ControllerType>
        void process(ControllerType &controller);

    };

    class ConditionalControllerSystem : public ControllerSystem {
    protected:
        void process(ConditionalController &ccontroller);

    };

    class ScriptControllerSystem : public ControllerSystem {
    protected:
        void process(ScriptController &controller) {
            controller.script(controller);
        }
    };
}

#endif //ILARGIA_SENSORSYSTEM_H
