#pragma once

#include "../bmploading/bmp.h"
#include "../cmd/parser.h"

using Params = const std::vector<std::string_view>;
using MyMatrix = std::vector<std::vector<int32_t>>;

class BaseFilter {
public:
    virtual void Apply(Params& filter, Bitmap& bmp) = 0;
};

void ApplyFilters(std::vector<AppliedFilter>& filter_to_apply, Bitmap& bmp);