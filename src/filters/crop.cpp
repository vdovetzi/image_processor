#include "crop.h"

void CropFilter::Apply(Params& filters, Bitmap& bmp) {
    int32_t width = std::stoi(std::string(filters[0]));
    int32_t height = std::stoi(std::string(filters[1]));
    bmp.Pixels().Resize(bmp, width, height);
}
