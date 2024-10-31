#ifndef ASSETSLOADER_H
#define ASSETSLOADER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>
#include <filesystem>
#include <string>
#include <iostream>


#define IMAGES_PATH "resources/imgs"
#define AUDIO_PATH "resources/sounds"
#define FONTS_PATH "resources/fonts"
#define GAME_PANEL_FONT_NAME "big.ttf"

#define TEXTURE_FALCON_FILE "fal/falcon125.png"
#define TEXTURE_FALCON_THRUST_FILE "fal/falcon125_thr.png"
#define TEXTURE_FALCON_PRO_FILE "fal/falcon125_PRO.png"
#define TEXTURE_FALCON_PRO_THRUST_FILE "fal/falcon125_PRO_thr.png"


#define TEXTURE_EXP_R1_C1 "exp/row-1-column-1.png"
#define TEXTURE_EXP_R1_C2 "exp/row-1-column-2.png"
#define TEXTURE_EXP_R1_C3 "exp/row-1-column-3.png"
#define TEXTURE_EXP_R2_C1 "exp/row-2-column-1.png"
#define TEXTURE_EXP_R2_C2 "exp/row-2-column-2.png"
#define TEXTURE_EXP_R2_C3 "exp/row-2-column-3.png"
#define TEXTURE_EXP_R3_C1 "exp/row-3-column-1.png"
#define TEXTURE_EXP_R3_C2 "exp/row-3-column-2.png"
#define TEXTURE_EXP_R3_C3 "exp/row-3-column-3.png"

#define SOUND_INSEC "insect.wav"
#define SOUND_KAPOW "kapow.wav"
#define SOUND_LASER "laser.wav"
#define SOUND_BG "music-background.wav"
#define SOUND_NUKE "nuke.wav"
#define SOUND_NUKE_UP "nuke-up.wav"
#define SOUND_PAC "pac.wav"
#define SOUND_SHIELD_UP "shieldup.wav"
#define SOUND_SHIP_SPAWN "shipsawn.wav"
#define SOUND_THUMP "thump.wav"
#define SOUND_WHITENOISE "whitenoise.wav"

class AssetsLoader
{
public:
    AssetsLoader();
    void loadAssets();
    static AssetsLoader* instance();

    std::shared_ptr<sf::Texture> getImage(const std::string& filename) const;
    void playSound(const std::string& filename) const;
    std::shared_ptr<sf::SoundBuffer> getSound(const std::string& filename) const;
    std::shared_ptr<sf::Font> useFont(const std::string& filename) const;

private:
    void loadImages();
    void loadSounds();
    void loadFonts();

    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> images;
    std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> sounds;
    std::unordered_map<std::string, std::shared_ptr<sf::Font>> fonts;

    static AssetsLoader* assetInstance;
    std::string getRelativePath(const std::filesystem::path& fullPath, const std::string& baseFolder) const;

};




#endif // ASSETSLOADER_H
