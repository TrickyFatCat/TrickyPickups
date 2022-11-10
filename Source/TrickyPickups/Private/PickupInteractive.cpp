// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "PickupInteractive.h"

#include "InteractionLibrary.h"
#include "Components/SphereComponent.h"

APickupInteractive::APickupInteractive()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractionTriggerComponent = CreateDefaultSubobject<USphereComponent>("InteractionTrigger");
	InteractionTriggerComponent->SetupAttachment(GetRootComponent());
	UInteractionLibrary::SetTriggerDefaultCollision(InteractionTriggerComponent);
}

void APickupInteractive::BeginPlay()
{
	Super::BeginPlay();

	InteractionTriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupInteractive::OnInteractionTriggerBeginOverlap);
	InteractionTriggerComponent->OnComponentEndOverlap.AddDynamic(this, &APickupInteractive::OnInteractionTriggerEndOverlap);
}

bool APickupInteractive::FinishInteraction_Implementation(AActor* OtherActor)
{
	return ActivatePickup(OtherActor);
}

void APickupInteractive::OnInteractionTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                                          AActor* OtherActor,
                                                          UPrimitiveComponent* OtherComp,
                                                          int32 OtherBodyIndex,
                                                          bool bFromSweep,
                                                          const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor))
	{
		return;
	}

	UInteractionLibrary::AddToInteractionQueue(OtherActor, this, InteractionData);
}

void APickupInteractive::OnInteractionTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent,
                                                        AActor* OtherActor,
                                                        UPrimitiveComponent* OtherComp,
                                                        int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor))
	{
		return;
	}

	UInteractionLibrary::RemoveFromInteractionQueue(OtherActor, this);
}
