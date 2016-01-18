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

MultiPoly::MultiPoly(const MultiPoly &multypolyToClone): Shape(multypolyToClone.getName())
{
    //TODO check if it work...
    for(std::shared_ptr<Shape> & s:multypolyToClone.shapes)
    {
        //call the copy constructor of every Shape (so it is recursive)
        shapes.push_back(std::shared_ptr<Shape>(std::make_shared<Shape>(s.get()))); //did it really work ?
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
