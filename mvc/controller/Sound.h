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

class Sound {
private:
    std::queue<std::string> soundQueue;
    std::mutex soundMutex;
    std::condition_variable soundCondVar;
    std::vector<std::thread> soundThreads;
    std::atomic<bool> terminateSoundThreads;



    // Private constructor to prevent instantiation
    Sound() : terminateSoundThreads(false) {
        // Launch a few threads to handle sound playing
        for (int i = 0; i < 5; ++i) {
            soundThreads.emplace_back(&Sound::soundThreadWorker, this);
        }
    }

    ~Sound() {
        terminateSoundThreads = true;
        soundCondVar.notify_all();
        for (auto& thread : soundThreads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

    // Worker function for threads to play sounds from the queue
    void soundThreadWorker() {
        while (!terminateSoundThreads) {
            std::unique_lock<std::mutex> lock(soundMutex);
            soundCondVar.wait(lock, [this] { return !soundQueue.empty() || terminateSoundThreads; });
            if (terminateSoundThreads) break;

            std::string filePath = soundQueue.front();
            soundQueue.pop();
            lock.unlock();

            playSoundFromFile(filePath);
        }
    }

    // Plays a sound from the specified file path using SFML
    void playSoundFromFile(const std::string& filePath) {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(filePath)) {
            std::cerr << "Error loading sound file: " << filePath << std::endl;
            return;
        }

        sf::Sound sound;
        sound.setBuffer(buffer);
        sound.play();

        // Keep the sound object alive until it finishes playing
        while (sound.getStatus() == sf::Sound::Playing) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

public:
    // Get the singleton instance
    static Sound& getInstance() {
        static Sound instance;
        return instance;
    }

    static Sound* instance();

    // Add a sound to be played (non-looping)
    void playSound(const std::string& soundPath) {
        std::lock_guard<std::mutex> lock(soundMutex);
        soundQueue.push(soundPath);
        soundCondVar.notify_one();
    }

    // Play a looping sound
    std::shared_ptr<sf::Music> clipForLoopFactory(const std::string& fileName) {
        auto music = std::make_shared<sf::Music>();
        std::string filePath = "sounds/" + fileName;
        if (!music->openFromFile(filePath)) {
            std::cerr << "Error loading looping sound: " << filePath << std::endl;
            return nullptr;
        }
        music->setLoop(true);
        return music;
    }

    // Deleted functions to ensure singleton property
    Sound(const Sound&) = delete;
    Sound& operator=(const Sound&) = delete;
};

#endif
