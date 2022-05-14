/*
#############################################################################################
# Global Agenda (1.5.1.5) SDK
# Generated with TheFeckless UE3 SDK Generator v1.4_Beta-Rev.51
# ========================================================================================= #
# File: SdkHeaders.h
# ========================================================================================= #
# Credits: uNrEaL, Tamimego, SystemFiles, R00T88, _silencer, the1domo, K@N@VEL
# Thanks: HOOAH07, lowHertz
# Forums: www.uc-forum.com, www.gamedeception.net
#############################################################################################
*/

/*
# ========================================================================================= #
# Defines
# ========================================================================================= #
*/

//#define GObjects			0x13465A54
//#define GNames			0x13454180

unsigned long GObjects = 0x13465A54;
unsigned long GNames = 0x13454180;

/*
# ========================================================================================= #
# Structs
# ========================================================================================= #
*/

template<class T>
struct TArray {
public:
	T* Data;
	int Count;
	int Max;

public:
	TArray() {
		Data = 0;
		Count = Max = 0;
	};

public:
	int Num() {
		return this->Count;
	};

	T& operator()(int i) {
		return this->Data[i];
	};

	const T& operator()(int i) const {
		return this->Data[i];
	};

	void Add(T InputData) {
		Data = (T*)realloc(Data, sizeof(T) * (Count + 1));
		Data[Count++] = InputData;
		Max = Count;
	};

	void Clear() {
		free(Data);
		Count = Max = 0;
	};
};

struct FNameEntry {
	unsigned char UnknownData00[0x10];
	char Name[0x10];
};

struct FName {
	int Index;
	unsigned char unknownData00[0x4];

	FName() : Index(0) {
	};

	FName(int i) : Index(i) {
	};

	~FName() {
	};

	FName(char* FindName) {
		static TArray<int> NameCache;

		for (int i = 0; i < NameCache.Count; ++i) {
			if (!strcmp(this->Names()->Data[NameCache(i)]->Name, FindName)) {
				Index = NameCache(i);
				return;
			}
		}

		for (int i = 0; i < this->Names()->Count; ++i) {
			if (this->Names()->Data[i]) {
				if (!strcmp(this->Names()->Data[i]->Name, FindName)) {
					NameCache.Add(i);
					Index = i;
				}
			}
		}
	};

	static TArray<FNameEntry*>* Names() {
		return (TArray<FNameEntry*>*)GNames;
	};

	char* GetName() {
		return this->Names()->Data[Index]->Name;
	};

	bool operator==(const FName& A) const {
		return (Index == A.Index);
	};
};

struct FString : public TArray<wchar_t> {
	FString() {
	};

	FString(wchar_t* Other) {
		this->Max = this->Count = *Other ? (wcslen(Other) + 1) : 0;

		if (this->Count)
			this->Data = Other;
	};

	~FString() {
	};

	FString operator=(wchar_t* Other) {
		if (this->Data != Other) {
			this->Max = this->Count = *Other ? (wcslen(Other) + 1) : 0;

			if (this->Count)
				this->Data = Other;
		}

		return *this;
	};
};

struct FScriptDelegate {
	unsigned char UnknownData00[0xC];
};

/*
# ========================================================================================= #
# Includes
# ========================================================================================= #
*/

#include "sdk\Core_structs.h"
#include "sdk\Core_classes.h"
#include "sdk\Core_f_structs.h"
#include "sdk\Core_functions.h"
#include "sdk\Engine_structs.h"
#include "sdk\Engine_classes.h"
#include "sdk\Engine_f_structs.h"
#include "sdk\Engine_functions.h"
#include "sdk\GameFramework_structs.h"
#include "sdk\GameFramework_classes.h"
#include "sdk\GameFramework_f_structs.h"
#include "sdk\GameFramework_functions.h"
#include "sdk\UnrealScriptTest_structs.h"
#include "sdk\UnrealScriptTest_classes.h"
#include "sdk\UnrealScriptTest_f_structs.h"
#include "sdk\UnrealScriptTest_functions.h"
#include "sdk\TgGame_structs.h"
#include "sdk\TgGame_classes.h"
#include "sdk\TgGame_f_structs.h"
#include "sdk\TgGame_functions.h"
#include "sdk\TgNetDrv_structs.h"
#include "sdk\TgNetDrv_classes.h"
#include "sdk\TgNetDrv_f_structs.h"
#include "sdk\TgNetDrv_functions.h"
#include "sdk\TgClient_structs.h"
#include "sdk\TgClient_classes.h"
#include "sdk\TgClient_f_structs.h"
#include "sdk\TgClient_functions.h"
#include "sdk\XAudio2_structs.h"
#include "sdk\XAudio2_classes.h"
#include "sdk\XAudio2_f_structs.h"
#include "sdk\XAudio2_functions.h"
#include "sdk\ALAudio_structs.h"
#include "sdk\ALAudio_classes.h"
#include "sdk\ALAudio_f_structs.h"
#include "sdk\ALAudio_functions.h"
#include "sdk\WinDrv_structs.h"
#include "sdk\WinDrv_classes.h"
#include "sdk\WinDrv_f_structs.h"
#include "sdk\WinDrv_functions.h"
