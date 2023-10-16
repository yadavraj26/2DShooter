#pragma once
#include<memory>

class Audio;

//Channel Type
enum class AudioObjectID
{
	PlayerAction=1,
	PlayerPickup=2,
	UNDEFINED=-1
};
class Locator
{
public:
	static void registerAudioService(std::shared_ptr<Audio> audioRef, AudioObjectID audioServiceType)
	{
		switch (audioServiceType)
		{
		case AudioObjectID::PlayerAction:
			plActionAudio = audioRef;
			break;
		case AudioObjectID::PlayerPickup:
			plPickupAudio = audioRef;
			break;
		case AudioObjectID::UNDEFINED:
			if (audioRef != nullptr)
				nullAudio = audioRef;
			break;
		}

	}
	static std::shared_ptr<Audio> getAudioService(AudioObjectID audioType)
	{
		switch (audioType)
		{
		case AudioObjectID::PlayerAction:
			
			return (plActionAudio!=nullptr)? plActionAudio:nullAudio;
		case AudioObjectID::PlayerPickup:
			return (plPickupAudio != nullptr) ? plPickupAudio : nullAudio;
		default:
			return  nullAudio;
		}
	}

private:
	static std::shared_ptr<Audio> plActionAudio;
	static std::shared_ptr<Audio> plPickupAudio;
	static std::shared_ptr<Audio> nullAudio;
};
