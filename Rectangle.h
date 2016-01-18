#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Polygon.h"
#include "Point.h"

/// class Rectangle - 
class Rectangle : public Polygon {
    // Operations
public:
    Rectangle(const std::string &RectName, const Point &firstCorner, const Point &secondCorner);


    virtual bool contain(const Point &point) const;
    std::string describe() const;

private:
    int xMax, xMin, yMax, yMin;
};

#endif
