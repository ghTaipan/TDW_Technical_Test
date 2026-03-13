// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Animation/AN/AnimNotify_SendGameplayEvent.h"

#include "AbilitySystemBlueprintLibrary.h"

void UAnimNotify_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, FGameplayEventData());
}
