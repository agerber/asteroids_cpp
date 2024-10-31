#include "assetsloader.h"

AssetsLoader* AssetsLoader::assetInstance = nullptr;


std::shared_ptr<sf::Texture> AssetsLoader::getImage(const std::string &filename) const
{
    auto it = images.find(filename);
    if (it != images.end()) {
        return it->second;
    } else {
        std::cerr << "Image not found: " << filename << std::endl;
        return nullptr;
    }
}

void AssetsLoader::playSound(const std::string &filename) const
{
    auto it = sounds.find(filename);
    if (it != sounds.end()) {
        sf::Sound sound;
        sound.setBuffer(*it->second);
        sound.play();
        // Normally you'd manage the sound's lifetime if it should persist.
    } else {
        std::cerr << "Sound not found: " << filename << std::endl;
    }
}

std::shared_ptr<sf::SoundBuffer> AssetsLoader::getSound(const std::string &filename) const
{
    auto it = sounds.find(filename);
    if (it != sounds.end()) {
        return it->second;
    } else {
        std::cerr << "Sound not found: " << filename << std::endl;
    }
}

std::shared_ptr<sf::Font> AssetsLoader::useFont(const std::string &filename) const
{
    auto it = fonts.find(filename);
    if (it != fonts.end()) {
        return it->second;
    } else {
        std::cerr << "Font not found: " << filename << std::endl;
        return nullptr;
    }
}

void AssetsLoader::loadFonts()
{
    for (const auto& entry : std::filesystem::directory_iterator(FONTS_PATH)) {
        auto font = std::make_shared<sf::Font>();
        if (font->loadFromFile(entry.path().string())) {
            std::string filename = entry.path().filename().string();
            fonts[filename] = font;
        } else {
            std::cerr << "Failed to load font: " << entry.path() << std::endl;
        }
    }
}

void AssetsLoader::loadSounds()
{
    for (const auto& entry : std::filesystem::directory_iterator(AUDIO_PATH)) {
        auto soundBuffer = std::make_shared<sf::SoundBuffer>();
        if (soundBuffer->loadFromFile(entry.path().string())) {
            std::string filename = entry.path().filename().string();
            sounds[filename] = soundBuffer;
        } else {
            std::cerr << "Failed to load sound: " << entry.path() << std::endl;
        }
    }
}


std::string AssetsLoader::getRelativePath(const std::filesystem::path& fullPath, const std::string& baseFolder) const {
    auto relativePath = std::filesystem::relative(fullPath, baseFolder);
    return relativePath.string();
}

void AssetsLoader::loadImages()
{
    for (const auto& entry : std::filesystem::recursive_directory_iterator(IMAGES_PATH)) {
        if (entry.is_regular_file()) {
            auto texture = std::make_shared<sf::Texture>();
            if (texture->loadFromFile(entry.path().string())) {
                std::string relativePath = getRelativePath(entry.path(), IMAGES_PATH);
                images[relativePath] = texture;
            } else {
                std::cerr << "Failed to load image: " << entry.path() << std::endl;
            }
        }
    }
}

AssetsLoader::AssetsLoader()
{

}

void AssetsLoader::loadAssets()
{
    loadImages();
    loadSounds();
    loadFonts();
}

AssetsLoader *AssetsLoader::instance()
{
    if (!assetInstance) {
        assetInstance = new AssetsLoader();
        assetInstance->loadAssets();
    }
    return assetInstance;
}
