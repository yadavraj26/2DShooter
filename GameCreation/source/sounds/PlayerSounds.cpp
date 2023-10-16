#pragma once
#include"../../include/sound/Audio.h"
//#include<iostream>

PlayerActionSound::PlayerActionSound()
{
	attack.loadFromFile("sound/sword-swing.flac");
	shout.loadFromFile("sound/Fire.ogg");
	playerSound.setBuffer(attack);
}

void PlayerActionSound::addAudio(std::string a[])
{
	for (int i =0; i<a->size(); i++)
	{

	}
}

void PlayerActionSound::playSound(AudioID audio)
{

	stopSound();
	switch (audio)
	{
	case AudioID::Shout:
		playerSound.setBuffer(shout);
		break;
	case AudioID::Attack:
		playerSound.setBuffer(attack);
		break;
	default:
		//std::cerr << "Audio Service does not match" << std::endl;
		return;
	}
	playerSound.play();
}

void PlayerActionSound::stopSound()
{
	playerSound.stop();
}

PlayerPickupSound::PlayerPickupSound()
{
	potionPickup.loadFromFile("sound/health-pickup.wav");
	playerSound.setBuffer(potionPickup);
}



void PlayerPickupSound::playSound(AudioID audio)
{
	playerSound.play();
}