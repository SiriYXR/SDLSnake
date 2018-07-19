#pragma once
#include "SIRI_Rect.h"

#include <stdexcept>
#include <string>

namespace siri {

	//通过file路径向renderer渲染器加载Texture纹理资源

	/**
	*  Loads an image directly to texture using SDL_image's
	*  built in function IMG_LoadTexture
	*  @param file The image file to load
	*  @return SDL_Texture* to the loaded texture
	*/
	SDL_Texture * LoadTexture(SDL_Renderer* renderer,const std::string & file);

	//释放Texture纹理资源
	void DelTexture(SDL_Texture* image);

	//获取Texture纹理的Size
	SIRI_Size& GetTextureSize(SDL_Texture* image);

	//向renderer渲染器绘制 SDL_Texture

	/**
	*  Draw a SDL_Texture to the screen at dstRect with various other options
	*  @param tex The SDL_Texture to draw
	*  @param dstRect The destination position and width/height to draw the texture with
	*  @param clip The clip to apply to the image, if desired
	*  @param angle The rotation angle to apply to the texture, default is 0
	*  @param xPivot The x coordinate of the pivot, relative to (0, 0) being center of dstRect
	*  @param yPivot The y coordinate of the pivot, relative to (0, 0) being center of dstRect
	*  @param flip The flip to apply to the image, default is none
	*/
	void Draw(SDL_Renderer* renderer, SDL_Texture *tex, SDL_Rect &dstRect, SDL_Rect *clip = NULL, float angle = 0.0, int xPivot = 0, int yPivot = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	void Draw(SDL_Renderer* renderer, SDL_Texture *tex, int x, int y);

	void DrawWithAlpha(SDL_Renderer* renderer, SDL_Texture *tex, int x, int y,int alpha);

	//向renderer渲染器输出字体

	/**
	*  Generate a texture containing the message we want to display
	*  @param message The message we want to display
	*  @param fontFile The font we want to use to render the text
	*  @param color The color we want the text to be
	*  @param fontSize The size we want the font to be
	*  @return An SDL_Texture* to the rendered message
	*/
	SDL_Texture* RenderText(SDL_Renderer* renderer, const std::string &message, const std::string &fontFile, int fontSize, SDL_Color color = { 255,255,255 });

	void RenderText(SDL_Renderer* renderer, const std::string &message, const std::string &fontFile, int x, int y, int fontSize, SDL_Color color = { 255,255,255 });

}