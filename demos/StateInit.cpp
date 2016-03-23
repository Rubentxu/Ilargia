#include "StateInit.h"
#include "Components/ViewComponent.h"


void StateInit::loadResources(Ilargia::AssetManager& assetManager) {
    assetManager.loadTexture("assets/avatar.png","Avatar");
}
void StateInit::unloadResources(Ilargia::AssetManager& assetManager) {
    assetManager.clearTextureMap();
}

void StateInit::init(anax::World &world) {
    auto entity = world.createEntity();

    Ilargia::ViewComponent& view = entity.addComponent<Ilargia::ViewComponent>();
    view.textureId = "Avatar";
    view.center = SDL_Point {100,100};
    view.bounds.x = 10;
    view.bounds.y = 10;
    view.bounds.w = 249;
    view.bounds.h= 249;
    entity.activate();
}
void StateInit::onResume(anax::World &world) { }
void StateInit::onPause(anax::World &world) { }
