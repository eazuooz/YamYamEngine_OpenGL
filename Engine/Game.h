#pragma once


#include "SDL/SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

// Game class
class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	class Renderer* GetRenderer() { return mRenderer; }
	class AudioSystem* GetAudioSystem() { return mAudioSystem; }

public:
	void SetIsRunning(bool running) { mIsRunning = running; }

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();


	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;

	class Renderer* mRenderer;
	class AudioSystem* mAudioSystem;

	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;

	class CameraActor* mCameraActor; 
};
