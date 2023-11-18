#include <SFML/Graphics.hpp>

class Bonus : public sf::Sprite
{
public:
    Bonus(float x, float y, const sf::Texture& texture);

    bool isTouched(const sf::FloatRect& playerBounds);
};
