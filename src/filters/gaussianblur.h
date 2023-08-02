#pragma once

#include "base.h"

class GaussianBlurFilter : public BaseFilter {
public:
    void Apply(Params& filters, Bitmap& bmp) override;
};