#include "ZenithAudio.hpp"

#include <thread>
#include <chrono>
#include <cstdlib>

int main()
{
	Zenith::Audio::Init();

	//auto audioSource = Zenith::Audio::LoadAudioSource("Resources/flacTest.flac");
	//auto audioSource = Zenith::Audio::LoadAudioSource("Resources/mp3Test.mp3");
	auto audioSource = Zenith::Audio::LoadAudioSource("Resources/Background_Music.wav");

	if (!audioSource.loaded) {
		std::cerr << "Failed to load the audio file." << std::endl;
		std::exit(-1);
	}

	Zenith::Audio::Play(audioSource);

	while (Zenith::Audio::IsPlaying(audioSource)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	Zenith::Audio::Shutdown();

	std::exit(0);
}
