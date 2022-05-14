//
// Created by dev on 5/13/2022.
//

#include <cstdint>
#include <Windows.h>
#include <cstdio>
#include <SafetyHook.hpp>

#include "sdk.hpp"

struct FFieldNetCache {
	UField* field1;
	int netindex;
	int dummy;
};

struct FClassNetCache {
	int field1;
	int field2;
	int field3;
	int FieldsBase;
	FClassNetCache* Super;
	int RepConditionCount;
	UClass *Class;
	TArray<FFieldNetCache> Fields;
	int FieldsNum;
	int field6;
};

std::unique_ptr<SafetyHook> hk_GetClassNetCache{};
std::unique_ptr<SafetyHook> hk_FBitReader_ReadInt{};

std::vector<void*> classes_registered{};
bool print_properties = true;
FClassNetCache* __fastcall GetClassNetCache(void* ecx, void* edx, UClass* uclass) {
	auto ret = hk_GetClassNetCache->thiscall<FClassNetCache*>(ecx, uclass);

	if (__builtin_return_address(0) == (void*)0x10D8E3EF) {
		if (std::ranges::find(classes_registered, ret) == classes_registered.end()) {
			print_properties = true;
			classes_registered.push_back(ret);

			printf("Registering %s: 0x%p\n", ret->Class->GetName(), uclass);
		} else {
			print_properties = false;
		}
	}

	return ret;
}

uint32_t __fastcall FBitReader_ReadInt(void* ecx, void* edx, uint32_t Max) {
	auto ret = hk_FBitReader_ReadInt->thiscall<uint32_t>(ecx, Max);

	bool ret_addr_field = __builtin_return_address(0) == (void*)0x10D8E484 || __builtin_return_address(0) == (void*)0x10D8E94B;
	bool ret_addr_rpc = __builtin_return_address(0) == (void*)0x10D8EF40;

	// 10D8EF40
	if (print_properties && (ret_addr_field || ret_addr_rpc)) {
		using get_from_index_t = FFieldNetCache*(__thiscall*)(void* ecx, uint32_t index);

		FFieldNetCache* cache = ((get_from_index_t)0x10D8F330)(classes_registered.back(), ret);

		if (ret_addr_field) {
			printf("--> Field %s: %i %i\n", cache->field1->GetName(), ret, Max);
		} else {
			printf("--> RPC %s: %i %i\n", cache->field1->GetName(), ret, Max);
		}
	}

	return ret;
}

void __stdcall entrypoint() {
	// Try and allocate a new console for debugging purposes.
	if (!AllocConsole()) {
		MessageBoxA(nullptr, "Unable to create a win32 console.", "foobar", MB_ICONERROR);
	}

	// Redirect output to the console.
	FILE *dummy;
	freopen_s(&dummy, "CONIN$", "r", stdin);
	freopen_s(&dummy, "CONOUT$", "w", stderr);
	freopen_s(&dummy, "CONOUT$", "w", stdout);

	// Enter local scope
	{
		const auto factory = SafetyHookFactory::init();

		// Freeze all threads
		auto builder = factory->acquire();

		hk_GetClassNetCache = builder.create((void*)0x11365C30, (void*)&GetClassNetCache);
		hk_FBitReader_ReadInt = builder.create((void*)0x11362EB0, (void*)&FBitReader_ReadInt);
	}
}

void exitpoint() {
	hk_GetClassNetCache.reset();
	hk_FBitReader_ReadInt.reset();
}

int32_t __stdcall DllMain(HMODULE self, uint32_t reason, void* reserved) {
	switch (reason) {
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(self);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)entrypoint, nullptr, 0, nullptr);
			return 1;

		case DLL_PROCESS_DETACH:
			exitpoint();
			return 1;

		default:
			return 1;
	}
}