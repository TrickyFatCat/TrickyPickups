// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#include "PickupInteractive.h"

#include "InteractionLibrary.h"
#include "SphereInteractionComponent.h"

APickupInteractive::APickupInteractive()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractionTriggerComponent = CreateDefaultSubobject<USphereInteractionComponent>("InteractionTrigger");
	InteractionTriggerComponent->SetupAttachment(GetRootComponent());
	UInteractionLibrary::SetTriggerDefaultCollision(InteractionTriggerComponent);
}

void APickupInteractive::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (InteractionTriggerComponent)
	{
		InteractionTriggerComponent->SetInteractionData(InteractionData);
	}
}

void APickupInteractive::BeginPlay()
{
	Super::BeginPlay();

	InteractionTriggerComponent->SetInteractionData(InteractionData);
}

FInteractionData APickupInteractive::GetInteractionData() const
{
	return InteractionData;
}

void APickupInteractive::SetInteractionData(const FInteractionData& Value)
{
	InteractionData = Value;
}

bool APickupInteractive::FinishInteraction_Implementation(AActor* OtherActor)
{
	return ActivatePickup(OtherActor);
}
