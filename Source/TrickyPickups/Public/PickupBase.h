// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

class UEaseAnimationComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickupActivatedSignature);

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

	UPROPERTY(BlueprintAssignable, Category="Pickup")
	FOnPickupActivatedSignature OnPickupActivated;

	UFUNCTION
	(BlueprintCallable, Category="Pickup")
	void ActivatePickup(AActor* OtherActor);

	UFUNCTION(BlueprintCallable, Category="Pickup")
	virtual void EnablePickup();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess))
	UEaseAnimationComponent* EaseAnimationComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Pickup")
	bool bDestroyOnActivation = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Pickup")
	bool bInterpolateToTarget = false;
	
	UFUNCTION(BlueprintNativeEvent, Category="Pickup")
	bool PickupEffect(AActor* OtherActor);

	virtual bool PickupEffect_Implementation(AActor* OtherActor);

	UFUNCTION(BlueprintImplementableEvent, Category="Pickup")
	void OnPickupEffectActivated(AActor* OtherActor);

	virtual void DisablePickup();

	UFUNCTION(BlueprintImplementableEvent, Category="Pickup")
	void OnPickupEnabled();

	UFUNCTION(BlueprintImplementableEvent, Category="Pickup")
	void OnPickupDisabled();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Pickup", meta=(AllowPrivateAccess, EditCondition="bInterpolateToTarget"))
	float ActivationDistance = 32.f;
	
	UPROPERTY()
	AActor* TargetActor = nullptr;
	
	void ActivatePickupEffect();
};
