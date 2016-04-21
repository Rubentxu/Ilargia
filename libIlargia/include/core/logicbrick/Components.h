#ifndef ILARGIA_SENSORCOMPONENT_H
#define ILARGIA_SENSORCOMPONENT_H

#include <vector>
#include "core/logicbrick/LogicBrick.h"

namespace Ilargia {

    struct DefaultBase {
    };

    struct State {
        float time = 0.0f;
        int oldState = -1;
        bool isChanged = false;
        std::vector<std::string> states;
        int typeIndex = -1;
        int currentState = 0;
    };


    struct Color {
        float R, G, B;
    };

    template<typename Transform>
    struct View {
        std::string name;
        Transform attachedTransform;
        mathfu::Vector<float, 2> position;
        mathfu::Vector<float, 2> localPosition;
        float rotation = 0;
        int opacity = 1;
        int layer;
        Color tint;
    };

    template<typename Transform>
    struct TextureView : View<Transform> {
        std::string texture;
        float height;
        float width;
        bool flipX = false;
        bool flipY = false;
    };

    /*template<typename Transform>
    struct ParticleEffectView : View<Transform> {
        ParticleEffect effect;
        boolean autoStart = false;
    };*/

    template<typename Sensor, typename BaseComponent = DefaultBase>
    struct SensorComponents : BaseComponent {
        std::vector<std::vector<Sensor>> sensors;
    };

    //using MouseSensorComponents = SensorComponents<MouseSensor,DefaultBase>;

}

#endif //ILARGIA_SENSORCOMPONENT_H
