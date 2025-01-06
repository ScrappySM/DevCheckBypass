#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <spdlog/spdlog.h>

#include <functional>
#include <thread>

/// <summary>
/// Main entry point for the DLL, starts the main function in a new thread
/// </summary>
/// <param name="lpReserved">Reserved</param>
/// <returns>0 on success</returns>
int main(LPVOID lpReserved) {
	HMODULE hModule = static_cast<HMODULE>(lpReserved);

	// Put your main code here
	spdlog::info("Hello from the template!");

	// Example: You can put a while loop here to keep the DLL loaded!
	while (!GetAsyncKeyState(VK_END)) {
	    std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	spdlog::info("Exiting...");
	FreeLibraryAndExitThread(hModule, 0);

	return 0;
}

/// <summary>
/// Entry point for the DLL
/// </summary>
/// <param name="hModule"></param>
/// <param name="dwReason"></param>
/// <param name="lpReserved"></param>
/// <returns>TRUE on success</returns>
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	static DWORD dwThreadId = 0;
	BOOL consoleAllocated = FALSE;

	if (dwReason == DLL_PROCESS_ATTACH) {
		consoleAllocated = AllocConsole();

		// Only do this if you want to have an infinite loop in the main function
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(main), hModule, 0, &dwThreadId);

		// Otherwise, just call main directly like so
		// main(hModule);
	}
	else if (dwReason == DLL_PROCESS_DETACH) {
		if (consoleAllocated) {
			FreeConsole();
		}

		// If you didn't start a new thread in the DLL_PROCESS_ATTACH, you can deinitialize here
		// otherwise, you should deinitalize in the main function
	}

	return TRUE;
}
