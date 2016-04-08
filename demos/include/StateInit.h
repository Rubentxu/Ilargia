#ifndef ILARGIA_STATEINIT_H
#define ILARGIA_STATEINIT_H

#include "core/GameState.h"

class StateInit : public Ilargia::GameState {

    virtual void loadResources(Ilargia::Engine& engine) override;

    virtual void init(Ilargia::Engine& engine) override;

    virtual void onResume(Ilargia::Engine& engine) override;

    virtual void onPause(Ilargia::Engine& engine) override;

    virtual void unloadResources(Ilargia::Engine& engine) override;
};


#endif //ILARGIA_STATEINIT_H
