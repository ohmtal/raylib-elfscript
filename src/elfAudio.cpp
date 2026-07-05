//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------

#include "elfResource.h"
#include <console/console.h>
#include "console/engineAPI.h"
#include "ConsoleTypes.h"


using namespace ElfResource;

//------------------------------------------------------------------------------------
// Audio Loading and Playing Functions (Module: audio)
//------------------------------------------------------------------------------------
// typedef void (*AudioCallback)(void *bufferData, unsigned int frames);
//
//------------------------------------------------------------------------------------
// Audio device management functions
//------------------------------------------------------------------------------------
// RLAPI void InitAudioDevice(void);                                     // Initialize audio device and context
DefineEngineFunction( InitAudioDevice, void, (), , "Initialize audio device and context") {
    InitAudioDevice();
}

// RLAPI void CloseAudioDevice(void);                                    // Close the audio device and context
DefineEngineFunction( CloseAudioDevice, void, (), , "Close the audio device and context") {
    CloseAudioDevice();
}

// RLAPI bool IsAudioDeviceReady(void);                                  // Check if audio device has been initialized successfully
DefineEngineFunction( IsAudioDeviceReady, bool, (), , "Check if audio device has been initialized successfully") {
    return IsAudioDeviceReady();
}

// RLAPI void SetMasterVolume(float volume);                             // Set master volume (listener)
DefineEngineFunction( SetMasterVolume, void, (float volume), , "Set master volume (listener), value between 0.0 and 1.0") {
    SetMasterVolume(volume);
}

// RLAPI float GetMasterVolume(void);                                    // Get master volume (listener)
DefineEngineFunction( GetMasterVolume, float, (), , "Get master volume (listener)") {
    return GetMasterVolume();
}
//------------------------------------------------------------------------------------
// Wave/Sound loading/unloading functions
//------------------------------------------------------------------------------------

// RLAPI Wave LoadWave(const char *fileName);                            // Load wave data from file
DefineEngineFunction( LoadWave, S32, (String fileName), , "Load wave data from file and return WaveID") {
    Wave wave = LoadWave(fileName.c_str());
    if (!IsWaveValid(wave)) return 0;
    return WaveMap.add(wave);
}

// RLAPI bool IsWaveValid(Wave wave);                                    // Check if wave data is valid
DefineEngineFunction( IsWaveValid, bool, (S32 waveId), , "Check if wave data is valid") {
    Wave* wave = WaveMap.get(waveId);
    if (!wave) return false;
    return IsWaveValid(*wave);
}

// RLAPI Sound LoadSound(const char *fileName);                          // Load sound from file
DefineEngineFunction( LoadSound, S32, (String fileName), , "Load sound from file and return SoundID") {
    Sound sound = LoadSound(fileName.c_str());
    if (!IsSoundValid(sound)) return 0;
    return SoundMap.add(sound);
}

// RLAPI Sound LoadSoundFromWave(Wave wave);                             // Load sound from wave data
DefineEngineFunction( LoadSoundFromWave, S32, (S32 waveId), , "Load sound from wave data and return SoundID") {
    Wave* wave = WaveMap.get(waveId);
    if (!wave) return 0;

    Sound sound = LoadSoundFromWave(*wave);
    if (!IsSoundValid(sound)) return 0;
    return SoundMap.add(sound);
}

// RLAPI Sound LoadSoundAlias(Sound source);                             // Load sound alias
DefineEngineFunction( LoadSoundAlias, S32, (S32 sourceSoundId), , "Load sound alias (shares sample data but can play independently) and return a new SoundID") {
    Sound* source = SoundMap.get(sourceSoundId);
    if (!source) return 0;

    Sound alias = LoadSoundAlias(*source);
    if (!IsSoundValid(alias)) return 0;
    return SoundMap.add(alias);
}

// RLAPI bool IsSoundValid(Sound sound);                                 // Check if a sound is valid
DefineEngineFunction( IsSoundValid, bool, (S32 soundId), , "Check if a sound is valid") {
    Sound* sound = SoundMap.get(soundId);
    if (!sound) return false;
    return IsSoundValid(*sound);
}

// RLAPI void UnloadWave(Wave wave);                                     // Unload wave data
DefineEngineFunction( UnloadWave, void, (S32 waveId), , "Unload wave data from memory") {
    WaveMap.remove(waveId);
}

