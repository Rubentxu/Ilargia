#include "Game.hpp"
#include <iostream>
#include <Components/TransformComponent.hpp>
#include <Components/SpriteComponent.hpp>

const std::string PLAYER_TEXTURE_ID{"player"};
const sf::Color CLEAR_COLOR{60, 60, 60};


Game::Game(sf::RenderTarget& renderTarget) :
    m_renderTarget(&renderTarget),
    m_spriteRenderingSystem(renderTarget)
{
}

void Game::init()
{
    loadResources();

    // create the player
    auto player = m_world.createEntity();

    auto& playerSprite = player.addComponent<SpriteComponent>().sprite;
    playerSprite.setTexture(m_textureCache[PLAYER_TEXTURE_ID]);

    auto& playerTransform = player.addComponent<TransformComponent>().transform;
    playerTransform.setPosition(m_renderTarget->getView().getSize().x / 2 - playerSprite.getLocalBounds().width / 2, m_renderTarget->getView().getSize().y / 2 - playerSprite.getLocalBounds().height / 2);

    // activate the player
    player.activate();

    // Add the systems to the world
    m_world.addSystem(m_spriteRenderingSystem);
}

void Game::update(float deltaTime)
{
    m_world.refresh();
}

void Game::render()
{
    m_renderTarget->clear(CLEAR_COLOR);
    m_spriteRenderingSystem.render();
}

void Game::handleEvents(sf::Event event)
{
    switch(event.type)
    {
        case sf::Event::Closed:
            quit();
            break;
        case sf::Event::KeyPressed:
            switch(event.key.code)
            {
                case sf::Keyboard::Key::Escape:
                    quit();
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void Game::loadResources()
{
    if(!m_textureCache[PLAYER_TEXTURE_ID].loadFromFile("resources/textures/playerSpriteSheet.png"))
    {
        std::cerr << "Failed to load spritesheet\n";
        quit();
    }
}
