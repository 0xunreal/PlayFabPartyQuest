// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PlayFabParty.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FPlayFabPartyModule"
DEFINE_LOG_CATEGORY(PlayFabPartyLog);

void *FPlayFabPartyModule::PartyWinHandle = nullptr;

void FPlayFabPartyModule::StartupModule()
{
	UE_LOG(PlayFabPartyLog, Log, TEXT("FPlayFabPartyModule startup."));
	BaseLibPath = IPluginManager::Get().FindPlugin(TEXT("PlayFabParty"))->GetBaseDir();
	UE_LOG(PlayFabPartyLog, Log, TEXT(" Lib path = '%s'"), *BaseLibPath);

#if PLATFORM_WINDOWS
	#if PLATFORM_64BITS
		#ifdef WITH_PLAYFAB_PARTY
			UE_LOG(PlayFabPartyLog, Log, TEXT("WITH_PLAYFAB_PARTY defined."));
			#if WITH_PLAYFAB_PARTY
				UE_LOG(PlayFabPartyLog, Log, TEXT("WITH_PLAYFAB_PARTY=1"));
				LoadThirdPartyDll("PartyWin", PartyWinHandle);
			#else
				UE_LOG(PlayFabPartyLog, Log, TEXT("WITH_PLAYFAB_PARTY=0"));			;
			#endif
		#else
			UE_LOG(PlayFabPartyLog, Log, TEXT("WITH_PLAYFAB_PARTY not defined."));
		#endif
	#endif
#endif
}

void FPlayFabPartyModule::ShutdownModule()
{
	FreeDll(PartyWinHandle);
}

void FPlayFabPartyModule::LoadThirdPartyDll(const FString &LibName, void *&Handle)
{
	BaseLibPath = BaseLibPath + TEXT("/ThirdParty/Win64");
	if (!LoadDll(BaseLibPath, LibName, Handle))
	{
		UE_LOG(PlayFabPartyLog, Error, TEXT("Failed to load %s. Plug-in will not be functional."), *LibName);
		FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT(LOCTEXT_NAMESPACE, "Failed to load {0}. Plug-in will not be functional."), FText::FromString(LibName)));
	}
	else
	{
		UE_LOG(PlayFabPartyLog, Log, TEXT("Successfully loaded Third party DLL %s."), *LibName);
	}
}

bool FPlayFabPartyModule::LoadDll(const FString &Dir, const FString &Name, void *&Handle)
{
	FString Lib = Name + TEXT(".") + FPlatformProcess::GetModuleExtension();
	FString Path = Dir.IsEmpty() ? *Lib : FPaths::Combine(*Dir, *Lib);

	UE_LOG(PlayFabPartyLog, Log, TEXT("LoadDll: %s"), *Path);

	Handle = FPlatformProcess::GetDllHandle(*Path);

	if (Handle == nullptr)
	{
		return false;
	}

	return true;
}

void FPlayFabPartyModule::FreeDll(void *&Handle)
{
	if (Handle != nullptr)
	{
		FPlatformProcess::FreeDllHandle(Handle);
		Handle = nullptr;
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPlayFabPartyModule, PlayFabParty)
