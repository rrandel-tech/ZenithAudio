#pragma once

#include <string>
#include <iostream>
#include <utility>

namespace Zenith {

	struct AudioSource
	{
		void* internalData;
		bool loaded;
		float length;

		AudioSource() : internalData(nullptr), loaded(false), length(0) {}

		std::pair<uint32_t, uint32_t> GetLengthMinutesAndSeconds() const;

		friend class Audio;
	};

	class Audio
	{
	public:
		static void Init();
		static void Shutdown();

		static AudioSource LoadAudioSource(const std::string& filename);

		static void Play(AudioSource& audioSource);
		static bool IsPlaying(AudioSource& source);

		static void SetDebugLogging(bool log);

	private:
		static bool s_DebugLog;
	};

}