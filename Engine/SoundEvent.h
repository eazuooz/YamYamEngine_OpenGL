#pragma once
#include <string>
#include "Math.h"


class SoundEvent
{
public:
	SoundEvent();

	bool IsValid();
	void ReStart();
	void Stop(bool allowFadeOut = true);
	
	void SetPaused(bool pause);
	void SetVolume(float value);
	void SetPitch(float value);
	void SetParameter(const std::string& name, float value);

	bool GetPaused() const;
	float GetVolume() const;
	float GetPitch() const;
	float GetParameter(const std::string& name);

	bool Is3D() const;
	void Set3DAttributes(const Matrix4& worldTrans);

protected:
	friend class AudioSystem;
	SoundEvent(class AudioSystem* system, unsigned int id);

private:
	class AudioSystem* mSystem;
	unsigned int mID;
};

