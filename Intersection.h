#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <string>
#include <vector>
#include "Point.h"
#include "MultiPoly.h"
#include "Shape.h"

/// class Intersection - 
class Intersection : public MultiPoly {
    // Operations
public:
    Intersection(const std::string & interName,const std::vector<Shape*> & shapes);

    bool contain(const Point & point) const;
    std::string describe() const;
    Shape* clone() const;
};

#endif