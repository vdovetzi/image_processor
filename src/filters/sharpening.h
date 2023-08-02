#pragma once

#include "base.h"

class SharpeningFilter : public BaseFilter {
public:
    void Apply(Params& filters, Bitmap& bmp) override;

protected:
    const MyMatrix matrix = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
};