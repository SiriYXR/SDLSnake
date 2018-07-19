#include "SIRI_Music.h"

namespace siri {

	int SIRI_BaseMixSound::MixNUM = 0;

	SIRI_BaseMixSound::SIRI_BaseMixSound()
	{
		if (MixNUM == 0)
		{
			if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
			{
				throw std::runtime_error("Mix_Open ERROR");
				exit(-1);
			}
		}
		MixNUM++;
	}

	SIRI_BaseMixSound::~SIRI_BaseMixSound()
	{
		MixNUM--;
		if (MixNUM == 0)
		{
			Mix_CloseAudio();
		}
	}

	SIRI_EffectSound::SIRI_EffectSound(const std::string & sound_fileName)
	{
		sound = Mix_LoadWAV(sound_fileName.c_str());
		if (sound == 0)
		{
			throw std::runtime_error(sound_fileName + ":load failed!");
		}
	}

	SIRI_EffectSound::~SIRI_EffectSound()
	{
		Mix_FreeChunk(sound);
	}

	void SIRI_EffectSound::play() const
	{
		if (Mix_PlayChannel(-1, sound, 0) == -1)
		{
			throw std::runtime_error("Mix_PlayChannel() ERROR");
		}
	}

	SIRI_MusicSound::SIRI_MusicSound(const std::string & music_fileName)
	{
		music = Mix_LoadMUS(music_fileName.c_str());
		if (music == 0)
		{
			throw std::runtime_error(music_fileName + ":load failed!");
		}
	}

	SIRI_MusicSound::~SIRI_MusicSound()
	{
		Mix_FreeMusic(music);
	}

	void SIRI_MusicSound::play() const
	{
		if (Mix_PlayingMusic() == false)
		{
			if (Mix_PlayMusic(music, 1) == -1)
			{
				throw std::runtime_error("Mix_PlayMusic() ERROR");
			}
		}
		else
		{
			if (Mix_PausedMusic() == true)
			{
				Mix_ResumeMusic();
			}
			else
			{
				Mix_PauseMusic();
			}
		}
	}

	void SIRI_MusicSound::stop() const
	{
		Mix_HaltMusic();
	}

	//=================================
	SIRI_Music::SIRI_Music()
	{
		eat = new SIRI_EffectSound("data/music/EAT.wav");
		dead = new SIRI_EffectSound("data/music/DEAD.wav");
		click = new SIRI_EffectSound("data/music/SWITCH.wav");
	}


	SIRI_Music::~SIRI_Music()
	{

	}
}