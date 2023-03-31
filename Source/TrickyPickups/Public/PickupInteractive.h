// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "InteractionInterface.h"
#include "InteractionLibrary.h"
#include "PickupInteractive.generated.h"

class USphereInteractionComponent;
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
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintGetter, Category="Pickup")
	FInteractionData GetInteractionData() const;

	UFUNCTION(BlueprintSetter, Category="Pickup")
	void SetInteractionData(const FInteractionData& Value);

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<USphereInteractionComponent> InteractionTriggerComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetInteractionData, BlueprintSetter=SetInteractionData,
		Category="Pickup")
	FInteractionData InteractionData;

private:
	virtual bool FinishInteraction_Implementation(AActor* OtherActor) override;
};
