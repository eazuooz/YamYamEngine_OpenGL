#include "AudioSystem.h"
#include <SDL/SDL_log.h>
#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include <vector>

unsigned int AudioSystem::sNextID = 0;

AudioSystem::AudioSystem(Game* game)
	:mGame(game)
	, mSystem(nullptr)
	, mLowLevelSystem(nullptr)
{

}

AudioSystem::~AudioSystem()
{
}

bool AudioSystem::Initialize()
{
	FMOD::Debug_Initialize(
		FMOD_DEBUG_LEVEL_ERROR,
		FMOD_DEBUG_MODE_TTY
	);

	FMOD_RESULT result;
	result = FMOD::Studio::System::create(&mSystem);
	if (result != FMOD_OK)
	{
		SDL_Log("Failed to create FMOD system: %s", FMOD_ErrorString(result));
		return false;
	}

	result = mSystem->initialize(
		512,
		FMOD_STUDIO_INIT_NORMAL,
		FMOD_INIT_NORMAL,
		nullptr
	);
	if (result != FMOD_OK)
	{
		SDL_Log("Failed to initialize FMOD system: %s", FMOD_ErrorString(result));
		return false;
	}

	mSystem->getLowLevelSystem(&mLowLevelSystem);

	LoadBank("Assets/Master Bank.strings.bank");
	LoadBank("Assets/Master Bank.bank");

	return true;
}

void AudioSystem::Shutdown()
{
	UnloadAllBank();
	if (mSystem)
	{
		mSystem->release();
	}
}

void AudioSystem::LoadBank(const std::string& name)
{
	if (mBanks.find(name) != mBanks.end())
	{
		return;
	}

	FMOD::Studio::Bank* bank = nullptr;
	FMOD_RESULT result = mSystem->loadBankFile(
		name.c_str(),
		FMOD_STUDIO_LOAD_BANK_NORMAL,
		&bank
	);

	const int maxPathLength = 512;
	if (result == FMOD_OK)
	{
		mBanks.emplace(name, bank);
		bank->loadSampleData();

		int numEvents = 0;
		bank->getEventCount(&numEvents);
		if (numEvents > 0)
		{
			std::vector<FMOD::Studio::EventDescription*> events(numEvents);
			bank->getEventList(events.data(), numEvents, &numEvents);
			char eventName[maxPathLength] = {};
			for (int i = 0; i < numEvents; i++)
			{
				FMOD::Studio::EventDescription* e = events[i];
				e->getPath(eventName, maxPathLength, nullptr);
				mEvents.emplace(eventName, e);
			}

			int numBuses = 0;
			bank->getBusCount(&numBuses);
			if (numBuses > 0)
			{
				std::vector<FMOD::Studio::Bus*> buses(numBuses);
				bank->getBusList(buses.data(), numBuses, &numBuses);
				char busName[512] = {};
				for (int i = 0; i < numBuses; i++)
				{
					FMOD::Studio::Bus* bus = buses[i];
					bus->getPath(busName, 512, nullptr);
					mBuses.emplace(busName, bus);
				}
			}
		}
	}
}

void AudioSystem::UnloadBank(const std::string& name)
{
	auto iter = mBanks.find(name);
	if (iter == mBanks.end())
	{
		return;
	}

	FMOD::Studio::Bank* bank = iter->second;
	int numEvents = 0;
	bank->getEventCount(&numEvents);
	if (numEvents > 0)
	{
		std::vector<FMOD::Studio::EventDescription*> events(numEvents);
		bank->getEventList(events.data(), numEvents, &numEvents);
		char eventName[512] = {};
		for (int i = 0; i < numEvents; i++)
		{
			FMOD::Studio::EventDescription* e = events[i];
			e->getPath(eventName, 512, nullptr);
			auto eventi = mEvents.find(eventName);
			if (eventi != mEvents.end())
			{
				mEvents.erase(eventi);
			}
		}
	}
	
	int numBuses = 0;
	bank->getBusCount(&numBuses);
	if (numBuses > 0)
	{
		std::vector<FMOD::Studio::Bus*> buses(numBuses);
		bank->getBusList(buses.data(), numBuses, &numBuses);
		char busName[512];
		for (int i = 0; i < numBuses; i++)
		{
			FMOD::Studio::Bus* bus = buses[i];
			bus->getPath(busName, 512, nullptr);
			auto busi = mBuses.find(busName);
			if (busi != mBuses.end())
			{
				mBuses.erase(busi);
			}
		}
	}

	bank->unloadSampleData();
	bank->unload();

	mBanks.erase(iter);
}

