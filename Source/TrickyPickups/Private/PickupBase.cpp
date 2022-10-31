// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "PickupBase.h"


APickupBase::APickupBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APickupBase::BeginPlay()
{
	Super::BeginPlay();
}

void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickupBase::ActivatePickup(AActor* TargetActor)
{
	if (!IsValid(TargetActor))
	{
		return;
	}

	if (ActivatePickupEffect(TargetActor))
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
	}
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

bool APickupBase::ActivatePickupEffect_Implementation(AActor* TargetActor)
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
	OnPickupDisabled();
}

