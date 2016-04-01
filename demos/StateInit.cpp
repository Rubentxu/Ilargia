#include "StateInit.h"
#include "isdl/Components/ViewComponent.h"



void StateInit::loadResources(Ilargia::Engine& assetManager) {
    assetManager.loadTexture("assets/avatar.png","Avatar");
}
void StateInit::unloadResources(Ilargia::Engine& assetManager) {
    assetManager.clearTextureMap();
}

void StateInit::init(Ilargia::Engine& engine) {
    auto entity = world.createEntity();

    Ilargia::ViewComponent& view = entity.addComponent<Ilargia::ViewComponent>();
    view.textureId = "Avatar";
    view.bounds.x = 10;
    view.bounds.y = 10;
    view.bounds.w = 249;
    view.bounds.h= 249;
    view.rotation = 90;
    view.center = {view.bounds.w/2, view.bounds.h/2};
    view.color = {100,150,130,100};
    entity.activate();
}

void StateInit::onResume(Ilargia::Engine& engine) { }

void StateInit::onPause(Ilargia::Engine& engine) { }
