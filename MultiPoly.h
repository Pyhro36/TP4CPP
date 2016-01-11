#include <vector>
#include <string>
#include "Shape.h"
#include "Point.h"

/// class MultiPoly -
class MultiPoly {
  // Attributes
protected:
  std::vector<Shape> shapes;
  // Operations
public:
  MultiPoly (std::string PolysName, std::vector<Shape> shapesList);
  virtual bool contain (Point point) = 0;
  void move (Point vector);
  virtual std::string describe () = 0;
};

