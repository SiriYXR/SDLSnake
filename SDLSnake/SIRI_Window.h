#pragma once
#include "SIRI_Image.h"
#include "SIRI_Music.h"

namespace siri {

	class SIRI_Window
	{
	public:
		SIRI_Window();
		~SIRI_Window();

		//��ʼ�� SDL �� TTF, ����һ�����ں���Ⱦ��
		void Init(std::string title = "Window", const int SCREEN_WIDTH = 640, const int SCREEN_HEIGHT = 480);
		//�Ƴ� SDL �� TTF
		void Quit();
		//���� SDL_Texture
		void Draw(SDL_Texture *tex, SDL_Rect &dstRect, SDL_Rect *clip = NULL, float angle = 0.0, int xPivot = 0, int yPivot = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void Draw(SDL_Texture *tex, int x, int y);
		void DrawWithAlpha(SDL_Texture *tex, int x, int y, int alpha);

		//�������
		SDL_Texture* RenderText(const std::string &message, const std::string &fontFile, int fontSize, SDL_Color color = { 255,255,255 });
		void RenderText(const std::string &message, const std::string &fontFile, int x, int y, int fontSize, SDL_Color color = { 255,255,255 });
		//��մ�������
		void Clear();
		//��ʾ��������
		void Present();
		//��ô��ڵĳߴ�
		SDL_Rect& getSDLRect();
		SIRI_Size& getSize();

		SDL_Renderer* getRenderer();

	public:
		SIRI_Image *mImage;
		SIRI_Music *mMusic;

	private:
		SDL_Window *mWindow;
		SDL_Renderer *mRenderer;
		SDL_Rect mBox;

	};


}