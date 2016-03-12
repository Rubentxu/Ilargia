#ifndef ILARGIA_ENTITY_H
#define ILARGIA_ENTITY_H

class Entity
{
public:
    bool destroyed{false};

    virtual ~Entity() {}
    virtual void update() {}
    virtual void draw(/*sf::RenderWindow& mTarget*/) {}
};

#endif //ILARGIA_ENTITY_H
