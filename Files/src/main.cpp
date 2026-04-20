#include <Windows.h>
#include "Application.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, int nCmdShow) {
	Application::CreateInstance();

	auto& app = Application::GetInstance();

	if (!app.Init()) return -1;

	app.GameLoop();

	if (!app.Release()) return -1;

	Application::DeleteInstance();

	return 0;
}
