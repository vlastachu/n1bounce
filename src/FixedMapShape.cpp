#include "FixedMapShape.h"
#include "defs.h"

void FixedMapShape::move(float dx)
{
	x -= dx;
}
float FixedMapShape::getw()
{
	return w;
}

float FixedMapShape::geth()
{
	return h;
}