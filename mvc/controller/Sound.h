#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <atomic>
#include "assetsloader.h"

const std::string sound_files_path = "resources/sounds/";


class Sound {
private:
    std::queue<std::string> soundQueue;
    std::mutex soundMutex;
    std::condition_variable soundCondVar;
    std::vector<std::thread> soundThreads;
    std::atomic<bool> terminateSoundThreads;

    // Private constructor to prevent instantiation
    Sound();
    ~Sound();

    // Worker function for threads to play sounds from the queue
    void soundThreadWorker();

    // Plays a sound from the specified file path using SFML
    void playSoundFromFile(const std::string& filePath);

public:

    static Sound* instance();

    // Add a sound to be played (non-looping)
    void playSound(const std::string& soundPath);

    // Play a looping sound
    std::shared_ptr<sf::Music> clipForLoopFactory(const std::string& fileName);

    // Deleted functions to ensure singleton property
    Sound(const Sound&) = delete;
    Sound& operator=(const Sound&) = delete;
};

#endif
