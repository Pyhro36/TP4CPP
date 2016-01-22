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
    void move(const Point &vector);
    std::string describe() const;
    Shape* clone() const;
private:
    void resetMinMax();
private:
    int xMax, xMin, yMax, yMin;
};

#endif
