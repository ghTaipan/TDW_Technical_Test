// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Animation/ANS/AnimNotifyState_RotateToCursor.h"

#include "Core/Player/TDWPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

void UAnimNotifyState_RotateToCursor::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                  float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	OwnerPawn = MakeWeakObjectPtr(Cast<APawn>(MeshComp->GetOwner()));
	
	// This supposed to be null only while displaying the montage in the editor.
#if WITH_EDITOR
	if (!OwnerPawn.IsValid())
	{
		return;
	}
#endif
	
	const ATDWPlayerController* PC = Cast<ATDWPlayerController>(OwnerPawn->GetController());
	if (IsValid(PC))
	{
		FHitResult Hit;
		if (PC->GetHitUnderCursor(Hit))
		{
			const FVector ActorLocation = OwnerPawn->GetActorLocation();
	
			// For being sure if player clicks very close to the character, the character won't turn into a beyblade.
			LookAtLocation = ActorLocation + ((Hit.Location - ActorLocation).GetSafeNormal() * 1000.0f);
		}
	}
}

void UAnimNotifyState_RotateToCursor::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	
#if WITH_EDITOR
	if (!OwnerPawn.IsValid())
	{
		return;
	}
#endif
	
	const FRotator& ActorRotation = OwnerPawn->GetActorRotation();
	
	const FRotator TargetRotation = FRotator(ActorRotation.Pitch, UKismetMathLibrary::FindLookAtRotation(OwnerPawn->GetActorLocation(), LookAtLocation).Yaw,
		ActorRotation.Roll);
	
	OwnerPawn->SetActorRotation(FMath::RInterpTo(ActorRotation, TargetRotation, FrameDeltaTime, InterpSpeed));
}
