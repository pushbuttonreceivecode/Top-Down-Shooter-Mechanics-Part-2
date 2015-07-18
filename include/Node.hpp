#ifndef NODE_HPP
#define NODE_HPP

#include <GeneralUtilities.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <memory>
#include <vector>

class Node : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    public:

        typedef std::unique_ptr<Node> ptr;

    public:
        Node();
        ~Node();

        void attachChild(ptr child);
        ptr detachChild(const Node& node);

        void update(sf::Time dt, sf::Vector2f target, sf::Vector2f bounds);
        virtual void updateCurrent(sf::Time dt, sf::Vector2f target, sf::Vector2f bounds);
        void updateChildren(sf::Time dt, sf::Vector2f target, sf::Vector2f bounds);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;
        virtual void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        Node* m_parent;
        std::vector<ptr> m_children;
};

#endif // NODE_HPP
