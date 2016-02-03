#ifndef UNION_H
#define UNION_H

#include <string>
#include "MultiPoly.h"

/// class Union - 
class Union : public MultiPoly
{
    // Operations
public:
    Union(const std::string &UnionName, const std::vector<Shape*> &shapes);

    bool contain(const Point &point) const;
    std::string describe() const;
    Shape* clone() const;
};

#endif
