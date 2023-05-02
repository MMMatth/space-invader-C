#include "../include/sound.h"

void init_sounds_systeme(){
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_AllocateChannels(32);
    Mix_VolumeMusic(SOUND_VOLUME % MIX_MAX_VOLUME); // on fait % pour que le volume soit entre 0 et MIX_MAX_VOLUME
    Mix_Volume(-1, MUSIC_VOLUME % MIX_MAX_VOLUME); // on fait % pour que le volume soit entre 0 et MIX_MAX_VOLUME
}

void init_sounds(sounds_t * sounds){
    sounds->laser = Mix_LoadWAV("assets/sounds/blaster.wav");
    sounds->explosion = Mix_LoadWAV("assets/sounds/blaster.wav");
    sounds->music = Mix_LoadMUS("assets/sounds/music.mp3");
}

void clean_sound(){
    Mix_CloseAudio();
}

void play_sound(Mix_Chunk *sound, int channel, int loop){
    Mix_PlayChannel(channel, sound, loop);
}

void play_music(Mix_Music *music, int loop){
    Mix_PlayMusic(music, loop);
}

void pause_music(){
    Mix_PauseMusic();
}

void resume_music(){
    Mix_ResumeMusic();
}

void stop_music(){
    Mix_HaltMusic();
}

void stop_channel(int channel){
    Mix_HaltChannel(channel);
}

void set_volume(int channel, int volume){
    Mix_Volume(channel, volume);
}

void fade_out_music(int ms){
    Mix_FadeOutMusic(ms);
}