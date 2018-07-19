#pragma once
#include"SIRI_GUI.h"

using namespace siri;

//���ڳߴ�
#define Win_L 780
#define Win_H 540

//��Ƶ�ļ�·��
#define MU_EAT "data/music/EAT.wav"
#define MU_DEAD "data/music/DEAD.wav"
#define MU_SWITCH "data/music/SWITCH.wav"

//�����ļ�·��
#define Font_kaiti "data/font/simkai.ttf"

//������¼�ļ�·��
#define ScoreFile "data/score/score.txt"

bool mainloop(SIRI_Window *win);
bool choiceloop(SIRI_Window *win);
bool gameloop(SIRI_Window *win, int mod);
bool aboutusloop(SIRI_Window *win);

void openVideo(SIRI_Window *win);
void endVideo(SIRI_Window *win);

void saveScore(string file,int score);//�洢����
int readScore(string file);//��ȡ����
