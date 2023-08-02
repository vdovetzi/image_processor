#pragma once

#include "base.h"

class GrayScaleFilter : public BaseFilter {
public:
    void Apply(Params& filters, Bitmap& bmp) override;
};