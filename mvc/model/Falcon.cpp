#include "Falcon.h"
#include "assetsloader.h"

Falcon::Falcon()
{
    setTeam(Team::FRIEND);
    setRadius(MIN_RADIUS);
    shield = 0;
    nukeMeter = 0;
    invisible = 0;
    maxSpeedAttained = false;
    showLevel = 0;
    thrusting = false;
    turnState = TurnState::IDLE;

    // Load images
    std::map<int, std::shared_ptr<sf::Texture>> rasterMap;
    rasterMap[static_cast<int>(ImageState::FALCON_INVISIBLE)] = nullptr;
    rasterMap[static_cast<int>(ImageState::FALCON)] = AssetsLoader::instance()->getImage(TEXTURE_FALCON_FILE);
    rasterMap[static_cast<int>(ImageState::FALCON_THR)] = AssetsLoader::instance()->getImage(TEXTURE_FALCON_THRUST_FILE);
    rasterMap[static_cast<int>(ImageState::FALCON_PRO)] = AssetsLoader::instance()->getImage(TEXTURE_FALCON_PRO_FILE);
    rasterMap[static_cast<int>(ImageState::FALCON_PRO_THR)] = AssetsLoader::instance()->getImage(TEXTURE_FALCON_PRO_THRUST_FILE);

    setRasterMap( rasterMap );
}

void Falcon::move()
{
    Sprite::move();

    if (invisible > 0) invisible--;
    if (shield > 0) shield--;
    if (nukeMeter > 0) nukeMeter--;
    if (showLevel > 0) showLevel--;

    const double THRUST = 0.85;
    const int MAX_VELOCITY = 39;

    if (thrusting) {
        double vectorX = std::cos(Utils::my_qDegreesToRadians(getOrientation())) * THRUST;
        double vectorY = std::sin(Utils::my_qDegreesToRadians(getOrientation())) * THRUST;

        int absVelocity = static_cast<int>(std::sqrt(
            std::pow(getDeltaX() + vectorX, 2) + std::pow(getDeltaY() + vectorY, 2)));

        if (absVelocity < MAX_VELOCITY) {
            setDeltaX(getDeltaX() + vectorX);
            setDeltaY(getDeltaY() + vectorY);
            setRadius(MIN_RADIUS + absVelocity / 3);
            maxSpeedAttained = false;
        } else {
            maxSpeedAttained = true;
        }
    }

    int adjustOr = getOrientation();
    switch (turnState) {
    case TurnState::LEFT:
        adjustOr = (getOrientation() <= 0) ? 360 - TURN_STEP : getOrientation() - TURN_STEP;
        break;
    case TurnState::RIGHT:
        adjustOr = (getOrientation() >= 360) ? TURN_STEP : getOrientation() + TURN_STEP;
        break;
    case TurnState::IDLE:
    default:
        break;
    }
    setOrientation(adjustOr);
}

void Falcon::draw(sf::RenderWindow &window)
{
    ImageState imageState;
    if (invisible > 0) {
        imageState = ImageState::FALCON_INVISIBLE;
    } else if (isProtected()) {
        imageState = thrusting ? ImageState::FALCON_PRO_THR : ImageState::FALCON_PRO;
        drawShield(window);
    } else {
        imageState = thrusting ? ImageState::FALCON_THR : ImageState::FALCON;
    }

    // Render based on image state
    renderRaster( window, getRasterMap()[static_cast<int>(imageState)], getRadius() * 4);
}

void Falcon::drawShield(sf::RenderWindow &window)
{
    sf::CircleShape shieldShape(getRadius());
    shieldShape.setOutlineColor(sf::Color::Cyan);
    shieldShape.setOutlineThickness(1);
    shieldShape.setFillColor(sf::Color::Transparent);
    shieldShape.setPosition(getCenter().x - getRadius(), getCenter().y - getRadius());
    window.draw(shieldShape);
}
