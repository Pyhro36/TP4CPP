#include <sstream>
#include "Intersection.h"

Intersection::Intersection(std::string interName, std::vector< std::shared_ptr<Shape> > shapes): MultiPoly(interName,shapes)
{

}

bool Intersection::contain(Point point) const
{
    for(const std::shared_ptr<Shape> & shape : shapes)
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
    for(const std::shared_ptr<Shape> & s : shapes)
    {
        ret << s->describe();
    }
    //Union creation:
    ret << "OI " << name;
    for(const std::shared_ptr<Shape> & s : shapes)
    {
        ret << " " << s->getName();
    }
    ret << std::endl;
    //delete all the unnecessary shapes:
    ret << "DELETE";
    for(const std::shared_ptr<Shape> & s : shapes)
    {
        ret << " " << s->getName();
    }
    ret << std::endl;
}
