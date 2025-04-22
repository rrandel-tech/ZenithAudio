# Zenith Audio

Zenith Audio is a lightweight audio library I developed, initially built on top of [OpenAL Soft](https://openal-soft.org/). As this is my first attempt at audio library development, it was an interesting challenge to build something from the ground up.

The library is still in its early stages, so expect it to be a bit bare-bones. As I continue development, I’ll be adding more features and functionality, and I'll keep this document updated to reflect the library’s limitations and improvements.

## Current Features

- Playback of `.wav`, `.mp3`, and `.flac` audio files

## Roadmap / TODO

- **Unload audio sources**: Proper management and unloading of audio resources
- **Audio streaming**: Ability to stream long audio files (e.g., background music)
- **Audio seeking**: Implement functionality for seeking within audio tracks
- **Listener API**: Provide a method to control listener positioning in 3D space
- **Audio effects**: Adding support for audio manipulation effects (reverb, filters, etc.)

## Example Usage

For a quick demonstration of Zenith Audio in action, check out the `ZenithAudio-Examples` project. The setup is straightforward and demonstrates basic playback functionality.

## Acknowledgements

- [OpenAL Soft](https://openal-soft.org/) – Audio backend for the library
- [minimp3](https://github.com/lieff/minimp3) – MP3 decoding library
- [libogg and Vorbis](https://www.xiph.org/) – Audio file formats

- [miniaudio.h](https://github.com/mackron/miniaudio) – Audio backend for the library
- [stb_vorbis.h](http://www.nothings.org/stb_vorbis/) – Ogg audio file loading
- [dr_wav.h](http://github.com/mackron/dr_libs) – WAV audio file loading
- [dr_mp3.h](https://github.com/mackron/dr_libs) – MP3 audio file loading
- [dr_flac.h](https://github.com/mackron/dr_libs) – FLAC audio file loading
