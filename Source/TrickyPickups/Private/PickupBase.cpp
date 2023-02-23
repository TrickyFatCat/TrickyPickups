// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#include "PickupBase.h"

#include "EaseAnimationComponent.h"
#include "PickupEffectType.h"


APickupBase::APickupBase()
{
	PrimaryActorTick.bCanEverTick = true;

	PickupRootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	SetRootComponent(PickupRootComponent);

	EaseAnimationComponent = CreateDefaultSubobject<UEaseAnimationComponent>("EaseAnimation");
	EaseAnimationComponent->Stop();
}

void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	EaseAnimationComponent->Stop();

	if (MainEffectType)
	{
		MainEffect = NewObject<UPickupEffectType>(this, MainEffectType);
	}

	if (SecondaryEffectsTypes.Num() > 0)
	{
		for (const TSubclassOf<UPickupEffectType>& Effect : SecondaryEffectsTypes)
		{
			UPickupEffectType* SecondaryEffect = NewObject<UPickupEffectType>(this, Effect);

			if (!SecondaryEffect)
			{
				continue;
			}

			SecondaryEffects.Emplace(SecondaryEffect);
		}
	}
}

void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInterpolateToTarget && IsValid(TargetActor) && EaseAnimationComponent->GetIsPlaying())
	{
		const float Distance = FVector::DistSquared(GetActorLocation(), TargetActor->GetActorLocation());

		if (Distance <= ActivationDistance * ActivationDistance)
		{
			ActivatePickupEffect();
		}
		else
		{
			SetAnimationTargetLocation();
		}
	}
}

bool APickupBase::ActivatePickup(AActor* OtherActor)
{
	if (!IsValid(OtherActor))
	{
		return false;
	}

	TargetActor = OtherActor;

	if (bInterpolateToTarget)
	{
		SetAnimationTargetLocation();
		EaseAnimationComponent->PlayFromStart();
		return true;
	}

	return ActivatePickupEffect();
}

void APickupBase::EnablePickup()
{
	if (!IsHidden())
	{
		return;
	}

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

void APickupBase::DisablePickup()
{
	if (IsHidden())
	{
		return;
	}

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	if (bInterpolateToTarget)
	{
		EaseAnimationComponent->Stop();
	}

	OnPickupDisabled();
}

bool APickupBase::ActivatePickupEffect()
{
	if (ActivateMainEffect())
	{
		ActivateSecondaryEffects();

		OnPickupEffectActivated(TargetActor);
		OnPickupActivated.Broadcast();

		if (bDestroyOnActivation)
		{
			Destroy();
		}
		else
		{
			DisablePickup();
		}

		return true;
	}

	return false;
}

void APickupBase::SetAnimationTargetLocation() const
{
	if (!IsValid(TargetActor))
	{
		return;
	}

	EaseAnimationComponent->SetTargetLocation(TargetActor->GetActorLocation());
}

bool APickupBase::ActivateMainEffect() const
{
	if (!IsValid(MainEffect))
	{
		return false;
	}

	return MainEffect->ActivateEffect(TargetActor);
}

void APickupBase::ActivateSecondaryEffects()
{
	for (const auto& Effect : SecondaryEffects)
	{
		if (!IsValid(Effect))
		{
			continue;
		}

		Effect->ActivateEffect(TargetActor);
	}
}