void AudioSystem::UnloadAllBank()
{
	for (auto& iter : mBanks)
	{
		iter.second->unloadSampleData();
		iter.second->unload();
	}
	mBanks.clear();
	mEvents.clear();
}

SoundEvent AudioSystem::PlayEvent(const std::string& name)
{
	unsigned int retID = 0;
	auto iter = mEvents.find(name);
	if (iter != mEvents.end())
	{
		FMOD::Studio::EventInstance* event = nullptr;
		iter->second->createInstance(&event);
		if (event)
		{
			event->start();
		
			sNextID++;
			retID = sNextID;
			mEventInstances.emplace(retID, event);
		}
	}

	return SoundEvent(this, retID);
}

void AudioSystem::Update(float deltaTime)
{
	std::vector<unsigned int> done;
	for (auto& iter : mEventInstances)
	{
		FMOD::Studio::EventInstance* e = iter.second;

		FMOD_STUDIO_PLAYBACK_STATE state;
		e->getPlaybackState(&state);
		if (state == FMOD_STUDIO_PLAYBACK_STOPPED)
		{
			e->release();
			done.emplace_back(iter.first);
		}
	}

	for (auto id : done)
	{
		mEventInstances.erase(id);
	}

	mSystem->update();
}

namespace
{
	FMOD_VECTOR VecToFMOD(const Vector3& in)
	{
		// Convert from our coordinates (+x forward, +y right, +z up)
		// to FMOD (+z forward, +x right, +y up)
		FMOD_VECTOR v;
		v.x = in.y;
		v.y = in.z;
		v.z = in.x;
		return v;
	}
}

void AudioSystem::SetListener(const Matrix4& viewMatrix)
{
	Matrix4 invView = viewMatrix;
	invView.Invert();
	FMOD_3D_ATTRIBUTES listener;
	listener.position = VecToFMOD(invView.GetTranslation());
	listener.forward = VecToFMOD(invView.GetZAxis());
	listener.up = VecToFMOD(invView.GetYAxis());
	listener.velocity = { 0.0f, 0.0f, 0.0f };

	mSystem->setListenerAttributes(0, &listener);
}

float AudioSystem::GetBusVolume(const std::string& name)
{
	float retVal = 0.0f;
	const auto iter = mBuses.find(name);
	if (iter != mBuses.end())
	{
		iter->second->getVolume(&retVal);
	}
	return retVal;
}

bool AudioSystem::GetBusPaused(const std::string& name) const
{
	bool retVal = false;
	const auto iter = mBuses.find(name);
	if (iter != mBuses.end())
	{
		iter->second->getPaused(&retVal);
	}
	return retVal;
}

void AudioSystem::SetBusVolume(const std::string& name, float volume)
{
	auto iter = mBuses.find(name);
	if (iter != mBuses.end())
	{
		iter->second->setVolume(volume);
	}
}

void AudioSystem::SetBusPaused(const std::string& name, bool pause)
{
	auto iter = mBuses.find(name);
	if (iter != mBuses.end())
	{
		iter->second->setPaused(pause);
	}
}

FMOD::Studio::EventInstance* AudioSystem::GetEventInstance(unsigned int id)
{
	FMOD::Studio::EventInstance* event = nullptr;
	auto iter = mEventInstances.find(id);
	if (iter != mEventInstances.end())
	{
		event = iter->second;
	}
	return event;
}
