#include "tools.h"
#include <cmath>

uint8_t TransformColour(uint8_t colour) {
    const double max_size = 255.0;
    return static_cast<uint8_t>(std::round((1 - (static_cast<double>(colour) / max_size)) * max_size));
}

RGB NormalizePixel(Colour pixel) {
    return RGB(static_cast<uint8_t>(pixel.b), static_cast<uint8_t>(pixel.g), static_cast<uint8_t>(pixel.r));
}

double Max(const double num1, const double num2) {
    return num1 >= num2 ? num1 : num2;
}

double Min(const double num1, const double num2) {
    return num1 <= num2 ? num1 : num2;
}

Colour AdjustColor(Colour& color) {
    const int max_size = 255;
    Colour rgb;

    // Красный канал
    rgb.r = color.r * 0.393 + color.g * 0.769 + color.b * 0.189;  // NOLINT
    rgb.r = Min(max_size, rgb.r);

    // Зеленый канал
    rgb.g = color.r * 0.349 + color.g * 0.686 + color.b * 0.168;  // NOLINT
    rgb.g = Min(max_size, rgb.g);

    // Синий канал
    rgb.b = color.r * 0.272 + color.g * 0.534 + color.b * 0.131;  // NOLINT
    rgb.b = Min(max_size, rgb.b);

    color.r = rgb.r;
    color.g = rgb.g;
    color.b = rgb.b;

    return color;
}

// Gaussian function
double Gaussian(double x, double sigma) {
    const double num = 2.0;
    return exp(-(x * x) / (num * sigma * sigma)) / (sqrt(num * M_PI) * sigma);
}

std::vector<double> GenerateKernel(int32_t n, double sigma) {
    std::vector<double> kernel(n);
    int32_t mid = n / 2;

    for (int32_t i = 0; i < n; ++i) {
        kernel[i] = Gaussian(i - mid, sigma);
    }

    // Normalize the kernel coefficients
    double sum = 0.0;
    for (int32_t i = 0; i < n; ++i) {
        sum += kernel[i];
    }

    for (int32_t i = 0; i < n; ++i) {
        kernel[i] /= sum;
    }

    return kernel;
}

std::vector<double> Multiply(Vector& neighbours, const MyMatrix& matrix) {
    const uint8_t max_size = 255;
    double ans_r = 0;
    double ans_g = 0;
    double ans_b = 0;
    for (int32_t i = 0; i < matrix.size(); ++i) {
        for (int32_t j = 0; j < matrix[0].size(); ++j) {
            ans_r += neighbours[i][j].r * matrix[i][j];
            ans_g += neighbours[i][j].g * matrix[i][j];
            ans_b += neighbours[i][j].b * matrix[i][j];
        }
    }
    ans_r = Min(max_size, Max(0, ans_r));
    ans_g = Min(max_size, Max(0, ans_g));
    ans_b = Min(max_size, Max(0, ans_b));

    return {ans_r, ans_g, ans_b};
}

void ApplySharpeningMatrix(Bitmap& bmp, const MyMatrix& matrix) {
    Vector neighbours;
    std::vector<double> ans;
    Vector temp = std::vector(bmp.Pixels().Height(), std::vector<RGB>(bmp.Pixels().Width()));
    for (int32_t row = 0; row < bmp.Pixels().Height(); ++row) {
        for (int32_t column = 0; column < bmp.Pixels().Width(); ++column) {
            neighbours = bmp.Pixels().GetNeighbours(row, column);
            ans = Multiply(neighbours, matrix);
            RGB pixel = {static_cast<uint8_t>(ans[2]), static_cast<uint8_t>(ans[1]), static_cast<uint8_t>(ans[0])};

            temp[row][column] = pixel;
        }
    }
    bmp.Pixels().GetMatrix() = temp;
}

void ApplyEdgeMatrix(Bitmap& bmp, const MyMatrix& matrix, double threshold) {
    const uint8_t max_size = 255;
    Vector neighbours;
    std::vector<double> ans;
    Vector temp = std::vector(bmp.Pixels().Height(), std::vector<RGB>(bmp.Pixels().Width()));
    for (int32_t row = 0; row < bmp.Pixels().Height(); ++row) {
        for (int32_t column = 0; column < bmp.Pixels().Width(); ++column) {
            neighbours = bmp.Pixels().GetNeighbours(row, column);
            ans = Multiply(neighbours, matrix);
            for (double colour : ans) {
                if (colour > threshold * max_size) {
                    ans = {1, 1, 1};
                    break;
                } else {
                    ans = {0, 0, 0};
                    break;
                }
            }
            RGB pixel = {static_cast<uint8_t>(ans[2] * max_size), static_cast<uint8_t>(ans[1] * max_size),
                         static_cast<uint8_t>(ans[0] * max_size)};
            temp[row][column] = pixel;
        }
    }
    bmp.Pixels().GetMatrix() = temp;
}