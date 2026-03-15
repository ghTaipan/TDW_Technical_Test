// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Animation/ANS/AnimNotifyState_TraceAndEvent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void UAnimNotifyState_TraceAndEvent::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                 float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	OwnerActor = MakeWeakObjectPtr(MeshComp->GetOwner());

#if WITH_EDITOR
	if (!OwnerActor.IsValid())
	{
		return;
	}
#endif
	
	OwnerASC = MakeWeakObjectPtr(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerActor.Get()));
	ActorsToIgnore.Add(OwnerActor.Get());
}

void UAnimNotifyState_TraceAndEvent::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	
#if WITH_EDITOR
	if (!(OwnerActor.IsValid() && OwnerASC.IsValid()))
	{
		return;
	}
#endif

	const EDrawDebugTrace::Type DrawDebugType = bDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;
	TArray<FHitResult> OutHits;
	
	const FVector ActorLocation = MeshComp->GetOwner()->GetActorLocation();
	const bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(MeshComp, ActorLocation, ActorLocation,
		Radius, HitObjectTypes, false,
		ActorsToIgnore, DrawDebugType, OutHits, true);
	
	if (bHit)
	{
		for (const FHitResult& Hit : OutHits)
		{
			AActor* HitActor = Hit.GetActor();
			if (!ActorsToIgnore.Contains(HitActor))
			{
				ActorsToIgnore.Add(HitActor);
				
				FGameplayEventData Payload;
				Payload.ContextHandle = OwnerASC->MakeEffectContext();
				Payload.ContextHandle.AddHitResult(Hit);
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor.Get(), EventTag, Payload);
			}
		}
	}
}

void UAnimNotifyState_TraceAndEvent::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	
	ActorsToIgnore.Empty();
}
