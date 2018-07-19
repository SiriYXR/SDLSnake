#pragma once
#include"SIRI_GUI.h"

using namespace siri;

//窗口尺寸
#define Win_L 780
#define Win_H 540

//音频文件路径
#define MU_EAT "data/music/EAT.wav"
#define MU_DEAD "data/music/DEAD.wav"
#define MU_SWITCH "data/music/SWITCH.wav"

//字体文件路径
#define Font_kaiti "data/font/simkai.ttf"

//分数记录文件路径
#define ScoreFile "data/score/score.txt"

bool mainloop(SIRI_Window *win);
bool choiceloop(SIRI_Window *win);
bool gameloop(SIRI_Window *win, int mod);
bool aboutusloop(SIRI_Window *win);

void openVideo(SIRI_Window *win);
void endVideo(SIRI_Window *win);

void saveScore(string file,int score);//存储分数
int readScore(string file);//读取分数
