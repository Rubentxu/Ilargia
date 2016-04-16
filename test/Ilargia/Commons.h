#ifndef ILARGIA_ENGINE_COMMONS_H
#define ILARGIA_ENGINE_COMMONS_H

#include <memory>
#include <vector>

class TestManager : public Ilargia::Manager {
};

class TestEngine : public Ilargia::Engine {
public:
    bool isConfigure = false;
    bool isInitSystem = false;
    bool isProcessInput = false;
    bool isUpdate = false;
    bool isRender = false;
    bool isShutdown = false;

    TestEngine(std::shared_ptr<Ilargia::Manager> &&manager) : Engine(std::move(manager)) { }

    virtual void configure(std::vector<std::string> &args) override {
        isConfigure = (args[0] == "true") ? true : false;
    }

    virtual void initSystems() override {
        isInitSystem = true;
    }


    virtual void processInput() override {
        isProcessInput = true;

    }

    virtual void update(float deltaTime) override {
        isUpdate = !isUpdate;
    }

    virtual void render() override {
        isRender = true;
        shutdownEngine(1);
    }

    virtual void shutdown() override {
        isShutdown = true;
    }

};

class TestTimer : public Ilargia::Timer {
public:
    TestTimer() : Timer() { }

    virtual double getSecondsTime() override {
        return 0.016666666666666666;
    }

};

class TestGameState: public Ilargia::GameState {
public:
    bool isLoadResources = false;
    bool isInit = false;
    bool isOnResume = false;
    bool isOnPause = false;
    bool isUnloadResources = false;
    TestGameState(std::shared_ptr<Ilargia::Engine> engine) : GameState(engine) {}

    virtual void loadResources()  override { isLoadResources = true;}

    virtual void init()   override { isInit = true;}

    virtual void onResume()  override { isOnResume = true;}

    virtual void onPause()  override { isOnPause = true;}

    virtual void unloadResources()  override { isUnloadResources = true;}

};


#endif //ILARGIA_ENGINE_COMMONS_H
