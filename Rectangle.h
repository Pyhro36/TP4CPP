#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Polygon.h"
#include "Point.h"

/// class Rectangle - 
class Rectangle : public Polygon
{
	// Attributes
private:
    int xMax, xMin, yMax, yMin;
    // Operations
public:
    Rectangle(const std::string &RectName, const Point &firstCorner, const Point &secondCorner);
    bool contain(const Point &point) const;
    void move(const Point &vector);
    std::string describe() const;
    Shape* clone() const;
private:
    void resetMinMax();

};

#endif
