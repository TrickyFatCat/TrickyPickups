# TrickyPickups

A plugin with different base pickup classes

## Dependencies

This plugin required this plugins to work:

1. [**TrickyInteractionSystem**](https://github.com/TrickyFatCat/TrickyInteractionSystem);
2. [**TrickyAnimationComponents**](https://github.com/TrickyFatCat/TrickyAnimationComponents);

Install them before installing this plugin.

## Installation

The plugin can be used in both C++ and Blueprint projects.

### Blueprint projects

**At the moment, the package is compatible only with Unreal Engine 4.**

1. Download package file;
2. Unzip the package to the Plugins folder in engine folder, e.g. `C:\Program Files\Epic Games\UE_4.27\Engine\Plugins`;
3. Restart the project;

In this case the plugin can be used for any blueprint project.

### C++ projects

1. Create the Plugins folder in the project directory;
2. Create the TrickyAnimationComponents folder in the Plugins folder;
3. Download the plugin source code into that folder;
4. Rebuild the project;

## Content

The plugin contains actors:

1. PickupBase;
2. PickupNormal;
3. PickupInteractive;

### PickupBase

A base pickup class which contains the main logic.

#### Variables

1. `DestroyOnActivation` - if true the pickup actor will destroy on activation, else it'll be disabled and hidden in
   game;
2. `InterpolateToTarget` - if true the actor will be interpolated to the target using EaseAnimationComponent from [**
   TrickyAnimationComponents**](https://github.com/TrickyFatCat/TrickyAnimationComponents);
3. `ActivationDistance` - determines the distance from the target actor the `ActivatePickup` function will be called.
   Worked only if `InterpolateToTarget == true`;

#### Functions

1. `ActivatePickup` - activates the pickup logic. Call this function if you want to activate the pickup in your custom
   pickup class;
2. `EnablePickup` - enables pickup if it was disabled when `DestroyOnActivation == false`;
3. `PickupEffect` - a function which is called to activate the actual pickup effect. Override it to implement pickup
   effect;

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