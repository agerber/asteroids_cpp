#include "Sound.h"

Sound *Sound::instance()
{
    static Sound sound;
    return &sound;
}
