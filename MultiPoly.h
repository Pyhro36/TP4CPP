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
    MultiPoly(std::string PolysName, std::vector< std::shared_ptr<Shape> > shapesList);
    virtual bool contain(Point point) const = 0;
    void move(Point vector);
    virtual std::string describe() const = 0;

protected:
    void appendToName(std::string newNameEnding);
};

#endif