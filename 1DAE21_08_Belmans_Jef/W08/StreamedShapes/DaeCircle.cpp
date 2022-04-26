#include "pch.h"		
#include "DaeCircle.h"

DaeCircle::DaeCircle( const Point2f &center, float diameter, const Color4f &color, bool isFilled )
: DaeEllipse::DaeEllipse(center, diameter, diameter, color, isFilled)
{
}

std::string DaeCircle::ToString()
{
    std::string properties{ "<DaeCircle\n" };
    properties += DaeShape::PropertiesToString() + "\n/>\n\n";

    return properties;
}
