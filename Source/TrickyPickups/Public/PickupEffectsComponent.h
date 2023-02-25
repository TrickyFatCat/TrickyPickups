// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickupEffectsComponent.generated.h"

class UPickupEffectType;
class AActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMainEffectActivatedSignature, UPickupEffectType*, PickupEffect);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSecondaryEffectActivatedSignature, UPickupEffectType*, PickupEffect);

/**
 * A component which handles activating pickup effects.
 */
UCLASS(ClassGroup=(TrickyPickups), meta=(BlueprintSpawnableComponent))
class TRICKYPICKUPS_API UPickupEffectsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPickupEffectsComponent();

protected:
	virtual void InitializeComponent() override;

public:
	/**Called when the main effect were activated.*/
	UPROPERTY(BlueprintAssignable, Category="Pickup")
	FOnMainEffectActivatedSignature OnMainEffectActivated;

	/**Called when the secondary effect were activated.*/
	UPROPERTY(BlueprintAssignable, Category="Pickup")
	FOnSecondaryEffectActivatedSignature OnSecondaryEffectActivated;

	/**
	 *Activates pickup effects.
	 *
	 *First it tries to activate main effect, if true, it activates secondary effects.
	 */
	UFUNCTION(BlueprintCallable, Category="Pickup")
	bool ActivatePickupEffects(AActor* OtherActor);
	
	UFUNCTION(BlueprintSetter, Category="Pickup")
	void SetMainEffectType(TSubclassOf<UPickupEffectType> Value);

	UFUNCTION(BlueprintGetter, Category="Pickup")
	TSubclassOf<UPickupEffectType> GetMainEffectType() const;

	UFUNCTION(BlueprintCallable, Category="Pickup")
	void SetSecondaryEffectsTypes(const TArray<TSubclassOf<UPickupEffectType>>& Value);

	UFUNCTION(BlueprintCallable, Category="Pickup")
	void GetSecondaryEffectsTypes(TArray<TSubclassOf<UPickupEffectType>>& Value);
	

protected:
	/**Main effect type.*/
	UPROPERTY(EditDefaultsOnly,
		BlueprintGetter=GetMainEffectType,
		BlueprintSetter=SetMainEffectType,
		Category="Pickup")
	TSubclassOf<UPickupEffectType> MainEffectType = nullptr;

	/**List of secondary effects types.*/
	UPROPERTY(EditDefaultsOnly, Category="Pickup")
	TArray<TSubclassOf<UPickupEffectType>> SecondaryEffectsTypes;

	UPROPERTY(BlueprintReadOnly, Category="Pickup")
	UPickupEffectType* MainEffect = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category="Pickup")
	TArray<UPickupEffectType*> SecondaryEffects;
};
