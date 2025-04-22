#pragma once

#include <string>
#include <iostream>
#include <utility>

namespace Zenith {

	struct AudioSourceInternal;

	struct AudioSource {
		AudioSourceInternal* data = nullptr;
		bool loaded = false;

		std::pair<uint32_t, uint32_t> GetLengthMinutesAndSeconds() const;
	};

	class Audio {
	public:
		static void Init();
		static void Shutdown();

		static AudioSource LoadAudioSource(const std::string& filepath);
		static bool IsPlaying(AudioSource& source);
		static void Play(AudioSource& source);
		static void Free(AudioSource& source);

		static void SetDebugLogging(bool enable);

	private:
		static bool s_DebugLog;
	};

}