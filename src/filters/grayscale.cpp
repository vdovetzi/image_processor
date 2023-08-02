#include "grayscale.h"

void GrayScaleFilter::Apply(Params& filters, Bitmap& bmp) {
    for (size_t i = 0; i < bmp.Pixels().Height(); ++i) {
        for (size_t j = 0; j < bmp.Pixels().Width(); ++j) {
            RGB& pixel = bmp.Pixels().GetMatrix()[i][j];
            const uint8_t formulae = static_cast<uint8_t>(0.299 * pixel.r + 0.587 * pixel.g + 0.114 * pixel.b);
            pixel = {formulae, formulae, formulae};
        }
    }
}
