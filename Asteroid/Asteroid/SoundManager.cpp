#include "SoundManager.h"

void SoundManager::InitializeSoundEffect()
{
	this->bufferLaser = new SoundBuffer;
	this->bufferLaser->loadFromFile("Laser.wav");
	this->soundLaser = new Sound(*this->bufferLaser);

	this->bufferDestroyBrick = new SoundBuffer;
	this->bufferDestroyBrick->loadFromFile("Explosion.wav");
	this->soundDestroyBrick = new Sound(*this->bufferDestroyBrick);

	this->bufferGameOver = new SoundBuffer;
	this->bufferGameOver->loadFromFile("GameOver.wav");
	this->soundGameOver = new Sound(*this->bufferGameOver);

	this->bufferThrust = new SoundBuffer;
	this->bufferThrust->loadFromFile("Thrust.wav");
	this->soundThrust = new Sound(*this->bufferThrust);

	this->bufferBGM = new SoundBuffer;
	this->bufferBGM->loadFromFile("BGM.wav");
	this->soundBGM = new Sound(*this->bufferBGM);

	this->bufferWin = new SoundBuffer;
	this->bufferWin->loadFromFile("winLevel.wav");
	this->soundWin = new Sound(*this->bufferWin);

	this->bufferPowerUp = new SoundBuffer;
	this->bufferPowerUp->loadFromFile("PowerUp.wav");
	this->soundPowerUp = new Sound(*this->bufferPowerUp);
}

void SoundManager::PlaySoundEffect(int index)
{
	switch (index)
	{
	case LaserSound:
		this->soundLaser->play();
		index = -1;
		break;
	case DestroySound:
		this->soundDestroyBrick->play();
		index = -1;
		break;
	case GameOverr:
		this->soundGameOver->play();
		index = -1;
		break;
	case ThrustSound:
		this->soundThrust->play();
		index = -1;
		break;
	case BGM:
		this->soundBGM->play();
		index = -1;
		break;
	case WinSound:
		this->soundWin->play();
		index = -1;
		break;
	case PowerUp:
		this->soundPowerUp->play();
		index = -1;
		break;
	}
}

bool SoundManager::CheckPlayStatus(int index)
{
	bool isPlaying;
	switch (index)
	{
	case LaserSound:
		if (this->soundLaser->getStatus() != SoundSource::Playing)
			return true;
		break;
	}
	return false;
}

SoundManager::~SoundManager()
{
	delete this->soundLaser;
	delete this->bufferLaser;
	delete this->bufferDestroyBrick;
	delete this->soundDestroyBrick;
	delete this->bufferGameOver;
	delete this->soundGameOver;
	delete this->bufferThrust;
	delete this->soundThrust;
	delete this->bufferBGM;
	delete this->soundBGM;
	delete this->bufferWin;
	delete this->soundWin;
	delete this->bufferPowerUp;
	delete this->soundPowerUp;
}