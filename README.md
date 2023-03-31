# TrickyPickups

A plugin with different base pickup classes

## Dependencies

This plugin required this plugins to work:

1. [**TrickyInteractionSystem**](https://github.com/TrickyFatCat/TrickyInteractionSystem/releases) v2.0 and higher;
2. [**TrickyAnimationComponents**](https://github.com/TrickyFatCat/TrickyAnimationComponents/releases) v2.0 and higher;

Install them before installing this plugin.

## Installation

The plugin can be used in both C++ and Blueprint projects.

### Blueprint projects

1. Download the latest [**package file**](https://github.com/TrickyFatCat/TrickyPickups/releases);
2. Install the plugin either in your project or for all projects in engine:
   * Unzip the package into Plugins folder of your project, e.g. `D:\UnrealProjects\MyProject\Plugins`;
   * Unzip the package to the Plugins folder in engine folder, e.g. `C:\Program Files\Epic Games\UE_5.0\Engine\Plugins`;
3. Restart the project;

In this case the plugin can be used for any blueprint project.

### C++ projects

1. Create the Plugins folder in the project directory;
2. Create the TrickyAnimationComponents folder in the Plugins folder;
3. Download the plugin source code into that folder;
4. Rebuild the project;

## Content

The plugin contains actors:

1. PickupEffectType;
2. PickupEffectsComponent;
3. PickupBase;
4. PickupNormal;
5. PickupInteractive;

### PickupEffectType

A class for creation of pickup effects.

#### Functions

1. `ActivatePickupEffect` - override this function to implement pickup effect logic;

### PickupEffectsComponent

A component which handles pickup effects activation.

#### Variables

1. `MainEffectType` - the class of the main pickup effect;
2. `SecondayEffectsTypes` - an array of secondary effects classes;

#### Functions

1. `ActivatePickupEffects` - activates pickup effects:
   1. First it tries to activate Main Effect;
   2. If it was successful, it activates secondary effects;

#### Delegates

1. `OnMainEffectActivated` - called when the main pickup effect successfully activated;
2. `OnSecondaryEffectActivated` - called when the secondary effect successfully activated;


### PickupBase

A base pickup class which contains the main logic.

#### Variables

1. `MainEffectType` - the class of the main pickup effect;
2. `SecondayEffectsTypes` - an array of secondary effects classes;
3. `DestroyOnActivation` - if true the pickup actor will be destroyed on activation, else it'll be disabled and hidden in game;
4. `InterpolateToTarget` - if true the actor will be interpolated to the target using EaseAnimationComponent from [**
   TrickyAnimationComponents**](https://github.com/TrickyFatCat/TrickyAnimationComponents);
5. `ActivationDistance` - determines the distance from the target actor the `ActivatePickup` function will be called.
   Worked only if `InterpolateToTarget == true`;

#### Functions

1. `ActivatePickup` - activates the pickup logic. Call this function if you want to activate the pickup in your custom
   pickup class;
2. `EnablePickup` - enables pickup if it was disabled when `DestroyOnActivation == false`;

#### Events

1. `OnPickupEffectActivated` - called when the pickup effect was successfully activated;
2. `OnPickupEnabled` - called when the pickup was enabled;
3. `OnPickupDisabled` - called when the pickup was disabled;

#### Delegates

1. `OnPickupActivated` - called when the pickup effect was successfully activated;

### PickupNormal

A pickup which activates if an actor enters an activation trigger.

### PickupInteractive

A pickup which activates by interacting with it. Override the `Interact` function to add additional checks and avoid
some strange behavior.