// RLAPI void UnloadSound(Sound sound);                                  // Unload sound
DefineEngineFunction( UnloadSound, void, (S32 soundId), , "Unload sound from memory") {
    SoundMap.remove(soundId);
}

// RLAPI void UnloadSoundAlias(Sound alias);                             // Unload sound alias
DefineEngineFunction( UnloadSoundAlias, void, (S32 aliasSoundId), , "Unload sound alias") {
    Sound* alias = SoundMap.get(aliasSoundId);
    if (!alias) return;


    UnloadSoundAlias(*alias);

    // do not call UnloadSound here ....
    SoundMap.mMap.erase(aliasSoundId);

}

// RLAPI bool ExportWave(Wave wave, const char *fileName);               // Export wave data to file
DefineEngineFunction( ExportWave, bool, (S32 waveId, String fileName), , "Export wave data to file (.wav), returns true on success") {
    Wave* wave = WaveMap.get(waveId);
    if (!wave) return false;
    return ExportWave(*wave, fileName.c_str());
}

// RLAPI bool ExportWaveAsCode(Wave wave, const char *fileName);         // Export wave sample data to code (.h)
DefineEngineFunction( ExportWaveAsCode, bool, (S32 waveId, String fileName), , "Export wave sample data to code (.h), returns true on success") {
    Wave* wave = WaveMap.get(waveId);
    if (!wave) return false;
    return ExportWaveAsCode(*wave, fileName.c_str());
}

//------------------------------------------------------------------------------------
// Wave/Sound management functions
//------------------------------------------------------------------------------------

// RLAPI void PlaySound(Sound sound);                                    // Play a sound
DefineEngineFunction( PlaySound, void, (S32 soundId), , "Play a sound using its SoundID") {
    Sound* sound = SoundMap.get(soundId);
    if (!sound) return;
    PlaySound(*sound);
}

// RLAPI void StopSound(Sound sound);                                    // Stop playing a sound
DefineEngineFunction( StopSound, void, (S32 soundId), , "Stop playing a sound") {
    Sound* sound = SoundMap.get(soundId);
    if (!sound) return;
    StopSound(*sound);
}

// RLAPI void PauseSound(Sound sound);                                   // Pause a sound
DefineEngineFunction( PauseSound, void, (S32 soundId), , "Pause a sound") {
    Sound* sound = SoundMap.get(soundId);
    if (!sound) return;
    PauseSound(*sound);
}

// RLAPI void ResumeSound(Sound sound);                                  // Resume a paused sound
DefineEngineFunction( ResumeSound, void, (S32 soundId), , "Resume a paused sound") {
    Sound* sound = SoundMap.get(soundId);
    if (!sound) return;
    ResumeSound(*sound);
}

// RLAPI bool IsSoundPlaying(Sound sound);                               // Check if a sound is currently playing
DefineEngineFunction( IsSoundPlaying, bool, (S32 soundId), , "Check if a sound is currently playing") {
    Sound* sound = SoundMap.get(soundId);
    if (!sound) return false;
    return IsSoundPlaying(*sound);
}

// RLAPI void SetSoundVolume(Sound sound, float volume);                 // Set volume for a sound
DefineEngineFunction( SetSoundVolume, void, (S32 soundId, float volume), , "Set volume for a sound (0.0 to 1.0)") {
    Sound* sound = SoundMap.get(soundId);
    if (!sound) return;
    SetSoundVolume(*sound, volume);
}

// RLAPI void SetSoundPitch(Sound sound, float pitch);                   // Set pitch for a sound
DefineEngineFunction( SetSoundPitch, void, (S32 soundId, float pitch), , "Set pitch/speed for a sound (1.0 is base)") {
    Sound* sound = SoundMap.get(soundId);
    if (!sound) return;
    SetSoundPitch(*sound, pitch);
}

// RLAPI void SetSoundPan(Sound sound, float pan);                       // Set pan for a sound
DefineEngineFunction( SetSoundPan, void, (S32 soundId, float pan), , "Set pan for a sound (-1.0 left, 0.0 center, 1.0 right)") {
    Sound* sound = SoundMap.get(soundId);
    if (!sound) return;
    SetSoundPan(*sound, pan);
}

// RLAPI Wave WaveCopy(Wave wave);                                       // Copy a wave to a new wave
DefineEngineFunction( WaveCopy, S32, (S32 waveId), , "Copy a wave to a new wave and return WaveID") {
    Wave* wave = WaveMap.get(waveId);
    if (!wave) return 0;
    Wave newWave = WaveCopy(*wave);
    return WaveMap.add(newWave);
}

