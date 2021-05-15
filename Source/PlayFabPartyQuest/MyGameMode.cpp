// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "PlayFabParty/Public/PartyPal.h"
#include "PlayFabParty/Public/Party.h"
#include "PlayFabParty/Public/PartyImpl.h"

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("AMyGameMode::BeginPlay("));

	auto& PartyManager = PartyManager::GetSingleton();

    const PartyError Error = PartyManager.Initialize(TCHAR_TO_UTF8("ASDF"));
    if (PARTY_FAILED(Error))
    {
        UE_LOG(LogTemp, Log, TEXT("partyManager Initialize failed: "));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("partyManager Initialized: %hs"), TCHAR_TO_UTF8("ASDF"));
}
