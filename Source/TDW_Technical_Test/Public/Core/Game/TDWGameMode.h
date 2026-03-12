// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TDWGameMode.generated.h"

class UTDWAbilityInputData;
class UTDWCharacterInitializationData;
/**
 * 
 */
UCLASS()
class TDW_TECHNICAL_TEST_API ATDWGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	/* Overriding this allows us to place a character in the Level and posses it,
	 * which is useful for testing editable properties.
	 */
	virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTDWAbilityInputData> AbilityInputData;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTDWCharacterInitializationData> CharacterInitializationData;
	
public:
	UTDWAbilityInputData* GetAbilityInputData() const {return AbilityInputData;}
	const UTDWCharacterInitializationData* GetCharacterInitializationData() const {return CharacterInitializationData;}
};
