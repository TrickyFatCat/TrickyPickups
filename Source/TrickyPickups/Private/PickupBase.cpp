// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov


#include "PickupBase.h"

#include "FollowAnimationComponent.h"
#include "PickupEffectsComponent.h"

APickupBase::APickupBase()
{
	PrimaryActorTick.bCanEverTick = true;

	PickupRootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	SetRootComponent(ToRawPtr(PickupRootComponent));

	PickupEffectsComponent = CreateDefaultSubobject<UPickupEffectsComponent>("PickupEffects");

	FollowAnimationComponent = CreateDefaultSubobject<UFollowAnimationComponent>("FollowAnimation");
	FollowAnimationComponent->StopFollowing();
}

void APickupBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (PickupEffectsComponent)
	{
		PickupEffectsComponent->SetMainEffectType(MainEffectType);
		PickupEffectsComponent->SetSecondaryEffectsTypes(SecondaryEffectsTypes);
	}
}

void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInterpolateToTarget && IsValid(TargetActor) && FollowAnimationComponent->GetIsFollowing())
	{
		const float Distance = FVector::DistSquared(GetActorLocation(), TargetActor->GetActorLocation());

		if (Distance <= ActivationDistance * ActivationDistance)
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
		FollowAnimationComponent->bFollowActor = true;
		FollowAnimationComponent->TargetActor = TargetActor;
		FollowAnimationComponent->StartFollowing();
		
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
		FollowAnimationComponent->StopFollowing();
	}

	OnPickupDisabled();
}

bool APickupBase::ActivatePickupEffect()
{
	if (PickupEffectsComponent->ActivatePickupEffects(TargetActor))
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