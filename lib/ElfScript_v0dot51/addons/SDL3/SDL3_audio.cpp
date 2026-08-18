//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// ELFSDL Audio - Only Wav - the sdl limit
//-----------------------------------------------------------------------------
#include "console/scriptPreprocessor.h"
#include "console/engineAPI.h"

#include "SDL3_audio.h"


namespace ElfSDL3
{

namespace Audio {
    //--------------------------------------------------------------------------
    SDL_AudioDeviceID AudioDevice = 0;

    bool isInitialized() { return AudioDevice != 0 ;}
    //--------------------------------------------------------------------------
    bool bindStream(SDL_AudioStream* stream)
    {
        if (!isInitialized() || !stream) return false;
        SDL_AudioDeviceID currentDevice = SDL_GetAudioStreamDevice(stream);

        if (currentDevice == AudioDevice) {
            return true;
        }
        if (currentDevice != 0) {
            SDL_UnbindAudioStream(stream);
        }
        return SDL_BindAudioStream(AudioDevice, stream);
    }
    //--------------------------------------------------------------------------
    bool unBindStream(SDL_AudioStream* stream)
    {
        if (!isInitialized() || !stream) return false;
        SDL_UnbindAudioStream( stream);
        return (SDL_GetAudioStreamDevice(stream) == 0);
    }
    //--------------------------------------------------------------------------
    S32 loadWav(const char* fileName)
    {
        if (!isInitialized() || !fileName || dStrlen(fileName) == 0) return 0;


        WavData wavData;
        if (!SDL_LoadWAV(fileName, &wavData.spec, &wavData.buffer, &wavData.len)) {
            Con::errorf("Couldn't load Wavefile:%s file: %s", fileName, SDL_GetError());
            return 0;
        }
        wavData.stream = SDL_CreateAudioStream(&wavData.spec, nullptr);
        if (!wavData.stream ) {
            Con::errorf("Couldn't create audio stream: %s", SDL_GetError());
            return 0;
        }

        if (!bindStream(wavData.stream )) {
            SDL_Log("Failed to bind '%s' stream to device: %s", fileName, SDL_GetError());
            SDL_DestroyAudioStream(wavData.stream);
            SDL_free(wavData.buffer);
            return 0;
        }

        return WaveDataMap.add(wavData);
    }

    //--------------------------------------------------------------------------
    void UnloadWavData(WavData wavData) {
        if (wavData.stream) {
            unBindStream(wavData.stream);
            SDL_DestroyAudioStream(wavData.stream);
            wavData.stream = nullptr;
        }
        if (wavData.buffer) {
            SDL_free(wavData.buffer);
            wavData.buffer = nullptr;
        }
    }
    //--------------------------------------------------------------------------
    void SDLCALL MyAudioLoopCallback(void *userdata, SDL_AudioStream *stream, int additional_amount, int total_amount) {
        WavData* data = (WavData*)userdata;
        if (additional_amount > 0) {
            SDL_PutAudioStreamData(stream, data->buffer, data->len);
        }
    }
    //--------------------------------------------------------------------------
    bool setMasterVolume(float value){
        if (isInitialized()) {
            return SDL_SetAudioDeviceGain(AudioDevice, value);
        }
        return false;
    }
    float getMasterVolume(){
        return isInitialized() ? SDL_GetAudioDeviceGain(AudioDevice) : 1.0f;
    }
    //--------------------------------------------------------------------------
    bool play(WavData* data, float gain , bool loop ) {
        if (!isInitialized() || !data || !data->stream)  return false;
        SDL_ClearAudioStream(data->stream);
        SDL_SetAudioStreamGain(data->stream, gain);

        if (loop) {
            SDL_SetAudioStreamGetCallback(data->stream, MyAudioLoopCallback, data);
        } else {
            SDL_SetAudioStreamGetCallback(data->stream, nullptr, nullptr);
        }

        SDL_PutAudioStreamData(data->stream, data->buffer, data->len);
        SDL_ResumeAudioStreamDevice(data->stream);
        return true;
    }

    //--------------------------------------------------------------------------
    bool  stop(WavData* data) {
        if (!isInitialized() || !data || !data->stream) return false;
        SDL_SetAudioStreamGetCallback(data->stream, nullptr, nullptr);
        SDL_ClearAudioStream(data->stream);
        return true;
    }


    //--------------------------------------------------------------------------
    bool Init()
    {
        if (AudioDevice != 0) {
            return true;
        }
        AudioDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
        Con::infof("Audio_Init device id:%d.", AudioDevice);
        return  AudioDevice != 0;
    }

    void ShutDown()
    {
        Audio::WaveDataMap.clear();
    }

} //namespace Audio
// ========================== BINDINGS ====================================
DefineEngineFunction(Audio_Init, bool, (), , "Init Audio Device for playback") {
    return Audio::Init();
}
DefineEngineFunction(Audio_Shutdown, void, (), , "ShutDown Audio Device ") {
    Audio::ShutDown();
}

DefineEngineFunction(Audio_LoadWav, S32, (const char* filename), , "Load a Wave File.\n@return WavID") {
    return Audio::loadWav(filename);
}

DefineEngineFunction(Audio_UnLoadWav, S32, (S32 WavID), , "Unload a Wave Steam") {
    return Audio::WaveDataMap.remove(WavID);
}


DefineEngineFunction(Audio_Play, bool, (S32 WavID, F32 gain, bool loop),(1.0f, false) , "Play a Wave Stream.@param gain is the normalized volume") {
    Audio::WavData* wavData = Audio::WaveDataMap.get(WavID);
    if (!wavData) return false;
    return Audio::play(wavData, gain, loop);
}
DefineEngineFunction(Audio_Stop, bool, (S32 WavID), , "Stop a Wave Stream.") {
    Audio::WavData* wavData = Audio::WaveDataMap.get(WavID);
    if (!wavData) return false;
    return Audio::stop(wavData);
}

DefineEngineFunction(Audio_SetMasterVolume, bool, (F32 volume), , "set the volume for all streams") {
    return Audio::setMasterVolume(volume);
}
DefineEngineFunction(Audio_GetMasterVolume, F32, (), , "get the volume for all streams") {
    return Audio::getMasterVolume();
}

} //namespace










