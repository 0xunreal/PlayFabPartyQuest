// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Party.h"
#include "MyGameMode.generated.h"

using namespace Party;

/**
 * 
 */
UCLASS()
class PLAYFABPARTYQUEST_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()

protected:

	void BeginPlay() override;
};
