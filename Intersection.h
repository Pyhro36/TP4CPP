#include <string>
#include <vector>
#include "Point.h"
#include "MultiPoly.h"
#include "Shape.h"

/// class Intersection - 
class Intersection : public MultiPoly {
  // Operations
public:
  Intersection (std::string interName, std::vector<Shape> shapes);
  bool contain (Point point);
  std::string describe ();
};

