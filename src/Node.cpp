#include <Node.hpp>

#include <algorithm>
#include <cassert>
#include <cmath>

Node::Node()
: m_children()
, m_parent(nullptr)
{

}

Node::~Node()
{

}

void Node::attachChild(ptr child)
{
    child->m_parent = this;
    m_children.push_back(std::move(child));
}

Node::ptr Node::detachChild(const Node& node)
{
    auto found = std::find_if(m_children.begin(), m_children.end(), [&] (ptr& p) { return p.get() == &node; });
	assert(found != m_children.end());

	ptr result = std::move(*found);
	result->m_parent = nullptr;
	m_children.erase(found);
	return result;
}

void Node::update(sf::Time dt, sf::Vector2f target, sf::Vector2f bounds)
{
    updateCurrent(dt,target,bounds);
    updateChildren(dt,target,bounds);
}

void Node::updateCurrent(sf::Time dt, sf::Vector2f target, sf::Vector2f bounds)
{
    //Do nothing by default
}

void Node::updateChildren(sf::Time dt, sf::Vector2f target, sf::Vector2f bounds)
{
    for(auto& child : m_children)
    {
        child->update(dt,target,bounds);
    }
}

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    drawCurrent(target,states);
    drawChildren(target,states);
}

void Node::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
	// Do nothing by default
}

void Node::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const ptr& child : m_children)
    {
        child->draw(target, states);
    }
}
