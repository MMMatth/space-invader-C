#include "../include/sound.h"

void init_sounds_systeme(){
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024); // on ouvre le son
    Mix_AllocateChannels(32); // on alloue 32 canaux
    Mix_VolumeMusic(MUSIC_VOLUME % MIX_MAX_VOLUME / 10); // on fait % pour que le volume soit entre 0 et MIX_MAX_VOLUME
    Mix_Volume(-1, SOUND_VOLUME % MIX_MAX_VOLUME); // on fait % pour que le volume soit entre 0 et MIX_MAX_VOLUME
}

void init_sounds(sounds_t * sounds){
    sounds->laser = Mix_LoadWAV("assets/sounds/blaster.wav"); 
    sounds->explosion = Mix_LoadWAV("assets/sounds/blaster.wav");
    sounds->music = Mix_LoadMUS("assets/sounds/music.mp3");
    sounds->clic = Mix_LoadWAV("assets/sounds/clic.wav");
}

void clean_sound(){
    Mix_CloseAudio(); // on ferme le son
}

void play_sound(Mix_Chunk *sound, int channel, int loop){
    Mix_PlayChannel(channel, sound, loop); // on joue le son
}

void play_music(Mix_Music *music, int loop){
    Mix_PlayMusic(music, loop); // on joue la musique
}

void pause_music(){
    Mix_PauseMusic(); // on met en pause la musique
}

void resume_music(){
    Mix_ResumeMusic(); // on reprend la musique
}

void stop_music(){
    Mix_HaltMusic(); // on arrête la musique
} 

void stop_channel(int channel){
    Mix_HaltChannel(channel); // on arrête le son
}

void set_volume(int channel, int volume){
    Mix_Volume(channel, volume); // on règle le volume
}

void fade_out_music(int ms){
    Mix_FadeOutMusic(ms); // on fait un fondu sur la musique
}