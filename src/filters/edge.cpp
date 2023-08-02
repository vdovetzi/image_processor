#include "edge.h"
#include "../tools.h"
#include "grayscale.h"

void EdgeDetectionFilter::Apply(Params& filters, Bitmap& bmp) {
    GrayScaleFilter gs;
    gs.Apply(filters, bmp);
    ApplyEdgeMatrix(bmp, matrix, std::stod(std::string(filters[0])));
}
