// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "PickupInteractive.h"

#include "InteractionTriggers/SphereInteractionTrigger.h"

APickupInteractive::APickupInteractive()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractionTrigger = CreateDefaultSubobject<USphereInteractionTrigger>("InteractionTrigger");
	InteractionTrigger->SetupAttachment(GetRootComponent());
}

bool APickupInteractive::Interact_Implementation(AActor* OtherActor)
{
	return ActivatePickup(OtherActor);
}
