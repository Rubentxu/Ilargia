#ifndef ILARGIA_MANAGER_H
#define ILARGIA_MANAGER_H

class Manager {
private:
    std::vector <std::unique_ptr<Entity>> entities;
    std::map <std::size_t, std::vector<Entity *>> groupedEntities;

public:
    template<typename T, typename... TArgs>
    T &create(TArgs &&... mArgs) {
        static_assert(std::is_base_of<Entity, T>::value,
                      "`T` must be derived from `Entity`");

        auto uPtr(std::unique_ptr<T>(std::forward<TArgs>(mArgs)...));
        auto ptr(uPtr.get());
        groupedEntities[typeid(T).hash_code()].emplace_back(ptr);
        entities.emplace_back(std::move(uPtr));

        return *ptr;
    }

    void refresh() {
        for (auto &pair : groupedEntities) {
            auto &vector(pair.second);

            vector.erase(std::remove_if(std::begin(vector), std::end(vector),
                                        [](auto mPtr) {
                                            return mPtr->destroyed;
                                        }),
                         std::end(vector));
        }

        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
                                      [](const auto &mUPtr) {
                                          return mUPtr->destroyed;
                                      }),
                       std::end(entities));
    }

    void clear() {
        groupedEntities.clear();
        entities.clear();
    }

    template<typename T>
    auto &getAll() {
        return groupedEntities[typeid(T).hash_code()];
    }

    template<typename T, typename TFunc>
    void forEach(const TFunc &mFunc) {
        for (auto ptr : getAll<T>()) mFunc(*reinterpret_cast<T *>(ptr));
    }

    void update() {
        for (auto &e : entities) e->update();
    }

    void draw(sf::RenderWindow &mTarget) {
        for (auto &e : entities) e->draw(mTarget);
    }
};

#endif //ILARGIA_MANAGER_H
