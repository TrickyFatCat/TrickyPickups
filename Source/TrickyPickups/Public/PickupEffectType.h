// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "PickupEffectType.generated.h"

class AActor;

/**
 * A class for creating custom pickup effects
 */
UCLASS(BlueprintType, Blueprintable)
class TRICKYPICKUPS_API UPickupEffectType : public UObject
{
	GENERATED_BODY()

public:
	/**Activates the pickup effect.*/
	UFUNCTION(BlueprintNativeEvent, Category="PickupEffectType")
	bool ActivateEffect(AActor* OtherActor);

	virtual bool ActivateEffect_Implementation(AActor* OtherActor);
};
