#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"


class Game;
class Editor
{
public:
	Editor(); 
	~Editor();

	static void InitGui(SDL_Window* window, void* sdl_gl_context, const char* glslVersion, Game* game);
	static void Render();
	static void RenderDrawData();
	static void ShutDown();

private:
	static Game* mGame;
	static ImGuiIO* io;
	static SDL_Window* mWindow;
	static void* mSdlGLContext;
};

