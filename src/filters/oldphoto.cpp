#include "oldphoto.h"
#include "../tools.h"

void OldPhotoFilter::Apply(Params& filters, Bitmap& bmp) {
    const double max_size = 255.0;
    const double c11 = 0.393;
    const double c12 = 0.769;
    const double c13 = 0.189;
    const double c21 = 0.349;
    const double c22 = 0.686;
    const double c23 = 0.168;
    const double c31 = 0.272;
    const double c32 = 0.534;
    const double c33 = 0.131;
    const double eps = 0.05;
    const double f11 = 1.2;
    const double f12 = 1.1;
    const double f13 = 1.3;
    const double f21 = 1.25;
    const double f22 = 1.15;
    int32_t height = bmp.Pixels().Height();
    int32_t width = bmp.Pixels().Width();
    Vector result(height, std::vector<RGB>(width));

    // Наложить эффект старой фотографии на каждый пиксель изображения
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            Colour pixel;
            pixel.r = bmp.Pixels().GetMatrix()[r][c].r * c11 + bmp.Pixels().GetMatrix()[r][c].g * c12 +
                      bmp.Pixels().GetMatrix()[r][c].b * c13;
            pixel.g = bmp.Pixels().GetMatrix()[r][c].r * c21 + bmp.Pixels().GetMatrix()[r][c].g * c22 +
                      bmp.Pixels().GetMatrix()[r][c].b * c23;
            pixel.b = bmp.Pixels().GetMatrix()[r][c].r * c31 + bmp.Pixels().GetMatrix()[r][c].g * c32 +
                      bmp.Pixels().GetMatrix()[r][c].b * c33;

            // Немного изменить яркость и контрастность
            pixel.r = Min((pixel.r * f11), max_size);
            pixel.g = Min((pixel.g * f12), max_size);
            pixel.b = Min((pixel.b * f13), max_size);

            // Применить случайный шум на некоторые пиксели
            double n = static_cast<double>(rand()) / RAND_MAX;
            if (n < eps) {
                pixel.r = Min(pixel.r * f21, max_size);
                pixel.g = Min(pixel.g * f11, max_size);
                pixel.b = Min(pixel.b * f22, max_size);
            }

            // Немного изменить тон
            pixel = AdjustColor(pixel);
            result[r][c] = NormalizePixel(pixel);
        }
    }
    bmp.Pixels().GetMatrix() = result;
}
