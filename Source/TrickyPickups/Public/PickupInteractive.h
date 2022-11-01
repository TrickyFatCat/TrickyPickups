// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "InteractionInterface.h"
#include "PickupInteractive.generated.h"

class USphereInteractionTrigger;
/**
 * A pickup which activates by interacting with it. Override the Interact function with parent call to add additional checks and avoid some strange behavior.
 */
UCLASS()
class TRICKYPICKUPS_API APickupInteractive : public APickupBase, public IInteractionInterface
{
	GENERATED_BODY()

public:
	APickupInteractive();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	USphereInteractionTrigger* InteractionTrigger = nullptr;

private:
	virtual bool Interact_Implementation(AActor* OtherActor) override;
};
