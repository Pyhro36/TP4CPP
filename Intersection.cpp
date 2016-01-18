#include <sstream>
#include "Intersection.h"

Intersection::Intersection(const std::string & interName,const std::vector<Shape*> & shapes): MultiPoly(interName,shapes)
{

}

bool Intersection::contain(const Point & point) const
{
    for(const Shape* shape : shapes)
    {
        if(!shape->contain(point))
        {
            return false; //at least one of the shape doesn't contain the point
        }
    }
    return true;
}

std::string Intersection::describe() const
{
    std::stringstream ret;
    //to create all the shape needed for the Union:
    for(const Shape * s : shapes)
    {
        ret << s->describe();
    }
    //Union creation:
    ret << "OI " << name;
    for(const Shape * s : shapes)
    {
        ret << " " << s->getName();
    }
    ret << std::endl;
    //delete all the unnecessary shapes:
    ret << "DELETE";

    for(const Shape * s : shapes)
    {
        ret << " " << s->getName();
    }
    ret << std::endl;
    return ret.str();
}

Shape* Intersection::clone() const
{
    return new Intersection(*this);
}
