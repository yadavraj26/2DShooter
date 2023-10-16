#pragma once
#include"../../include/sound/Audio.h"
#include"Locator.h"
class AudioManager
{
public:
	AudioManager()
	{
		plA = std::make_shared<PlayerActionSound>();
		plP = std::make_shared<PlayerPickupSound>();
		nullAudio = std::make_shared<NullAudio>();

		Locator::registerAudioService(plA, AudioObjectID::PlayerAction);
		Locator::registerAudioService(plP, AudioObjectID::PlayerPickup);
	}
private:
	std::shared_ptr<PlayerActionSound> plA;
	std::shared_ptr<PlayerPickupSound> plP;
	std::shared_ptr<NullAudio> nullAudio;
};