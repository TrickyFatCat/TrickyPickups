// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov


#include "PickupEffectsComponent.h"

#include "PickupEffectType.h"

UPickupEffectsComponent::UPickupEffectsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	UActorComponent::SetComponentTickEnabled(false);
	bWantsInitializeComponent = true;
}

void UPickupEffectsComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (MainEffectType)
	{
		MainEffect = NewObject<UPickupEffectType>(this, MainEffectType);
	}

	if (SecondaryEffectsTypes.Num() > 0)
	{
		SecondaryEffects.Empty();

		for (const auto& EffectType : SecondaryEffectsTypes)
		{
			if (!EffectType)
			{
				continue;
			}

			UPickupEffectType* NewEffect = NewObject<UPickupEffectType>(this, EffectType);
			SecondaryEffects.Emplace(NewEffect);
		}
	}
}

bool UPickupEffectsComponent::ActivatePickupEffects(AActor* OtherActor)
{
	if (!IsValid(OtherActor) || !IsValid(MainEffect))
	{
		return false;
	}

	const bool Result = MainEffect->ActivateEffect(OtherActor);

	if (Result)
	{
		OnMainEffectActivated.Broadcast(MainEffect);
	}

	if (SecondaryEffects.Num() > 0 && Result)
	{
		for (const auto& Effect : SecondaryEffects)
		{
			if (!IsValid(Effect))
			{
				continue;
			}
			
			if (Effect->ActivateEffect(OtherActor))
			{
				OnSecondaryEffectActivated.Broadcast(Effect);
			}
		}
	}

	return Result;
}

void UPickupEffectsComponent::SetMainEffectType(TSubclassOf<UPickupEffectType> Value)
{
	MainEffectType = Value;
}

TSubclassOf<UPickupEffectType> UPickupEffectsComponent::GetMainEffectType() const
{
	return MainEffectType;
}

void UPickupEffectsComponent::SetSecondaryEffectsTypes(const TArray<TSubclassOf<UPickupEffectType>>& Value)
{
	SecondaryEffectsTypes = Value;
}

void UPickupEffectsComponent::GetSecondaryEffectsTypes(TArray<TSubclassOf<UPickupEffectType>>& Value)
{
	Value = SecondaryEffectsTypes;
}
