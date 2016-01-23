#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include <string>
#include <map>
#include <memory>
#include "any.h"
#include <iostream>

class blackboard {
    std::map<std::string, std::unique_ptr<any>> properties;

public:
    blackboard();

    template<typename T>
    T get(std::string name) {
        return static_cast<T>(properties.at(name));
    }

    template<class... Args>
    void set(std::string name, Args &&... value) {
        properties.emplace(std::string(name), make_unique<any>(std::forward<Args>(value)...));
        //OnPropertyChanged(name);
    }

    std::map<std::string, std::unique_ptr<any>> getProperties() const {
        return properties;
    };


};

#endif //BLACKBOARD_H
