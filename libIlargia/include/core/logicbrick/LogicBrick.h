#ifndef ILARGIA_LOGICBRICK_H
#define ILARGIA_LOGICBRICK_H

#include <string>
#include <unordered_map>
#include <set>
#include <queue>
#include "mathfu/vector.h"
#include "core/logicbrick/LogicBrick.h"

namespace Ilargia {

    enum class BrickMode {
        BM_IDLE, BM_ON, BM_OFF
    };
    enum class Pulse {
        PM_IDLE, PM_TRUE, PM_FALSE, PM_BOTH
    };
    enum class TapMode {
        TAP_OUT, TAP_IN
    };

    struct Component {
    };

    struct LogicBrick {
        std::string name;
        int state = -1;
        BrickMode pulseState = BrickMode::BM_IDLE;

    };

    struct Sensor : LogicBrick {
        // Config Values
        float frequency = 0;
        bool invert = false;
        bool tap = false;
        Pulse pulse = Pulse::PM_IDLE; // Valorar si quitar. Duplicidad de funcionalidad con positive

        // Values
        float tick = 0;
        bool positive = false;
        bool firstExec = true;
        bool initialized = false;
        TapMode firstTap = TapMode::TAP_IN;
        TapMode lastTap = TapMode::TAP_OUT;

    };

    struct AlwaysSensor : Sensor {
        AlwaysSensor() {
            Sensor::pulseState = BrickMode::BM_ON;
            Sensor::pulse = Pulse::PM_BOTH;
        }
    };

    enum class MouseEvent {
        MOUSEMOTION = 0x400, MOUSEBUTTONDOWN, MOUSEBUTTONUP, MOUSEWHEEL
    };

    template<typename Entity>
    struct MouseSensor : Sensor {
        MouseEvent mouseEvent = MouseEvent::MOUSEMOTION;
        Entity target;

        MouseEvent mouseEventSignal;
        mathfu::Vector<float, 2> positionSignal;
        int amountScrollSignal;

    };

    struct DelaySensor : Sensor {
        // Config Values
        float delay;
        float duration;
        bool repeat;

        // Signal
        float time = 0.0;

        DelaySensor(float _delay, float _duration = 0.0, bool _repeat = false) : delay{_delay}, duration{_duration}, repeat{_repeat} {}
    };

    struct KeyboardSensor : Sensor {
        // Config Values
        int keyCode;
        bool allKeys = false;
        bool logToggle = false;

        std::string target;

        KeyboardSensor(int _keyCode, bool _allKeys, bool _logToggle)
                : keyCode{_keyCode}, allKeys{_allKeys}, logToggle{_logToggle} { }

    };

    template<typename Body, typename Contact>
    struct NearSensor : Sensor {
        // Config Values
        std::string targetTag;
        std::string targetPropertyName;
        float distance = 0;
        float resetDistance = 0;
        Body attachedRigidBody;

        // Signal Values
        std::set<Contact> distanceContactList;
        std::set<Contact> resetDistanceContactList;
        bool initContact = false;
    };

    enum class Axis2D {
        Xpositive, Ypositive, Xnegative, Ynegative
    };

    template<typename Contact>
    struct RadarSensor : Sensor {
        // Config Values
        std::string targetTag;
        std::string targetPropertyName;
        Axis2D axis2D;
        float angle = 0;
        float distance = 0;
        // Signal Values
        std::set<Contact> contactList;
    };


    struct Actuator : LogicBrick {
        bool isActive = false;
    };

    struct Controller : LogicBrick {
        std::unordered_map<std::string, std::unique_ptr<Sensor>> sensors;
        std::unordered_map<std::string, std::unique_ptr<Actuator>> actuators;
    };

    enum class Op {
        OP_NILL,
        OP_AND,
        OP_OR,
        OP_XOR,
        OP_NAND,
        OP_NOR,
        OP_XNOR,
    };

    struct ConditionalController : Controller {
        Op op;
        bool isInverter = false;
    };

    struct ScriptController : Controller {
        std::function<void(Controller &)> script;
    };


}

#endif //ILARGIA_LOGICBRICK_H
