#include "negative.h"
#include "../tools.h"

void NegativeFilter::Apply(Params& filters, Bitmap& bmp) {
    for (size_t i = 0; i < bmp.Pixels().Height(); ++i) {
        for (size_t j = 0; j < bmp.Pixels().Width(); ++j) {
            RGB& pixel = bmp.Pixels().GetMatrix()[i][j];
            uint8_t red = TransformColour(pixel.r);
            uint8_t green = TransformColour(pixel.g);
            uint8_t blue = TransformColour(pixel.b);
            pixel = {blue, green, red};
        }
    }
}
