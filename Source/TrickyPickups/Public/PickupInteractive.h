// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "InteractionInterface.h"
#include "InteractionLibrary.h"
#include "PickupInteractive.generated.h"

class USphereComponent;
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
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Pickup")
	FInteractionData InteractionData;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	USphereComponent* InteractionTriggerComponent = nullptr;

private:
	virtual bool FinishInteraction_Implementation(AActor* OtherActor) override;

	UFUNCTION()
	void OnInteractionTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                                      AActor* OtherActor,
	                                      UPrimitiveComponent* OtherComp,
	                                      int32 OtherBodyIndex,
	                                      bool bFromSweep,
	                                      const FHitResult& SweepResult);
	UFUNCTION()
	void OnInteractionTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent,
	                                    AActor* OtherActor,
	                                    UPrimitiveComponent* OtherComp,
	                                    int32 OtherBodyIndex);
};
