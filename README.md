# TDW_Technical_Test

This documentation focuses on the macro-level decisions behind the implementation.

1- Grouping Relative Attributes: Instead of implementing all the attributes and their logic in one attribute set, grouping relative attributes together in their own attribute set allows the system to be more modular and it prevents us from setting irrelevant attributes to certain characters. For instance, a Test Dummy does not need Mana and Attack Speed attributes.

2- AbilitySystemInitializationSpec: This struct is consistent of initial GameplayAbilities, GameplayEffects, Attribute Sets, Attribute's initial values and GameplayTags. By using it with CharacterInitializationData, we can define and specify every character type within a single data asset.

3- Localizing ability activation: Localizing ability activation under specific conditions provides several key benefits:
   
    A) Scalability:
        As the project grows and dozens of abilities are added, it becomes harder to manage individual assets. Without localization, we would have to open too many files to manually set ActivationBlockedTags and ActivationRequiredTags. While the GameplayTag hierarchy is great for defining boundaries, the manual workload scales poorly. Localizing activation allows us to define the logic in one data asset to rule them all!
    
    B) Debugging & Performance:
        Binding multiple abilities to the same input can make debugging a nightmare and waste processing power on "unactivatable" abilities.
        For Example: Lets say we have light attack, sprint attack, dash attack and jump attack and all are given to the AbilitySystemComponent in order and bound to MB1; clicking it while in-air forces you to step through the code for every single one until you hit the Jump Attack logic. This is a waste of both debugging time and performance.

4- Custom Gameplay Effect Context & DamageSpec: Implemented the DamageSpec struct to store the necessary data for specifying attacks and derived a children of FGameplayEffectContext to ensure this data flows through the applying damage pipeline.

5- CharacterAssets DataAsset:: Created a C++ UDataAsset base with Blueprint derivatives for customizing each character class's assets, keeping the project modular and organized.

6- Widget Controllers: Widget Controllers function as a bridge between the Ability System and the UI. Their main job is to broadcast data updates (attribute changes in our case) directly to the interface.
