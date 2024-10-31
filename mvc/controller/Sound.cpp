#include "Sound.h"

Sound::Sound()
 : terminateSoundThreads(false)
{
    // Launch a few threads to handle sound playing
    for (int i = 0; i < 5; ++i) {
        soundThreads.emplace_back(&Sound::soundThreadWorker, this);
    }
}

Sound::~Sound()
{
    terminateSoundThreads = true;
    soundCondVar.notify_all();
    for (auto& thread : soundThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void Sound::soundThreadWorker()
{
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

void Sound::playSoundFromFile(const std::string &filePath)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(sound_files_path + filePath)) {
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


Sound *Sound::instance()
{
    static Sound sound;
    return &sound;
}

void Sound::playSound(const std::string &soundPath)
{
    std::lock_guard<std::mutex> lock(soundMutex);
    soundQueue.push(soundPath);
    soundCondVar.notify_one();
}

std::shared_ptr<sf::Music> Sound::clipForLoopFactory(const std::string &fileName)
{
    auto music = std::make_shared<sf::Music>();
    std::string filePath = sound_files_path + fileName;
    if (!music->openFromFile(filePath)) {
        std::cerr << "Error loading looping sound: " << filePath << std::endl;
        return nullptr;
    }
    music->setLoop(true);
    return music;
}
