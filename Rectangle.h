#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Polygon.h"
#include "Point.h"

/// class Rectangle - 
class Rectangle : public Polygon {
  // Operations
public:
  virtual bool contain (Point point) const;
  Rectangle (std::string RectName, Point firstCorner, Point secondCorner);
  std::string describe () const;

private:
    int xMax, xMin, yMax, yMin;
};

#endif