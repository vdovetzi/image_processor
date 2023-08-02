#include "sharpening.h"
#include "../tools.h"

void SharpeningFilter::Apply(Params& filters, Bitmap& bmp) {
    ApplySharpeningMatrix(bmp, matrix);
}
