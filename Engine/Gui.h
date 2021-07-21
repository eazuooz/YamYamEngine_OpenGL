#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"


class Gui
{
public:
	Gui() {}
	~Gui() {}

	static InitGui();

private:
	ImGuiIO* io;
};

