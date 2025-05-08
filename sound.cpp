#include "sound.h"
#include <iostream>

Sound::Sound() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        return;
    }

    introMusic = Mix_LoadMUS("D:/TETRIS_GAME/assets/mix/intro_music.mp3");
    backgroundMusic = Mix_LoadMUS("D:/TETRIS_GAME/assets/mix/background_music.mp3");
    startSound = Mix_LoadWAV("D:/TETRIS_GAME/assets/mix/start_sound.mp3");
    moveSound = Mix_LoadWAV("D:/TETRIS_GAME/assets/mix/move_sound.mp3");
    rotateSound = Mix_LoadWAV("D:/TETRIS_GAME/assets/mix/rotate_sound.mp3");
    dropSound = Mix_LoadWAV("D:/TETRIS_GAME/assets/mix/drop_sound.mp3");
    landSound = Mix_LoadWAV("D:/TETRIS_GAME/assets/mix/land_sound.mp3");
    scoreSound = Mix_LoadWAV("D:/TETRIS_GAME/assets/mix/score_sound.mp3");
    newHighScoreSound = Mix_LoadWAV("D:/TETRIS_GAME/assets/mix/highscore_sound.mp3");
    gameOverSound = Mix_LoadWAV("D:/TETRIS_GAME/assets/mix/gameover_sound.mp3");
}

Sound::~Sound() {
    Mix_FreeMusic(introMusic);
    Mix_FreeMusic(backgroundMusic);
    Mix_FreeChunk(startSound);
    Mix_FreeChunk(moveSound);
    Mix_FreeChunk(rotateSound);
    Mix_FreeChunk(dropSound);
    Mix_FreeChunk(landSound);
    Mix_FreeChunk(scoreSound);
    Mix_FreeChunk(newHighScoreSound);
    Mix_FreeChunk(gameOverSound);
    Mix_CloseAudio();
}

void Sound::playIntroMusic(bool isMuted) {
    if (!isMuted && introMusic) Mix_PlayMusic(introMusic, 1);
}

void Sound::playBackgroundMusic(bool isMuted) {
    if (!isMuted && backgroundMusic) Mix_PlayMusic(backgroundMusic, -1);
}

void Sound::pauseBackgroundMusic() {
    Mix_PauseMusic();
}

void Sound::resumeBackgroundMusic(bool isMuted) {
    if (!isMuted && backgroundMusic) Mix_ResumeMusic();
}

void Sound::playStartSound(bool isMuted) {
    if (!isMuted && startSound) Mix_PlayChannel(-1, startSound, 0);
}

void Sound::playMoveSound(bool isMuted) {
    if (!isMuted && moveSound) Mix_PlayChannel(-1, moveSound, 0);
}

void Sound::playRotateSound(bool isMuted) {
    if (!isMuted && rotateSound) Mix_PlayChannel(-1, rotateSound, 0);
}

void Sound::playDropSound(bool isMuted) {
    if (!isMuted && dropSound) Mix_PlayChannel(-1, dropSound, 0);
}

void Sound::playLandSound(bool isMuted) {
    if (!isMuted && landSound) Mix_PlayChannel(-1, landSound, 0);
}

void Sound::playScoreSound(bool isMuted) {
    if (!isMuted && scoreSound) Mix_PlayChannel(-1, scoreSound, 0);
}

void Sound::playNewHighScoreSound(bool isMuted) {
    if (!isMuted && newHighScoreSound) Mix_PlayChannel(-1, newHighScoreSound, 0);
}

void Sound::playGameOverSound(bool isMuted) {
    if (!isMuted && gameOverSound) Mix_PlayChannel(-1, gameOverSound, 0);
}
