// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickupEffectsComponent.generated.h"

class UPickupEffectType;
class AActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMainEffectActivatedSignature, TSubclassOf<UPickupEffectType>, PickupEffectType);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSecondaryEffectActivatedSignature, TSubclassOf<UPickupEffectType>, PickupEffectType);

UCLASS(ClassGroup=(TrickyPickups), meta=(BlueprintSpawnableComponent))
class TRICKYPICKUPS_API UPickupEffectsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPickupEffectsComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(BlueprintAssignable, Category="Pickup")
	FOnMainEffectActivatedSignature OnMainEffectActivated;

	UPROPERTY(BlueprintAssignable, Category="Pickup")
	FOnSecondaryEffectActivatedSignature OnSecondaryEffectActivated;
	
	UFUNCTION(BlueprintCallable, Category="Pickup")
	bool ActivatePickupEffect(AActor* OtherActor);
	
	UFUNCTION(BlueprintSetter, Category="Pickup")
	void SetMainEffectType(TSubclassOf<UPickupEffectType> Value);

	UFUNCTION(BlueprintGetter, Category="Pickup")
	TSubclassOf<UPickupEffectType> GetMainEffectType() const;

	UFUNCTION(BlueprintCallable, Category="Pickup")
	void SetSecondaryEffectsTypes(const TArray<TSubclassOf<UPickupEffectType>>& Value);

	UFUNCTION(BlueprintCallable, Category="Pickup")
	void GetSecondaryEffectsTypes(TArray<TSubclassOf<UPickupEffectType>>& Value);
	

protected:
	UPROPERTY(EditDefaultsOnly,
		BlueprintGetter=GetMainEffectType,
		BlueprintSetter=SetMainEffectType,
		Category="Pickup")
	TSubclassOf<UPickupEffectType> MainEffectType = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Pickup")
	TArray<TSubclassOf<UPickupEffectType>> SecondaryEffectsTypes;

	UPROPERTY(BlueprintReadOnly, Category="Pickup")
	UPickupEffectType* MainEffect = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="Pickup")
	TArray<UPickupEffectType*> SecondaryEffects;
};
