
#ifndef ENTITAS_CONFIG_HPP
#define ENTITAS_CONFIG_HPP

#include <cstddef>


namespace Entitas{

    /// The maximum amount of components an entity can
    /// contain. Try to make this number even, or preferably
    /// a power of 2.
    constexpr const std::size_t MAX_AMOUNT_OF_COMPONENTS = 4;

    enum class ComponentIds {
        // agregar componentes y sus indices
        // ejemplo:
        ICOMPONENT = 0,
		Test2Component=1,
		TestComponent=2
    };

}

#endif // ENTITAS_CONFIG_HPP
