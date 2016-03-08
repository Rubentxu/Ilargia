
#ifndef ENTITAS_CONFIG_HPP
#define ENTITAS_CONFIG_HPP

#include <cstddef>


namespace Entitas{

    /// The maximum amount of components an entity can
    /// contain. Try to make this number even, or preferably
    /// a power of 2.
    constexpr const std::size_t MAX_AMOUNT_OF_COMPONENTS = @MAX_AMOUNT_OF_COMPONENTS@;

    enum class ComponentIds {
        // agregar componentes y sus indices
        // ejemplo:
        @COMPONENT_IDS@
    };

}

#endif // ENTITAS_CONFIG_HPP
