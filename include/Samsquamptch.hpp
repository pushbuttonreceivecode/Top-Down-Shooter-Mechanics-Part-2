#ifndef SAMSQUAMPTCH_HPP
#define SAMSQUAMPTCH_HPP

#include <Node.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include <GeneralUtilities.hpp>

class Samsquamptch : public Node
{
    public:
        Samsquamptch();
        Samsquamptch(float aggressionLevel);
        ~Samsquamptch();

        sf::Uint32 const getHealth() const {return m_health;};
        void damage(int d);

        void setSize(float x, float y){m_rect.setSize(sf::Vector2f(x,y));};
        sf::Vector2f const getSize() const {return m_rect.getSize();};

        void setFillColor(sf::Color c){m_rect.setFillColor(c);};

        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        virtual void updateCurrent(sf::Time dt, sf::Vector2f target, sf::Vector2f bounds);

     private:
        sf::Vector2f direction(sf::Vector2f target);
        void acquireTarget(sf::Vector2f target, sf::Vector2f bounds);

    private:
        sf::RectangleShape m_rect;

        sf::Vector2f m_velocity;
        sf::Vector2f m_bounds;
        sf::Vector2f m_target;
        float m_angle;

        sf::Uint32 m_health;
        bool m_alive;
        float m_aggressionLevel;
};

#endif // SAMSQUAMPTCH_HPP
