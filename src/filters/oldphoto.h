#pragma once

#include "base.h"

class OldPhotoFilter : public BaseFilter {
public:
    void Apply(Params& filters, Bitmap& bmp) override;
};