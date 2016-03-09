//
// Created by rdcabrera on 08/03/2016.
//

#ifndef ILARGIA_TESTCOMPONENT_H
#define ILARGIA_TESTCOMPONENT_H

#include <Entity.h>


namespace Entitas {
    struct TestComponent: public IComponent {
        bool _test = false;
        TestComponent(){}
        TestComponent(bool test):_test{test}{}
    };


}


#endif //ILARGIA_TESTCOMPONENT_H
