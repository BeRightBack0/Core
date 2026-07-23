#pragma once
#include "pch.h"

#include "PrimitiveComponent.h"

class UModel;
class UBodySetup;

class UBrushComponent : public UPrimitiveComponent {
public:
	DefineUnrealClass(UBrushComponent);

	DefineUProperty(UModel*, Brush);
	DefineUProperty(UBodySetup*, BrushBodySetup);
};