// RLAPI void WaveCrop(Wave *wave, int initFrame, int finalFrame);       // Crop a wave to defined frames range
DefineEngineFunction( WaveCrop, void, (S32 waveId, int initFrame, int finalFrame), , "Crop a wave to defined frames range") {
    Wave* wave = WaveMap.get(waveId);
    if (!wave) return;
    WaveCrop(wave, initFrame, finalFrame);
}

// RLAPI void WaveFormat(Wave *wave, int sampleRate, int sampleSize, int channels); // Convert wave data
DefineEngineFunction( WaveFormat, void, (S32 waveId, int sampleRate, int sampleSize, int channels), , "Convert wave data to desired format") {
    Wave* wave = WaveMap.get(waveId);
    if (!wave) return;
    WaveFormat(wave, sampleRate, sampleSize, channels);
}
//------------------------------------------------------------------------------------
// Music management functions
//------------------------------------------------------------------------------------
// RLAPI Music LoadMusicStream(const char *fileName);                    // Load music stream from file
DefineEngineFunction( LoadMusicStream, S32, (String fileName), , "Load music stream from file and return MusicID") {
    Music music = LoadMusicStream(fileName.c_str());
    if (!IsMusicValid(music)) return 0;
    return MusicMap.add(music);
}

// RLAPI bool IsMusicValid(Music music);                                 // Check if a music stream is valid
DefineEngineFunction( IsMusicValid, bool, (S32 musicId), , "Check if a music stream is valid") {
    Music* music = MusicMap.get(musicId);
    if (!music) return false;
    return IsMusicValid(*music);
}

// RLAPI void UnloadMusicStream(Music music);                            // Unload music stream
DefineEngineFunction( UnloadMusicStream, void, (S32 musicId), , "Unload music stream from VRAM and RAM") {
    MusicMap.remove(musicId);
}

// RLAPI void PlayMusicStream(Music music);                              // Start music playing
DefineEngineFunction( PlayMusicStream, void, (S32 musicId), , "Start playing a music stream") {
    Music* music = MusicMap.get(musicId);
    if (!music) {
        Con::errorf("PlayMusicStream failed to get music by id:%d", musicId);
        return;
    }
    PlayMusicStream(*music);
}

// RLAPI bool IsMusicStreamPlaying(Music music);                         // Check if music is playing
DefineEngineFunction( IsMusicStreamPlaying, bool, (S32 musicId), , "Check if music is currently playing") {
    Music* music = MusicMap.get(musicId);
    if (!music) return false;
    return IsMusicStreamPlaying(*music);
}

// RLAPI void UpdateMusicStream(Music music);                            // Update buffers for music streaming
DefineEngineFunction( UpdateMusicStream, void, (S32 musicId), , "Update buffers for music streaming (MUST be called every frame!)") {
    Music* music = MusicMap.get(musicId);
    if (!music) return;
    UpdateMusicStream(*music);
}

// RLAPI void StopMusicStream(Music music);                              // Stop music playing
DefineEngineFunction( StopMusicStream, void, (S32 musicId), , "Stop music playing") {
    Music* music = MusicMap.get(musicId);
    if (!music) return;
    StopMusicStream(*music);
}

// RLAPI void PauseMusicStream(Music music);                             // Pause music playing
DefineEngineFunction( PauseMusicStream, void, (S32 musicId), , "Pause music playing") {
    Music* music = MusicMap.get(musicId);
    if (!music) return;
    PauseMusicStream(*music);
}

// RLAPI void ResumeMusicStream(Music music);                            // Resume playing paused music
DefineEngineFunction( ResumeMusicStream, void, (S32 musicId), , "Resume playing paused music") {
    Music* music = MusicMap.get(musicId);
    if (!music) return;
    ResumeMusicStream(*music);
}

// RLAPI void SeekMusicStream(Music music, float position);              // Seek music to a position (in seconds)
DefineEngineFunction( SeekMusicStream, void, (S32 musicId, float position), , "Seek music to a specific position in seconds") {
    Music* music = MusicMap.get(musicId);
    if (!music) return;
    SeekMusicStream(*music, position);
}

// RLAPI void SetMusicVolume(Music music, float volume);                 // Set volume for music (1.0 is max level)
DefineEngineFunction( SetMusicVolume, void, (S32 musicId, float volume), , "Set volume for music stream (0.0 to 1.0)") {
    Music* music = MusicMap.get(musicId);
    if (!music) return;
    SetMusicVolume(*music, volume);
}

