#include <Player.hpp>

Player::Player()
{

}

Player::~Player()
{

}

void Player::damage(int d)
{
    if(m_health <= 0)
        m_alive = false;
    else
    {
        m_health -= d;
        m_alive = true;
    }
}
