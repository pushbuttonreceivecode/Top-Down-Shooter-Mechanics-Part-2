#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <GeneralUtilities.hpp>

class Player : public sf::RectangleShape
{
    public:
        Player();
        ~Player();

        sf::Uint32 const getHealth() const {return m_health;};
        void damage(int d);

        bool const isAlive() const {return m_alive;};

    private:
        sf::Uint32 m_health;
        bool m_alive;
};

#endif // PLAYER_HPP
