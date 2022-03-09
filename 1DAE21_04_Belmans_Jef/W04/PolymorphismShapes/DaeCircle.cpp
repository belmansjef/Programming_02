#include "pch.h"		
#include "DaeCircle.h"

DaeCircle::DaeCircle( const Point2f &center, float diameter, const Color4f &color, bool isFilled )
: DaeEllipse::DaeEllipse(center, diameter, diameter, color, isFilled)
{
}