// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

class UEaseAnimationComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickupActivatedSignature);

/**
 * A base pickup class which contains the main logic.
 */
UCLASS()
class TRICKYPICKUPS_API APickupBase : public AActor
{
	GENERATED_BODY()

public:
	APickupBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	/**
	 * Called when the pickup effect was successfully activated;
	 */
	UPROPERTY(BlueprintAssignable, Category="Pickup")
	FOnPickupActivatedSignature OnPickupActivated;

	/**
	 * Activates the pickup logic.
	 * Call this function if you want to activate the pickup in your custom pickup class.
	 */
	UFUNCTION(BlueprintCallable, Category="Pickup")
	bool ActivatePickup(AActor* OtherActor);

	/**
	 * Enables the pickup if it was disabled.
	 * Works if DestroyOnActivation == false.
	 */
	UFUNCTION(BlueprintCallable, Category="Pickup")
	virtual void EnablePickup();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess))
	USceneComponent* PickupRootComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess))
	UEaseAnimationComponent* EaseAnimationComponent = nullptr;

	/**
	 * If true the pickup actor will destroy on activation, else it'll be disabled and hidden in game.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Pickup")
	bool bDestroyOnActivation = true;

	/**
	 * If true the actor will be interpolated to the target using EaseAnimationComponent.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Pickup")
	bool bInterpolateToTarget = false;

	/**
	 * A function which is called to activate the actual pickup effect. Override it to implement pickup effect.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Pickup")
	bool PickupEffect(AActor* OtherActor);

	virtual bool PickupEffect_Implementation(AActor* OtherActor);

	/**
	 * Called when the pickup effect was successfully activated.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="Pickup")
	void OnPickupEffectActivated(AActor* OtherActor);

	virtual void DisablePickup();

	/**
	 * Called when the pickup was enabled.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="Pickup")
	void OnPickupEnabled();

	/**
	 * Called when the pickup wan disabled.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="Pickup")
	void OnPickupDisabled();

private:
	/**
	 * Determines the distance from the target actor the ActivatePickup function will be called.
	 */
	UPROPERTY(EditDefaultsOnly,
		BlueprintReadWrite,
		Category="Pickup",
		meta=(AllowPrivateAccess, EditCondition="bInterpolateToTarget"))
	float ActivationDistance = 32.f;

	UPROPERTY()
	AActor* TargetActor = nullptr;

	bool ActivatePickupEffect();

	void SetAnimationTargetLocation() const;
};
