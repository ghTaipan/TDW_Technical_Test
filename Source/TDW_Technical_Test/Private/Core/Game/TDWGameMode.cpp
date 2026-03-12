// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Game/TDWGameMode.h"

#include "Kismet/GameplayStatics.h"

APawn* ATDWGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
	// 1. Check if an instance already exists in the world
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), DefaultPawnClass, FoundActors);

	if (FoundActors.Num() > 0)
	{
		APawn* ChosenPawn = Cast<APawn>(FoundActors[0]);
		ChosenPawn->SetActorLocation(StartSpot->GetActorLocation());
		return ChosenPawn;
	}

	// 3. Otherwise, proceed with default spawning
	return Super::SpawnDefaultPawnFor_Implementation(NewPlayer, StartSpot);
}
