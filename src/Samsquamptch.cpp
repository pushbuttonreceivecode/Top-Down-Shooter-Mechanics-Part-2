#include <Samsquamptch.hpp>
#include <iostream>

Samsquamptch::Samsquamptch()
    : m_velocity(sf::Vector2f(0.f,0.f))
    , m_target(sf::Vector2f(0.f,0.f))
    , m_bounds(sf::Vector2f(0.f,0.f))
    , m_angle(0.f)
    , m_health(10)
    , m_alive(false)
    , m_aggressionLevel(2.f)
{
    centerOrigin(m_rect);
    setOrigin(m_rect.getOrigin());
}

Samsquamptch::Samsquamptch(float aggressionLevel)
    : m_velocity(sf::Vector2f(0.f,0.f))
    , m_target(sf::Vector2f(0.f,0.f))
    , m_bounds(sf::Vector2f(0.f,0.f))
    , m_angle(0.f)
    , m_health(10)
    , m_alive(false)
    , m_aggressionLevel(aggressionLevel)
{
    centerOrigin(m_rect);
    setOrigin(m_rect.getOrigin());
}

Samsquamptch::~Samsquamptch()
{

}

void Samsquamptch::damage(int d)
{
    if(m_health <= 0)
        m_alive = false;
    else
    {
        m_health -= d;
        m_alive = true;
    }
}

sf::Vector2f Samsquamptch::direction(sf::Vector2f target)
{
    return unitVector(sf::Vector2f(target - getPosition()));
}

void Samsquamptch::updateCurrent(sf::Time dt, sf::Vector2f target, sf::Vector2f bounds)
{
    acquireTarget(target,bounds);

    m_velocity *= dt.asSeconds()*m_aggressionLevel;

    if(getPosition().y >= m_target.y
            && getPosition().y < m_target.y + m_bounds.y
            && getPosition().x >= m_target.x
            && getPosition().x < m_target.x + m_bounds.y)
    {
        //achieved goal - target acquired
    }
    else
    {
        //work towards goal
        setRotation(toDegree(m_angle) + 90.f);
        move(m_velocity);
        m_rect.setPosition(getPosition());
        m_rect.setRotation(getRotation());
        //std::cout<<"Chasing..."<<std::endl;
    }
}

void Samsquamptch::acquireTarget(sf::Vector2f target, sf::Vector2f bounds)
{
    m_bounds = bounds;
    m_target = direction(target);
    m_velocity = unitVector(sf::Vector2f(m_target.x, m_target.y));
    m_angle = std::atan2(m_velocity.y, m_velocity.x);
    //std::cout<<"Target acquired: "<<m_target.x<<", "<<m_target.y<<std::endl;
}

void Samsquamptch::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_rect);
}
