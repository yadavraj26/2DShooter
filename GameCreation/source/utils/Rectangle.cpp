#include "../../include/utils/Rectangle.h"


bool Rectangle::inside(float x, float y) const
{
    // Implement this function, that returns true if the point <x,y> is inside this rectangle.
    if (x > topLeft.x && x<bottomRight.x && y>topLeft.y && y < bottomRight.y)
        return true; 
    return false;
}

bool Rectangle::intersects(const Rectangle& rect) const
{
    // Implement this function, that returns true if the rectangle "rect" overlaps with this rectangle.
    if(rect.getTopLeft().x>bottomRight.x||topLeft.x>rect.getBottomRight().x|| rect.getTopLeft().y>bottomRight.y||rect.getBottomRight().y<topLeft.y)
        return false;
    return true;
}

