#pragma once

#include <cstdint>
#include "bmploading/bmp.h"

using Vector = std::vector<std::vector<RGB>>;
using MyMatrix = std::vector<std::vector<int32_t>>;

uint8_t TransformColour(uint8_t colour);

void ApplySharpeningMatrix(Bitmap& bmp, const MyMatrix& matrix);

void ApplyEdgeMatrix(Bitmap& bmp, const MyMatrix& matrix, double threshold);

std::vector<double> Multiply(Vector& neighbours, const MyMatrix& matrix);

RGB NormalizePixel(Colour pixel);

std::vector<double> GenerateKernel(int n, double sigma);

Colour AdjustColor(Colour& color);

double Min(const double num1, const double num2);
double Max(const double num1, const double num2);
