#include "SIRI_Graphics.h"

#pragma comment(lib,"SDL2_image.lib")
#pragma comment(lib,"SDL2_ttf.lib")

#include "SDL_image.h"
#include "SDL_ttf.h"

namespace siri {

	SDL_Texture * LoadTexture(SDL_Renderer* renderer, const std::string & file)
	{
		SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
		if (texture == nullptr) {
			throw std::runtime_error("LoadTexture");
		}
		return texture;
	}

	void DelTexture(SDL_Texture * image)
	{
		SDL_DestroyTexture(image);
	}

	SIRI_Size& GetTextureSize(SDL_Texture * image)
	{
		int w;
		int h;
		SDL_QueryTexture(image, NULL, NULL, &w, &h);
		return SIRI_Size(w,h);
	}

	void Draw(SDL_Renderer * renderer, SDL_Texture * tex, SDL_Rect & dstRect, SDL_Rect * clip, float angle, int xPivot, int yPivot, SDL_RendererFlip flip)
	{
		//Convert pivot pos from relative to object's center to screen space
		xPivot += dstRect.w / 2;
		yPivot += dstRect.h / 2;
		//SDL expects an SDL_Point as the pivot location
		SDL_Point pivot = { xPivot, yPivot };
		//Draw the texture
		SDL_RenderCopyEx(renderer, tex, clip, &dstRect, angle, &pivot, flip);
	}

	void Draw(SDL_Renderer * renderer, SDL_Texture * tex, int x, int y)
	{
		SDL_Rect dstRect;
		dstRect.x = x;
		dstRect.y = y;
		SDL_QueryTexture(tex, NULL, NULL, &dstRect.w, &dstRect.h);
		SDL_RenderCopyEx(renderer, tex, NULL, &dstRect, 0.0, NULL, SDL_FLIP_NONE);
	}

	void DrawWithAlpha(SDL_Renderer * renderer, SDL_Texture * tex, int x, int y, int alpha)
	{
		if (alpha < 0)
			alpha = 0;
		if (alpha > 255)
			alpha = 255;
		SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(tex, alpha);
		Draw(renderer, tex, x, y);
	}

	SDL_Texture * RenderText(SDL_Renderer * renderer, const std::string & message, const std::string & fontFile, int fontSize, SDL_Color color)
	{
		//Open the font
		TTF_Font *font = nullptr;
		font = TTF_OpenFont(fontFile.c_str(), fontSize);
		if (font == nullptr)
			throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());

		//Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
		SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
		//Clean up unneeded stuff
		SDL_FreeSurface(surf);
		TTF_CloseFont(font);

		return texture;
	}

	void RenderText(SDL_Renderer * renderer, const std::string & message, const std::string & fontFile, int x, int y, int fontSize, SDL_Color color)
	{
		SDL_Texture *texture = RenderText(renderer,message, fontFile, fontSize, color);
		Draw(renderer,texture, x, y);
		SDL_DestroyTexture(texture);
	}

}