#include "whiteclouddebris.h"
#include "assetsloader.h"

WhiteCloudDebris::WhiteCloudDebris(Sprite *explodingSprite)
{
    // Set team as debris
    setTeam(Team::DEBRIS);

    // Load graphics into the raster map
    std::map<int, std::shared_ptr<sf::Texture>> rasterMap;
    rasterMap[0] = AssetsLoader::instance()->getImage(TEXTURE_EXP_R1_C1);
    rasterMap[1] = AssetsLoader::instance()->getImage(TEXTURE_EXP_R1_C2);
    rasterMap[2] = AssetsLoader::instance()->getImage(TEXTURE_EXP_R1_C3);
    rasterMap[3] = AssetsLoader::instance()->getImage(TEXTURE_EXP_R2_C1);
    rasterMap[4] = AssetsLoader::instance()->getImage(TEXTURE_EXP_R2_C2);
    rasterMap[5] = AssetsLoader::instance()->getImage(TEXTURE_EXP_R2_C3);
    rasterMap[6] = AssetsLoader::instance()->getImage(TEXTURE_EXP_R3_C1);
    rasterMap[7] = AssetsLoader::instance()->getImage(TEXTURE_EXP_R3_C2);
    rasterMap[8] = AssetsLoader::instance()->getImage(TEXTURE_EXP_R3_C3);

    setRasterMap(rasterMap);

    // Set expiry based on the number of images (frames)
    setExpiry(static_cast<int>(rasterMap.size()));

    // Inherit properties from the exploding sprite
    setSpin(explodingSprite->getSpin());
    setCenter(explodingSprite->getCenter());
    setDeltaX(explodingSprite->getDeltaX());
    setDeltaY(explodingSprite->getDeltaY());
    setRadius(static_cast<int>(explodingSprite->getRadius() * 1.3));
}

void WhiteCloudDebris::draw(sf::RenderWindow &window)
{
    // Calculate the index based on the remaining expiry
    int index = static_cast<int>(getRasterMap().size()) - getExpiry() - 1;

    if (getRasterMap().find(index) != getRasterMap().end()) {
        renderRaster(window, getRasterMap()[index]);
    }
}
