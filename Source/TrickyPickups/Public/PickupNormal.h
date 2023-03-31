// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "PickupNormal.generated.h"

class USphereComponent;

/**
 * A pickup which activates if an actor enters an activation trigger.
 */
UCLASS()
class TRICKYPICKUPS_API APickupNormal : public APickupBase
{
	GENERATED_BODY()

public:
	APickupNormal();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<USphereComponent> ActivationTrigger = nullptr;

private:
	UFUNCTION()
	void HandleActivationTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                                     AActor* OtherActor,
	                                     UPrimitiveComponent* OtherComp,
	                                     int32 OtherBodyIndex,
	                                     bool bFromSweep,
	                                     const FHitResult& SweepResult);
};
