#include "MultiPoly.h"

MultiPoly::MultiPoly(const std::string & PolysName,const std::vector<std::shared_ptr<Shape>> & shapesList): Shape(PolysName), shapes(shapesList)
{
    //rename all the entities in shapesList:
    std::string toAdd = "-";
    toAdd.append(name);
    for(std::shared_ptr<Shape> & s:shapes)
    {
        s->appendToName(toAdd);
    }
}

void MultiPoly::move(const Point & vector)
{
    for(std::shared_ptr<Shape> & shape : shapes)
    {
        shape->move(vector);
    }
}

void MultiPoly::appendToName(const std::string & newNameEnding)
{
    Shape::appendToName(newNameEnding);
    for(std::shared_ptr<Shape> & s:shapes)
    {
        s->appendToName(newNameEnding);
    }
}
