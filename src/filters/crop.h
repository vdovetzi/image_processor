#pragma once

#include "base.h"

class CropFilter : public BaseFilter {
public:
    void Apply(Params& filter, Bitmap& bmp) override;
};
