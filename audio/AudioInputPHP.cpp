//
// libtgvoip is free and unencumbered public domain software.
// For more information, see http://unlicense.org or the UNLICENSE file
// you should have received with this source code distribution.
//


#include "AudioInputPHP.h"
#include <stdio.h>
#include "../libtgvoip/logging.h"

using namespace tgvoip;
using namespace tgvoip::audio;


AudioInputPHP::AudioInputPHP(void* controller){
	wrapper = (VoIP *)((VoIPController*)controller)->implData;
}


AudioInputPHP::~AudioInputPHP(){

}


void AudioInputPHP::Configure(uint32_t sampleRate, uint32_t bitsPerSample, uint32_t channels) {
	wrapper->configureAudioInput((int32_t)sampleRate, (int32_t)bitsPerSample, (int32_t)channels);
}

void AudioInputPHP::Start(){
	if(running)
		return;
	running = true;
	wrapper->startInput();
}

void AudioInputPHP::Stop(){
	wrapper->stopInput();
	running = false;
}
bool AudioInputPHP::writeFrames(const char* data){
	if (running) {
		LOGE("STARTED");
		unsigned char buf[960*2];
		memcpy(buf, data, 960*2);
		InvokeCallback(buf, (size_t)960*2);
		delete buf;
		return true;
	} else {
		LOGE("NOT STARTED");
		return false;
	}/*
	if (!running) {
		return false;
	}*/
}
