#pragma once

#include "base.h"
#include "grayscale.h"
class EdgeDetectionFilter : public BaseFilter {
public:
    void Apply(Params& filters, Bitmap& bmp) override;

protected:
    const MyMatrix matrix = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
};
