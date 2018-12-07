#pragma once
#include "sfml.h"

#define LaserSound 0
#define DestroySound 1
#define GameOverr 2
#define ThrustSound 3
#define BGM 4
#define WinSound 5
#define PowerUp 6

using namespace sf;

class SoundManager
{
public:
	void InitializeSoundEffect();
	void PlaySoundEffect(int index);
	bool CheckPlayStatus(int index);

	~SoundManager();

	SoundBuffer* bufferLaser;
	Sound* soundLaser;

	SoundBuffer* bufferDestroyBrick;
	Sound* soundDestroyBrick;

	SoundBuffer* bufferGameOver;
	Sound* soundGameOver;

	SoundBuffer* bufferThrust;
	Sound* soundThrust;

	SoundBuffer* bufferBGM;
	Sound* soundBGM;

	SoundBuffer* bufferWin;
	Sound* soundWin;

	SoundBuffer* bufferPowerUp;
	Sound* soundPowerUp;
};