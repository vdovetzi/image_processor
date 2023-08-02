#include "gaussianblur.h"
#include "../tools.h"
#include <cmath>

void GaussianBlurFilter::Apply(Params& filters, Bitmap& bmp) {
    double sigma = std::stod(std::string(filters[0]));
    int32_t height = bmp.Pixels().Height();
    int32_t width = bmp.Pixels().Width();

    // Generate kernel coefficients
    int32_t n = static_cast<int32_t>(2 * ceil(3 * sigma) + 1);
    std::vector<double> kernel = GenerateKernel(n, sigma);

    // Convolve the kernel with each row of the image
    std::vector<std::vector<RGB>> blurred_image(height, std::vector<RGB>(width));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Colour new_pixel;

            for (int i = 0; i < n; ++i) {
                int idx = x + i - n / 2;

                if (idx < 0) {
                    idx = 0;
                }
                if (idx >= width) {
                    idx = width - 1;
                }

                new_pixel.r += kernel[i] * bmp.Pixels().GetMatrix()[y][idx].r;
                new_pixel.g += kernel[i] * bmp.Pixels().GetMatrix()[y][idx].g;
                new_pixel.b += kernel[i] * bmp.Pixels().GetMatrix()[y][idx].b;
            }

            blurred_image[y][x] = NormalizePixel(new_pixel);
        }
    }

    // Convolve the kernel with each column of the image
    std::vector<std::vector<RGB>> final_image(height, std::vector<RGB>(width));

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Colour new_pixel;

            for (int i = 0; i < n; ++i) {
                int idx = y + i - n / 2;

                if (idx < 0) {
                    idx = 0;
                }
                if (idx >= height) {
                    idx = height - 1;
                }

                new_pixel.r += kernel[i] * blurred_image[idx][x].r;
                new_pixel.g += kernel[i] * blurred_image[idx][x].g;
                new_pixel.b += kernel[i] * blurred_image[idx][x].b;
            }

            final_image[y][x] = NormalizePixel(new_pixel);
        }
    }
    bmp.Pixels().GetMatrix() = final_image;
}