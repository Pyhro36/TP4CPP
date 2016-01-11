#include "Polygon.h"

/// class Segment - 
class Segment : public Polygon {
  // Operations
public:
  Segment (std::string name, Point firstPoint, Point secondPoint);
  bool contains (Point point);
  std::string describe ();
};

