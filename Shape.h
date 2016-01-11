#include <string>
#include "Point.h"

/// class Shape -
class Shape {
  // Attributes
protected:
  std::string name;
  // Operations
public:
  Shape (std::string shapeName);
  virtual bool contain (Point point) = 0;
  virtual void move (Point vector) = 0;
  virtual std::string describe () = 0;
};

