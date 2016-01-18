#include "Shape.h"

Shape::Shape(const std::string & shapeName): name(shapeName)
{

}

void Shape::appendToName(const std::string & newNameEnding)
{
    name.append(newNameEnding);
}

std::string Shape::getName() const
{
    return name;
}