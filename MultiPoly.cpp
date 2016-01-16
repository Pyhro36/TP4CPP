#include "MultiPoly.h"

MultiPoly::MultiPoly(std::string PolysName, std::vector< std::shared_ptr<Shape> > shapesList): Shape(PolysName), shapes(shapesList)
{
    //rename all the entities in shapesList:
    std::string toAdd = "-";
    toAdd.append(name);
    for(std::shared_ptr<Shape> & s:shapes)
    {
        s->appendToName(toAdd);
    }
}

void MultiPoly::move(Point vector)
{
    for(std::shared_ptr<Shape> & shape : shapes)
    {
        shape->move(vector);
    }
}

void MultiPoly::appendToName(std::string newNameEnding)
{
    Shape::appendToName(newNameEnding);
    for(std::shared_ptr<Shape> & s:shapes)
    {
        s->appendToName(newNameEnding);
    }
}
