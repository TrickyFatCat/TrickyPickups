// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "PickupNormal.h"

#include "Components/SphereComponent.h"

APickupNormal::APickupNormal()
{
	PrimaryActorTick.bCanEverTick = true;

	ActivationTrigger = CreateDefaultSubobject<USphereComponent>("ActivationTrigger");
	ActivationTrigger->SetupAttachment(GetRootComponent());
	ActivationTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ActivationTrigger->SetCollisionObjectType(ECC_WorldDynamic);
	ActivationTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	ActivationTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void APickupNormal::BeginPlay()
{
	Super::BeginPlay();

	ActivationTrigger->OnComponentBeginOverlap.AddDynamic(this, &APickupNormal::OnActivationTriggerBeginOverlap);
}

void APickupNormal::OnActivationTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
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

	if (ActivatePickup(OtherActor))
	{
		ActivationTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ActivationTrigger->OnComponentBeginOverlap.Clear();
	}
}
