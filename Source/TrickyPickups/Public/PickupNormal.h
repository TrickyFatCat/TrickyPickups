// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "PickupNormal.generated.h"

class USphereComponent;

/**
 * 
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
	USphereComponent* ActivationTrigger = nullptr;

private:
	UFUNCTION()
	void OnActivationTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                                     AActor* OtherActor,
	                                     UPrimitiveComponent* OtherComp,
	                                     int32 OtherBodyIndex,
	                                     bool bFromSweep,
	                                     const FHitResult& SweepResult);
};
