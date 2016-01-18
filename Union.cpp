#include <sstream>
#include "Union.h"

Union::Union(const std::string & UnionName,const std::vector<std::shared_ptr<Shape>> & shapes): MultiPoly(UnionName, shapes)
{

}

bool Union::contain(const Point & point) const
{
    for(const Shape* shape : shapes)
    {
        if(shape->contain(point))
        {
            return true; //at least one of the shape does contain the point
        }
    }
    return false;
}

std::string Union::describe() const
{
    std::stringstream ret;
    //to create all the shape needed for the Union:
    for(const Shape * s : shapes)
    {
        ret << s->describe();
    }
    //Union creation:
    ret << "OR " << name;
    for(const Shape* s: shapes)
    {
        ret << " " << s->getName();
    }
    ret << std::endl;
    //delete all the unnecessary shapes:
    ret << "DELETE";
    for(const Shape* s: shapes)
    {
        ret << " " << s->getName();
    }
    ret << std::endl;
    return ret.str();
}

Shape* Union::clone() const
{
    return new Union(*this);
}