// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "PickupBase.h"

#include "EaseAnimationComponent.h"


APickupBase::APickupBase()
{
	PrimaryActorTick.bCanEverTick = true;

	PickupRootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	SetRootComponent(PickupRootComponent);

	EaseAnimationComponent = CreateDefaultSubobject<UEaseAnimationComponent>("EaseAnimation");
	EaseAnimationComponent->bFollowActor = true;
	EaseAnimationComponent->SetIsEnabled(false);
}

void APickupBase::BeginPlay()
{
	Super::BeginPlay();
}

void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInterpolateToTarget && IsValid(TargetActor) && EaseAnimationComponent->GetIsEnabled())
	{
		const float Distance = FVector{GetActorLocation() - TargetActor->GetActorLocation()}.Size();

		if (Distance <= ActivationDistance)
		{
			ActivatePickupEffect();
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
		EaseAnimationComponent->TargetActor = TargetActor;
		EaseAnimationComponent->SetIsEnabled(true);
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

bool APickupBase::PickupEffect_Implementation(AActor* OtherActor)
{
	return true;
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
		EaseAnimationComponent->SetIsEnabled(false);
		EaseAnimationComponent->TargetActor = nullptr;
	}

	OnPickupDisabled();
}

bool APickupBase::ActivatePickupEffect()
{
	if (PickupEffect(TargetActor))
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
