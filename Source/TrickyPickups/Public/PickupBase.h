// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

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
	void ActivatePickup(AActor* TargetActor);

	UFUNCTION(BlueprintCallable, Category="Pickup")
	virtual void EnablePickup();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Pickup")
	bool bDestroyOnActivation = true;
	
	UFUNCTION(BlueprintNativeEvent, Category="Pickup")
	bool ActivatePickupEffect(AActor* TargetActor);

	virtual bool ActivatePickupEffect_Implementation(AActor* TargetActor);

	UFUNCTION(BlueprintImplementableEvent, Category="Pickup")
	void OnPickupEffectActivated(AActor* TargetActor);

	virtual void DisablePickup();

	UFUNCTION(BlueprintImplementableEvent, Category="Pickup")
	void OnPickupEnabled();

	UFUNCTION(BlueprintImplementableEvent, Category="Pickup")
	void OnPickupDisabled();
};
