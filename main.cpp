#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <utility>
#include <array>

#include <SFML/Graphics.hpp>

#include <GeneralUtilities.hpp>
#include <Node.hpp>
#include <Samsquamptch.hpp>
#include <Player.hpp>
#include <Projectile.hpp>
#include <Pickup.hpp>

enum Layer
{
    samsquamptches,
    layerCount
};

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(800,600,32), "The Hoards that Follow", sf::Style::Default);
    sf::Event e;

    Player player;
    player.setFillColor(sf::Color(200,0,0,255));
    player.setSize(sf::Vector2f(20.f,20.f));
    player.setPosition(window.getSize().x/2.f, window.getSize().y - player.getLocalBounds().height);

    //create an empty node to use as a scene graph
    Node sceneGraph;

    //set up the number of layers available in the scene graph
    std::array<Node*, layerCount> layers;

    for (std::size_t i = 0; i < layerCount; ++i)
	{
	    Node::ptr layer(new Node);
		layers[i] = layer.get();

		sceneGraph.attachChild(std::move(layer));
	}

    sf::Font myfont;
    if(!myfont.loadFromFile("resources/fonts/contb.ttf"))
    {
        std::cerr<<"Could not load font"<<std::endl;
    }

    sf::Text status("Chasing....", myfont);
    status.setPosition(window.getSize().x/2.f, 0.f);
    status.setCharacterSize(32);
    status.setColor(sf::Color(200,100,0,255));

    sf::Time timePerFrame = sf::seconds(1.f/60.f);
    sf::Clock clock;
    sf::Time timeElapsed = sf::Time::Zero;
    sf::Time duration = sf::Time::Zero;

    //spawn and timing
    sf::Clock spawnTime;
    unsigned int squanchCounter = 0;

    while(window.isOpen())
    {
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
            {
                window.close();
                return 0;
            }

            if(e.type == sf::Event::KeyPressed)
            {
                switch(e.key.code)
                {
                case sf::Keyboard::Escape:
                    {
                        window.close();
                        return 0;
                    }
                    break;

                case sf::Keyboard::Left:
                {
                    player.move(-10.f,0.f);
                }
                break;

                case sf::Keyboard::Right:
                {
                    player.move(10.f,0.f);
                }
                break;

                case sf::Keyboard::Up:
                {
                    player.move(0.f,-10.f);
                }
                break;

                case sf::Keyboard::Down:
                {
                    player.move(0.f,10.f);
                }
                break;

                default:
                    break;
                }
            }
        }

        if(spawnTime.getElapsedTime().asSeconds() > 2.f)
        {
            //spawn samsquamptches every 2 seconds
            std::unique_ptr<Samsquamptch> enemy(new Samsquamptch(50.f));
            enemy->setFillColor(sf::Color(0,200,0,255));
            enemy->setSize(30.f,30.f);
            enemy->setPosition(window.getSize().x/2.f,0.f);
            layers[samsquamptches]->attachChild(std::move(enemy));

            squanchCounter++;

            spawnTime.restart();
        }

        window.setTitle("Samsquamptches: " + std::to_string(squanchCounter));

        timeElapsed += clock.restart();
        while (timeElapsed > timePerFrame)
        {
            timeElapsed -= timePerFrame;

            //update sceneGraph
            sceneGraph.update(timePerFrame, player.getPosition(), sf::Vector2f(player.getSize().x,player.getSize().y));
        }

        window.clear();
        window.draw(player);

        //draw sceneGraph
        window.draw(sceneGraph);

        window.display();
    }
    return 0;
}
