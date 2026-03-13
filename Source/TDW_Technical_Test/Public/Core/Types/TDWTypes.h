#pragma once

#include "GameplayTagContainer.h"
#include "TDWTypes.generated.h"


// If a CPP map uses this struct as a key, it needs to customize owning UObject's PostEditChangeChainProperty. Otherwise, the details panel will allow 2 identical keys.
USTRUCT(BlueprintType, meta = (Hidden))
struct FTDWGameplayTagContainerMapKey
{
	GENERATED_BODY()
	
	FTDWGameplayTagContainerMapKey() = default;
	FTDWGameplayTagContainerMapKey(const FGameplayTagContainer& InTagContainer) : TagContainer(InTagContainer)
	{}
	
	bool operator==(const FTDWGameplayTagContainerMapKey& Other) const
	{
		return TagContainer == Other.TagContainer;
	}
	friend uint32 GetTypeHash(const FTDWGameplayTagContainerMapKey& Key)
	{
		if (Key.CachedHash == 0)
		{
			TArray<FGameplayTag> Tags;
			Key.TagContainer.GetGameplayTagArray(Tags);
			
			Tags.Sort([](const FGameplayTag& A, const FGameplayTag& B) {
				return A.GetTagName().LexicalLess(B.GetTagName());
			});
			
			uint32 Hash = 0;
			for (const FGameplayTag& Tag : Tags)
			{
				Hash = HashCombine(Hash, GetTypeHash(Tag));
			}
			
			Key.CachedHash = Hash;
		}
		
		return Key.CachedHash;
	}
	
	void InvalidateHash() const
	{
		CachedHash = 0;
	}
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FGameplayTagContainer TagContainer;
	
	mutable uint32 CachedHash = 0;
};

USTRUCT(BlueprintType)
struct FSoundBaseArray
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USoundBase*> SoundArray;
};