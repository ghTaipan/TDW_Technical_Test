// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_RotateToCursor.generated.h"

/**
 * 
 */
UCLASS()
class TDW_TECHNICAL_TEST_API UAnimNotifyState_RotateToCursor : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

private:
	TWeakObjectPtr<APawn> OwnerPawn;
	FVector LookAtLocation = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere)
	float InterpSpeed = 90.0f;
};
