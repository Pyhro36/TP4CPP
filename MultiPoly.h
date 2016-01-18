#ifndef MULTIPOLY_H
#define MULTIPOLY_H

#include <vector>
#include <string>
#include <memory>
#include "Shape.h"
#include "Point.h"

/// class MultiPoly -
class MultiPoly : public Shape
{
    // Attributes
protected:
    std::vector< std::shared_ptr<Shape> > shapes;
    // Operations
public:
    MultiPoly(const std::string & PolysName,const std::vector< std::shared_ptr<Shape>> & shapesList);
    virtual bool contain(const Point & point) const = 0;
    void move(const Point & vector);
    virtual std::string describe() const = 0;
    void appendToName(const std::string & newNameEnding);
};

#endif