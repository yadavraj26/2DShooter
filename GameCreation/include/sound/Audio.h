#pragma once
#include"SFML/Audio.hpp"

enum class AudioID
{
	UNDEFINED = -1,
	PotionPickup = 1,
	Shout = 2,
	Attack = 3
};

class Audio
{
public:
	~Audio() {}
	virtual void addAudio(std::string a[]) = 0;
	virtual void playSound(AudioID audioToPlay) = 0;

	virtual void stopSound() = 0;
};

class PlayerActionSound :public Audio
{
public:
	PlayerActionSound();
	~PlayerActionSound() {}
	void addAudio(std::string a[])override;
	void playSound(AudioID audioToPlay)override;
	void stopSound() override;
private:
	sf::Sound playerSound;
	sf::SoundBuffer shout, attack;
};

class PlayerPickupSound : public Audio
{
public:
	PlayerPickupSound();
	~PlayerPickupSound() {}
	void addAudio(std::string a[])override {}
	void playSound(AudioID audioToPlay)override;
	void stopSound()override {}

private:
	sf::Sound playerSound;
	sf::SoundBuffer potionPickup;
};

class NullAudio :public Audio
{
public:
	~NullAudio(){}
	void addAudio(std::string a[])override{}
	void playSound(AudioID audioToPlay)override{}
	void stopSound()override{}
};