// RLAPI void SetMusicPitch(Music music, float pitch);                   // Set pitch for music (1.0 is base level)
DefineEngineFunction( SetMusicPitch, void, (S32 musicId, float pitch), , "Set pitch/speed for music stream") {
    Music* music = MusicMap.get(musicId);
    if (!music) return;
    SetMusicPitch(*music, pitch);
}

// RLAPI void SetMusicPan(Music music, float pan);                       // Set pan for music (-1.0 left, 0.0 center, 1.0 right)
DefineEngineFunction( SetMusicPan, void, (S32 musicId, float pan), , "Set pan for music stream (-1.0 left, 0.0 center, 1.0 right)") {
    Music* music = MusicMap.get(musicId);
    if (!music) return;
    SetMusicPan(*music, pan);
}

// RLAPI float GetMusicTimeLength(Music music);                          // Get music time length (in seconds)
DefineEngineFunction( GetMusicTimeLength, float, (S32 musicId), , "Get total music time length in seconds") {
    Music* music = MusicMap.get(musicId);
    if (!music) return 0.0f;
    return GetMusicTimeLength(*music);
}

// RLAPI float GetMusicTimePlayed(Music music);                          // Get current music time played (in seconds)
DefineEngineFunction( GetMusicTimePlayed, float, (S32 musicId), , "Get current music time played in seconds") {
    Music* music = MusicMap.get(musicId);
    if (!music) return 0.0f;
    return GetMusicTimePlayed(*music);
}
//------------------------------------------------------------------------------------
// AudioStream management functions NOTE: most not implemented!
//------------------------------------------------------------------------------------
// RLAPI void SetAudioStreamBufferSizeDefault(int size); // Default size for new audio streams
DefineEngineFunction( SetAudioStreamBufferSizeDefault, void, (int size), , "Set default buffer size for new audio streams (in samples)") {
    SetAudioStreamBufferSizeDefault(size);
}

// RLAPI AudioStream LoadAudioStream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels); // Load audio stream (to stream raw audio pcm data)
// RLAPI bool IsAudioStreamValid(AudioStream stream);                    // Check if an audio stream is valid (buffers initialized)
// RLAPI void UnloadAudioStream(AudioStream stream);                     // Unload audio stream and free memory
// RLAPI void UpdateAudioStream(AudioStream stream, const void *data, int frameCount); // Update audio stream buffers with data
// RLAPI bool IsAudioStreamProcessed(AudioStream stream);                // Check if any audio stream buffers requires refill
// RLAPI void PlayAudioStream(AudioStream stream);                       // Play audio stream
// RLAPI void PauseAudioStream(AudioStream stream);                      // Pause audio stream
// RLAPI void ResumeAudioStream(AudioStream stream);                     // Resume audio stream
// RLAPI bool IsAudioStreamPlaying(AudioStream stream);                  // Check if audio stream is playing
// RLAPI void StopAudioStream(AudioStream stream);                       // Stop audio stream
// RLAPI void SetAudioStreamVolume(AudioStream stream, float volume);    // Set volume for audio stream (1.0 is max level)
// RLAPI void SetAudioStreamPitch(AudioStream stream, float pitch);      // Set pitch for audio stream (1.0 is base level)
// RLAPI void SetAudioStreamPan(AudioStream stream, float pan);          // Set pan for audio stream (-1.0 left, 0.0 center, 1.0 right)
// RLAPI void SetAudioStreamBufferSizeDefault(int size);                 // Default size for new audio streams
// RLAPI void SetAudioStreamCallback(AudioStream stream, AudioCallback callback); // Audio thread callback to request new data
//
// RLAPI void AttachAudioStreamProcessor(AudioStream stream, AudioCallback processor); // Attach audio stream processor to stream, receives frames x 2 samples as 'float' (stereo)
// RLAPI void DetachAudioStreamProcessor(AudioStream stream, AudioCallback processor); // Detach audio stream processor from stream
//
// RLAPI void AttachAudioMixedProcessor(AudioCallback processor); // Attach audio stream processor to the entire audio pipeline, receives frames x 2 samples as 'float' (stereo)
// RLAPI void DetachAudioMixedProcessor(AudioCallback processor); // Detach audio stream processor from the entire audio pipeline

