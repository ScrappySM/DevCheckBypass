// How the mod works:
// The game has a check that is ran whilst joining another player/server that compares the clients flag to the servers flag.
// If the flags don't match, the game will kick the player.
// This mod bypasses that check by nopping the instruction that jumps after the comparison of the two flags.

// Here's a brief snippet of the assembly in the function
// .text:000000014042CE97 0F B6 05 99 A6 E3 00    movzx   eax, cs:byte_141267537 ; Move with Zero-Extend
// .text:000000014042CE9E 41 38 46 78             cmp     [r14+78h], al   ; Compare Two Operands
// .text:000000014042CEA2 0F 85 89 0A 00 00       jnz     loc_14042D931   ; Jump if Not Zero (ZF=0) <--- This is the instruction we want to nop

// Here's what we do to it
// .text:000000014042CE97 0F B6 05 99 A6 E3 00    movzx   eax, cs:byte_141267537 ; Move with Zero-Extend
// .text:000000014042CE9E 41 38 46 78             cmp     [r14+78h], al   ; Compare Two Operands
// .text:000000014042CEA2 90 90 90 90 90 90       nop nop nop nop nop nop ; No operation <--- We replace it with **6** nops because the original instruction is 6 bytes long and nop is 1 byte long

// How to update the offset:
// You can find this function (assuming you're using IDA) by searching for the string "mismatching developer mode flags" in the strings window.
// You should then X-Ref the string and find the function that references it.
// Then select the if statement that checks the flags and synchronise a disassembly view with the decompiled view.
// You should then see the jnz instruction that we want to nop.
// The offset is the address of the jnz instruction minus the base address of the module (0x140000000 in this case).

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstdint>

// The offset of the instruction we want to nop
static constexpr uintptr_t pOffset = 0x42CEA2;

/// <summary>
/// Entry point for the DLL
/// </summary>
/// <param name="hModule"></param>
/// <param name="dwReason"></param>
/// <param name="lpReserved"></param>
/// <returns>TRUE on success</returns>
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		auto pAddress = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr)) + pOffset;

		// The first byte is 0F which is the opcode for the instruction
		// If it's not 0F, the game has been updated and the offset is no longer valid
		if (*reinterpret_cast<uint8_t*>(pAddress) != 0x0F) {
			MessageBoxA(nullptr, "DevCheckBypass isn't compatible with this game version!", "Error", MB_ICONERROR);
			return FALSE;
		}

		// Patch to nops, need to replace 6 bytes as the original instruction is 6 bytes long
		DWORD oldProtect;
		if (!VirtualProtect(reinterpret_cast<void*>(pAddress), 6, PAGE_EXECUTE_READWRITE, &oldProtect)) {
			MessageBoxA(nullptr, "Failed to change memory protection!", "Error", MB_ICONERROR);
			return FALSE;
		}

		// Nop the instruction
		memset(reinterpret_cast<void*>(pAddress), 0x90, 6);

		// Restore the original protection
		VirtualProtect(reinterpret_cast<void*>(pAddress), 6, oldProtect, &oldProtect);
	}

	return TRUE;
}
