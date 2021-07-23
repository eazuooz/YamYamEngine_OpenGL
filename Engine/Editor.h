#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"


class Editor
{
public:
	Editor() {}
	~Editor() {}

	static void InitGui();

private:
	ImGuiIO* io;
};

