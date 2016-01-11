#include "Polygon.h"

/// class Rectangle - 
class Rectangle : public Polygon {
  // Operations
public:
  bool contains (Point point);
  Rectangle (std::string RectName, Point firstCorner, Point secondCorner);
  std::string describe ();
};

