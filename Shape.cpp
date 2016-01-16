#include "Shape.h"

Shape::Shape(std::string shapeName): name(shapeName)
{

}

void Shape::appendToName(std::string newNameEnding)
{
    name.append(newNameEnding);
}

std::string Shape::getName()
{
    return name;
}