#pragma once

#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_video.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static Mix_Chunk* g_sound_laser_l;
static Mix_Chunk* g_sound_laser_r;
static Mix_Chunk* g_sound_bullet;
static Mix_Chunk* g_sound_exp_player;
static Mix_Chunk* g_sound_exp_threats;
static Mix_Chunk* g_sound_play;
static Mix_Chunk* g_sound_menu;
static Mix_Chunk* g_sound_gameover;
static Mix_Chunk* g_sound_gamewin;


//Man hinh
const int FRAME_PER_SECOND = 200;
const int SCREEN_WIDTH = 1000;// chieu rong
const int SCREEN_HEIGHT = 720;//chieu cao
const int SCREEN_BPP = 32;//pixel
const int NUM_MAX_THREATS = 5;//số lượng máy bay
const double PI =3.141592653589793238462643383279;

int RandomNumber(int min, int max);

namespace SDL_Common
{
	bool check_overlap(const SDL_Rect& object1, const SDL_Rect& object2);
}

#endif // COMMON_FUNCTION_H



