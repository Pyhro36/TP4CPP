#include "MultiPoly.h"

MultiPoly::MultiPoly(const std::string & PolysName,const std::vector<Shape*> & shapesList): Shape(PolysName), shapes(shapesList)
{
    //rename all the entities in shapesList:
    std::string toAdd = "-";
    toAdd.append(name);
    for(Shape* s:shapes)
    {
        s->appendToName(toAdd);
    }
}

MultiPoly::MultiPoly(const MultiPoly &multypolyToClone): Shape(multypolyToClone.getName())
{
    //TODO check if it work...
    for(Shape* s:multypolyToClone.shapes)
    {
        //call the copy constructor of every Shape (so it is recursive)
        //shapes.push_back(new Shape(*s)); //did it really work ?
        shapes.push_back(s->clone());
    }
}

MultiPoly::~MultiPoly()
{
    for(Shape* s:shapes)
    {
        delete s;
    }
}

void MultiPoly::move(const Point & vector)
{
    for(Shape* shape : shapes)
    {
        shape->move(vector);
    }
}

void MultiPoly::appendToName(const std::string & newNameEnding)
{
    Shape::appendToName(newNameEnding);
    for(Shape* s:shapes)
    {
        s->appendToName(newNameEnding);
    }
}
