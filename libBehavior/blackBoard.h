#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include <string>
#include <map>
#include <memory>
#include <iostream>

class blackBoard {
    std::map<std::string, std::unique_ptr<boost::any>> properties;

public:
    blackBoard() {};

    blackBoard(blackBoard const &s) = delete;

    void operator=(blackBoard const &x) = delete;

    template<typename T>
    T get(std::string name) {
        boost::any*  result = properties.at(name).get();
        if (result->is<T>())
            return result->_<T>();
        else nullptr;
    }

    template<typename T>
    bool is(std::string name) {

        return properties.at(name)->is<T>();
    }

    template<class... Args>
    void set(std::string name, Args &&... value) {
        properties.emplace(std::string(name), make_unique<boost::any>(std::forward<Args>(value)...));
        //OnPropertyChanged(name);
    }

//    std::map<std::string, std::unique_ptr<any>> getProperties() const {
//        return properties;
//    };

};

#endif //BLACKBOARD_H
