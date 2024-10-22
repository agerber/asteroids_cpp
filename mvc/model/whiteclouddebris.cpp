#include "whiteclouddebris.h"


WhiteCloudDebris::WhiteCloudDebris(const Sprite &explodingSprite)
{
    // Set team as debris
    setTeam(Team::DEBRIS);

    // Load graphics into the raster map
    std::map<int, std::shared_ptr<sf::Texture>> rasterMap;
    rasterMap[0] = loadGraphic("resources/imgs/exp/row-1-column-1.png");
    rasterMap[1] = loadGraphic("resources/imgs/exp/row-1-column-2.png");
    rasterMap[2] = loadGraphic("resources/imgs/exp/row-1-column-3.png");
    rasterMap[3] = loadGraphic("resources/imgs/exp/row-2-column-1.png");
    rasterMap[4] = loadGraphic("resources/imgs/exp/row-2-column-2.png");
    rasterMap[5] = loadGraphic("resources/imgs/exp/row-2-column-3.png");
    rasterMap[6] = loadGraphic("resources/imgs/exp/row-3-column-1.png");
    rasterMap[7] = loadGraphic("resources/imgs/exp/row-3-column-2.png");
    rasterMap[8] = loadGraphic("resources/imgs/exp/row-3-column-3.png");

    setRasterMap(rasterMap);

    // Set expiry based on the number of images (frames)
    setExpiry(static_cast<int>(rasterMap.size()));

    // Inherit properties from the exploding sprite
    setSpin(explodingSprite.getSpin());
    setCenter(explodingSprite.getCenter());
    setDeltaX(explodingSprite.getDeltaX());
    setDeltaY(explodingSprite.getDeltaY());
    setRadius(static_cast<int>(explodingSprite.getRadius() * 1.3));
}

void WhiteCloudDebris::draw(sf::RenderWindow &window)
{
    // Calculate the index based on the remaining expiry
    int index = static_cast<int>(getRasterMap().size()) - getExpiry() - 1;

    if (getRasterMap().find(index) != getRasterMap().end()) {
        renderRaster(window, getRasterMap()[index]);
    }
}