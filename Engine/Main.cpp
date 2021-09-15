#include "Game.h"
#include <crtdbg.h>

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(382); // Ãß°¡
	//{455} normal block at 0x000001C98F232350, 12 bytes long.
	//	Data: < > 0D 00 00 00 0E 00 00 00 0F 00 00 00
	//{419} normal block at 0x000001C98F2325D0, 12 bytes long.
	//	Data : < > 0A 00 00 00 0B 00 00 00 0C 00 00 00
	//{382} normal block at 0x000001C98A857BB0, 12 bytes long.
	//	Data: < > 07 00 00 00 08 00 00 00 09 00 00 00

	Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}
