// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
DECLARE_LOG_CATEGORY_EXTERN(PlayFabPartyLog, Log, All);

class FPlayFabPartyModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	/** Handle to the dlls we will load */
	static void *PartyWinHandle;

	void LoadThirdPartyDll(const FString &LibName, void *&Handle);
	static bool LoadDll(const FString &Dir, const FString &Name, void *&Handle);
	static void FreeDll(void *&Handle);

	/** Dynamic library */
	FString BaseLibPath;
};
