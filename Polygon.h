#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <string>
#include "Point.h"
#include "Shape.h"

/// class Polygon -
class Polygon : public Shape{
  // Attributes
protected:
  std::vector<Point> points;
  // Operations
public:
  Polygon (const std::string & polyName,const std::vector<Point> & polyPoints = std::vector<Point>());
  virtual bool contain (const Point & point) const;
  void move (const Point & vector);
  virtual std::string describe () const;

private:
    bool isBetween(int x, int firstBound, int secondBound) const;
};

#endif
