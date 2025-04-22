#include "ZenithAudio.hpp"

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

#include <iostream>

#define ZN_LOG(x) std::cout << "[Zenith Audio]  " << x << std::endl

namespace Zenith {

	bool Audio::s_DebugLog = true;

	struct AudioSourceInternal {
		ma_decoder decoder;
		ma_device device;
	};

	void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
	{
		auto* internal = static_cast<AudioSourceInternal*>(pDevice->pUserData);
		if (!internal) return;

		ma_decoder_read_pcm_frames(&internal->decoder, pOutput, frameCount, NULL);
		(void)pInput;
	}

	void Audio::Init()
	{
		if (s_DebugLog) {
			ZN_LOG("ZenithAudio initialized using miniaudio low-level API.");
		}
	}

	AudioSource Audio::LoadAudioSource(const std::string& filename)
	{
		AudioSource source;
		auto* internal = new AudioSourceInternal;

		if (ma_decoder_init_file(filename.c_str(), nullptr, &internal->decoder) != MA_SUCCESS) {
			std::cerr << "Failed to load audio file: " << filename << std::endl;
			delete internal;
			return source;
		}

		ma_device_config config = ma_device_config_init(ma_device_type_playback);
		config.playback.format = internal->decoder.outputFormat;
		config.playback.channels = internal->decoder.outputChannels;
		config.sampleRate = internal->decoder.outputSampleRate;
		config.dataCallback = data_callback;
		config.pUserData = internal;

		if (ma_device_init(nullptr, &config, &internal->device) != MA_SUCCESS) {
			std::cerr << "Failed to initialize playback device." << std::endl;
			ma_decoder_uninit(&internal->decoder);
			delete internal;
			return source;
		}

		source.data = internal;
		source.loaded = true;

		if (s_DebugLog) {
			ZN_LOG("Loaded audio file: " << filename);
		}

		return source;
	}

	bool Audio::IsPlaying(AudioSource& source)
	{
		if (!source.loaded || !source.data)
			return false;

		return ma_device_is_started(&source.data->device);
	}

	void Audio::Play(AudioSource& source)
	{
		if (!source.loaded) return;
		ma_device_start(&source.data->device);
	}

	void Audio::Free(AudioSource& source)
	{
		if (!source.loaded) return;
		ma_device_uninit(&source.data->device);
		ma_decoder_uninit(&source.data->decoder);
		delete source.data;
		source.data = nullptr;
		source.loaded = false;

		if (s_DebugLog) {
			ZN_LOG("Audio source freed.");
		}
	}

	void Audio::Shutdown()
	{
		if (s_DebugLog) {
			ZN_LOG("Shutting down audio system...");
		}
	}

	std::pair<uint32_t, uint32_t> AudioSource::GetLengthMinutesAndSeconds() const
	{
		if (!loaded || !data) return { 0, 0 };

		ma_uint64 lengthFrames = 0;
		ma_decoder_get_length_in_pcm_frames(&data->decoder, &lengthFrames);
		ma_uint32 sampleRate = data->decoder.outputSampleRate;

		uint32_t totalSeconds = static_cast<uint32_t>(lengthFrames / sampleRate);
		return { totalSeconds / 60, totalSeconds % 60 };
	}

}
