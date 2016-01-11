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
  Polygon (std::string polyName, std::vector<Point> polyPoints);
  bool contains (Point point);
  void move (Point vector);
  std::string describe ();
};

