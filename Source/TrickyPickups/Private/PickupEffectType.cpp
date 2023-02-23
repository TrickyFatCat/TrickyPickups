// MIT License Copyright. Created by Artyom "Tricky Fat Cat" Volkov


#include "PickupEffectType.h"

bool UPickupEffectType::ActivateEffect_Implementation(AActor* OtherActor)
{
	if (!IsValid(OtherActor))
	{
		return false;
	}
	
	return true;
}
