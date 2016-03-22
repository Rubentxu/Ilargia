#ifndef ILARGIA_STATEINIT_H
#define ILARGIA_STATEINIT_H

#include "GameState.h"
#include "AssetManager.h"

class AssetManager;

class StateInit : public Ilargia::GameState {

    virtual void loadResources(Ilargia::AssetManager& assetManager) override;

    virtual void init(anax::World& world) override;

    virtual void onResume(anax::World& world) override;

    virtual void onPause(anax::World& world) override;

    virtual void unloadResources(Ilargia::AssetManager& assetManager) override;
};


#endif //ILARGIA_STATEINIT_H
