#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>

class Sound {
public:
    Sound();
    ~Sound();
    void playIntroMusic(bool isMuted);
    void playBackgroundMusic(bool isMuted);
    void pauseBackgroundMusic();
    void resumeBackgroundMusic(bool isMuted);
    void playStartSound(bool isMuted);
    void playMoveSound(bool isMuted);
    void playRotateSound(bool isMuted);
    void playDropSound(bool isMuted);
    void playLandSound(bool isMuted);
    void playScoreSound(bool isMuted);
    void playNewHighScoreSound(bool isMuted);
    void playGameOverSound(bool isMuted);
private:
    Mix_Music* introMusic;
    Mix_Music* backgroundMusic;
    Mix_Chunk* startSound;
    Mix_Chunk* moveSound;
    Mix_Chunk* rotateSound;
    Mix_Chunk* dropSound;
    Mix_Chunk* landSound;
    Mix_Chunk* scoreSound;
    Mix_Chunk* newHighScoreSound;
    Mix_Chunk* gameOverSound;
};

#endif //SOUND_H
