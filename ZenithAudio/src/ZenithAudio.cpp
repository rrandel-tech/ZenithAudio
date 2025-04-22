#include "ZenithAudio.hpp"

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

#include <iostream>

#define ZN_LOG(x) std::cout << "[Zenith Audio]  " << x << std::endl

namespace Zenith {

	bool Audio::s_DebugLog = true;

	static ma_engine s_Engine;
	static ma_decoder s_Decoder;

	void Audio::Init()
	{
		ma_result result;

		result = ma_engine_init(nullptr, &s_Engine);
		if (result != MA_SUCCESS) {
			std::cerr << "Failed to initialize miniaudio engine." << std::endl;
			return;
		}

		if (s_DebugLog) {
			ZN_LOG("Miniaudio engine initialized.");
		}
	}

	AudioSource Audio::LoadAudioSource(const std::string& filename)
	{
		AudioSource source;

		ma_result result;
		ma_sound* sound = new ma_sound;

		result = ma_sound_init_from_file(&s_Engine, filename.c_str(), MA_SOUND_FLAG_STREAM, nullptr, nullptr, sound);

		if (result != MA_SUCCESS) {
			std::cerr << "Failed to load audio file: " << filename << " | Error code: " << result << std::endl;
			delete sound;
			return source;
		}

		source.internalData = sound;
		source.loaded = true;

		if (s_DebugLog) {
			ZN_LOG("Streamed audio file: " << filename);
		}

		return source;
	}

	void Audio::Play(AudioSource& audioSource)
	{
		if (audioSource.loaded) {
			ma_sound* sound = static_cast<ma_sound*>(audioSource.internalData);
			ma_result result = ma_sound_start(sound);
			if (result != MA_SUCCESS) {
				std::cerr << "Failed to play audio." << std::endl;
			}
		}
	}

	bool Audio::IsPlaying(AudioSource& source)
	{
		if (!source.loaded) return false;
		ma_sound* sound = static_cast<ma_sound*>(source.internalData);
		return ma_sound_is_playing(sound);
	}

	void Audio::SetDebugLogging(bool log)
	{
		s_DebugLog = log;
	}

	void Audio::Shutdown()
	{
		ma_engine_uninit(&s_Engine);
		ZN_LOG("Miniaudio engine shut down.");
	}

	std::pair<uint32_t, uint32_t> AudioSource::GetLengthMinutesAndSeconds() const
	{
		uint32_t mins = static_cast<uint32_t>(length / 60);
		uint32_t secs = static_cast<uint32_t>(length) % 60;
		return { mins, secs };
	}
}
