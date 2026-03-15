// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_TraceAndEvent.generated.h"

class UAbilitySystemComponent;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class TDW_TECHNICAL_TEST_API UAnimNotifyState_TraceAndEvent : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
private:
	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;
	
	TWeakObjectPtr<AActor> OwnerActor;
	TWeakObjectPtr<UAbilitySystemComponent> OwnerASC;
	
	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> HitObjectTypes;
	
	UPROPERTY(EditAnywhere)
	FGameplayTag EventTag;
	// Trace origin socket.
	UPROPERTY(EditAnywhere, meta = (AnimNotifyBoneName = "true"))
	FName SocketName;
	// Radius of the trace.
	UPROPERTY(EditAnywhere)
	float Radius = 150.0f;
	
	UPROPERTY(EditAnywhere)
	bool bDebug = false;
};
