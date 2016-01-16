#ifndef UNION_H
#define UNION_H

#include <string>
#include "MultiPoly.h"

/// class Union - 
class Union : public MultiPoly {
  // Operations
public:
  Union (std::string UnionName,std::vector< std::shared_ptr<Shape> > shapes);
  bool contain (Point point) const;
  std::string describe () const;
};

#endif