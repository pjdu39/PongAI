#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>

namespace Collision {

    inline bool circleIntersectsRectangle(const sf::CircleShape& circle, const sf::RectangleShape& rect) {
        sf::Vector2f circleCenter = circle.getPosition();
        float radius = circle.getRadius();
        sf::FloatRect rectBounds = rect.getGlobalBounds();

        float nearestX = std::max(rectBounds.position.x, std::min(circleCenter.x, rectBounds.position.x + rectBounds.size.x));
        float nearestY = std::max(rectBounds.position.y, std::min(circleCenter.y, rectBounds.position.y + rectBounds.size.y));

        float deltaX = circleCenter.x - nearestX;
        float deltaY = circleCenter.y - nearestY;
        float distanceSquared = deltaX * deltaX + deltaY * deltaY;

        return distanceSquared < (radius * radius);
    }

}