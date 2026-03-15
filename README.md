# TDW_Technical_Test

This documentation focuses on the macro-level decisions behind the implementation.

1- Grouping Relative Attributes: Instead of implementing all the attributes and their logic in one attribute set, grouping relative attributes together in their own attribute set allows the system to be more modular and it prevents us from setting irrelevant attributes to certain characters (e.g., a Test Dummy does not need Mana). While this level of abstraction may seem unnecessary for a small test scenario, it is one of the best practices that ensures scalability as the project evolves.

2- AbilitySystemInitializationSpec: This struct is consistent of initial GameplayAbilities, GameplayEffects, Attribute Sets, Attribute's initial values and GameplayTags. By using it with CharacterInitializationData, we can define and specify every character type within a single data asset. While several implementation paths exist, this approach was chosen for its balance of simplicity and high extensibility.

3- Input Handling in PlayerController: Managing input within the Controller rather than the Character is best practice, as it eliminates the need to re-bind inputs during character swaps or in multiplayer scenarios where a character may respawn while the Controller persists. Even though this project is not currently built around those specific needs, this approach maintains a strict separation between player intent and character execution. This architecture ensures the Character class remains a clean representation of the physical actor, while the Controller serves as the dedicated interface for user input.

4- Custom Gameplay Effect Context & DamageSpec: Implemented the DamageSpec struct to store the necessary data for specifying attacks and derived a children of FGameplayEffectContext to ensure this data flows through the applying damage pipeline.

5- CharacterAssets DataAsset: Created a C++ UDataAsset base with Blueprint derivatives for customizing each character class's assets, keeping the project modular and organized.

6- Widget Controllers: Widget Controllers function as a bridge between the Ability System and the UI. Their main job is to broadcast data updates (attribute changes in our case) directly to the interface.