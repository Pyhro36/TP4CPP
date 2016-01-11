#include <string>
#include "MultiPoly.h"

/// class Union - 
class Union : public MultiPoly {
  // Operations
public:
  Union (std::vector<Shape> shapes, std::string UnionName);
  bool contains (Point point);
  std::string describe ();
};

