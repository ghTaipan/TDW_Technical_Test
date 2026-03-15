// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Animation/ANS/AnimNotifyState_RotateToCursor.h"

#include "Core/Player/TDWPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

void UAnimNotifyState_RotateToCursor::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                  float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	OwnerPawn = MakeWeakObjectPtr(Cast<APawn>(MeshComp->GetOwner()));
	
	if (!OwnerPawn.IsValid())
	{
		return;
	}
	
	const ATDWPlayerController* PC = Cast<ATDWPlayerController>(OwnerPawn->GetController());
	if (IsValid(PC))
	{
		FHitResult Hit;
		if (PC->GetHitUnderCursor(Hit))
		{
			const FVector& ActorLocation = OwnerPawn->GetActorLocation();
			const FVector ActorLocationXY = FVector(ActorLocation.X, ActorLocation.Y, 0);
			const FVector HitLocationXY = FVector(Hit.Location.X, Hit.Location.Y, 0);
			
			FVector TargetDirection;
			const float DistanceToCursor = FMath::Sqrt(FVector::DistSquared(ActorLocationXY, HitLocationXY));
			if (DistanceToCursor >= 15.0f)
			{
				TargetDirection = (HitLocationXY - ActorLocationXY).GetSafeNormal();
			}
			else
			{
				TargetDirection = OwnerPawn->GetActorForwardVector();
			}
			
			// For being sure if player clicks very close to the character, the character won't turn into a beyblade.
			LookAtLocation = ActorLocation + (TargetDirection * 1000.0f);
		}
	}
}

void UAnimNotifyState_RotateToCursor::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	
	if (!OwnerPawn.IsValid())
	{
		return;
	}
	
	const FRotator& ActorRotation = OwnerPawn->GetActorRotation();
	
	const FRotator TargetRotation = FRotator(ActorRotation.Pitch, UKismetMathLibrary::FindLookAtRotation(OwnerPawn->GetActorLocation(), LookAtLocation).Yaw,
		ActorRotation.Roll);
	
	OwnerPawn->SetActorRotation(FMath::RInterpTo(ActorRotation, TargetRotation, FrameDeltaTime, InterpSpeed));
}
