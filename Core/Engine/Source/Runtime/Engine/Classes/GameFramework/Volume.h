#pragma once
#include "pch.h"

#include "Actor.h"
#include "Engine/Source/Runtime/Engine/Classes/Components/BrushComponent.h"

class UModel;

class ABrush : public AActor {
public:
	DefineUnrealClass(ABrush);

	DefineUProperty(UModel*, Brush);
	DefineUProperty(UBrushComponent*, BrushComponent);
};

class AVolume : public ABrush {
public:
	DefineUnrealClass(AVolume);
};
