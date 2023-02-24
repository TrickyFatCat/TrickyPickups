// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#include "PickupBase.h"

#include "EaseAnimationComponent.h"
#include "PickupEffectsComponent.h"

APickupBase::APickupBase()
{
	PrimaryActorTick.bCanEverTick = true;

	PickupRootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	SetRootComponent(PickupRootComponent);

	PickupEffectsComponent = CreateDefaultSubobject<UPickupEffectsComponent>("PickupEffects");

	EaseAnimationComponent = CreateDefaultSubobject<UEaseAnimationComponent>("EaseAnimation");
	EaseAnimationComponent->Stop();
}

void APickupBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (PickupEffectsComponent)
	{
		PickupEffectsComponent->SetMainEffectType(MainEffectType);
		PickupEffectsComponent->SetSecondaryEffectsTypes(SecondaryEffectsTypes);
	}

	if (EaseAnimationComponent)
	{
		EaseAnimationComponent->Stop();
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
	if (PickupEffectsComponent->ActivatePickupEffect(TargetActor))
	{
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