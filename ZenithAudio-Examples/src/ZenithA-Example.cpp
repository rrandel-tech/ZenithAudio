#include <ZenithAudio.hpp>

#include <thread>
#include <chrono>

int main()
{
	while (true)
	{
		// Initialize the audio engine
		Zenith::Audio::Init();
		// Load audio source from file
		auto source = Zenith::AudioSource::LoadFromFile("Resources/Background_Music.mp3", false);
		// Play audio source
		Zenith::Audio::Play(source);

		auto frontLeftSource = Zenith::AudioSource::LoadFromFile("Resources/FrontLeft.ogg", true);
		frontLeftSource.SetGain(5.0f);
		frontLeftSource.SetPosition(-5.0f, 0.0f, 5.0f);
		Zenith::Audio::Play(frontLeftSource);

		auto frontRightSource = Zenith::AudioSource::LoadFromFile("Resources/FrontRight.ogg", true);
		frontRightSource.SetGain(5.0f);
		frontRightSource.SetPosition(5.0f, 0.0f, 5.0f);
		Zenith::Audio::Play(frontRightSource);

		auto movingSource = Zenith::AudioSource::LoadFromFile("Resources/Moving.ogg", true);
		movingSource.SetGain(5.0f);
		movingSource.SetPosition(5.0f, 0.0f, 5.0f);

		int sourceIndex = 0;
		const int sourceCount = 3;
		Zenith::AudioSource* sources[] = { &frontLeftSource, &frontRightSource, &movingSource };

		float xPosition = 5.0f;
		float playFrequency = 3.0f;
		float timer = playFrequency;

		std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
		while (true)
		{
			std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
			std::chrono::duration<float> delta = currentTime - lastTime;
			lastTime = currentTime;

			if (timer < 0.0f)
			{
				timer = playFrequency;
				Zenith::Audio::Play(*sources[sourceIndex++ % sourceCount]);
			}

			// Moving sound source
			if (sourceIndex == 3)
			{
				xPosition -= delta.count() * 2.0f;
				movingSource.SetPosition(xPosition, 0.0f, 5.0f);
			}
			else
			{
				xPosition = 5.0f;
			}

			timer -= delta.count();

			using namespace std::literals::chrono_literals;
			std::this_thread::sleep_for(5ms);
		}
	}
}