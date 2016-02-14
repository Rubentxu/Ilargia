#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <boost/any.hpp>
#include <boost/optional.hpp>


class blackBoard {
    std::map<std::string, boost::any> properties;

public:
    blackBoard() {};

    blackBoard(blackBoard const &s) = delete;

    void operator=(blackBoard const &x) = delete;

    template<typename T>
    T& get(std::string name) {
        boost::any result = properties.at(name);
        if (!result.empty() && result.type() == typeid(T))
            return boost::any_cast<T&>(result);
        else
            set(name,new T{});
            return boost::any_cast<T&>(properties.at(name));
    }

    template<class... Args>
    void set(std::string name, Args &&... value) {
        properties.emplace(std::string(name), boost::any(std::forward<Args>(value)...));
        //OnPropertyChanged(name);
    }
};

#endif //BLACKBOARD_H
