#include <Windows.h>
#include "Application.h"

// できるだけ簡潔にコードを書くため、#include と行数は減らすこと

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, int nCmdShow) {
	Application::CreateInstance();

	if (!Application::GetInstance().Init()) return -1;

	Application::GetInstance().GameLoop();

	if (!Application::GetInstance().Release()) return -1;
	Application::DeleteInstance();

	return 0;
}
