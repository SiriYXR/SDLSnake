#pragma once

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"SDL2_mixer.lib")

#include "SDL.h"
#include "SDL_mixer.h"

#include <string>
#include <stdexcept>

namespace siri {

	//*******************************
	//class BaseMixSound
	class SIRI_BaseMixSound
	{
	private:
		static int MixNUM;
	protected:
		SIRI_BaseMixSound();
	public:
		virtual ~SIRI_BaseMixSound();
	};
	//*******************************



	//*******************************
	//class EffectSound
	class SIRI_EffectSound : public SIRI_BaseMixSound
	{
	private:
		Mix_Chunk* sound;
	public:
		SIRI_EffectSound(const std::string& sound_fileName);
		~SIRI_EffectSound();
		void play() const;
	};

	//*******************************



	//*******************************
	//class MusicSound
	class SIRI_MusicSound : public SIRI_BaseMixSound
	{
	private:
		Mix_Music* music;
	public:
		SIRI_MusicSound(const std::string& music_fileName);
		~SIRI_MusicSound();
		void play() const;
		void stop() const;
	};
	//*******************************


	//*******************************
	//class Music
	class SIRI_Music
	{
	public:
		SIRI_Music();
		~SIRI_Music();

		SIRI_EffectSound* eat;
		SIRI_EffectSound* dead;
		SIRI_EffectSound* click;
	};
}