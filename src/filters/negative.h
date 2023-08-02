#pragma once

#include "base.h"

class NegativeFilter : public BaseFilter {
public:
    void Apply(Params& filters, Bitmap& bmp) override;
};