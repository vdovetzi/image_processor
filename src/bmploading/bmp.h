#pragma once

#include <fstream>
#include <vector>
#include "../cmd/parser.h"
struct BMPHeader {
    uint16_t fileType;    // файл должен начинаться со строки "BM"
    uint32_t fileSize;    // размер файла в байтах
    uint16_t reserved1;   // зарезервированные байты (должны быть 0)
    uint16_t reserved2;   // зарезервированные байты (должны быть 0)
    uint32_t dataOffset;  // смещение до начала данных изображения
} __attribute__((__packed__));

struct DIBHeader {
    uint32_t headerSize;  // размер заголовка (в байтах)
    int32_t width;        // ширина изображения в пикселях
    int32_t height;       // высота изображения в пикселях
    uint16_t planes;      // число плоскостей (должно быть 1)
    uint16_t bitDepth;  // число бит на пиксель (24 для 24-битных RGB изображений)
    uint32_t compressionType;  // тип сжатия (обычно 0 для несжатых изображений)
    uint32_t dataSize;  // размер данных сжатых значений пикселей (может быть 0 для несжатых изображений)
    int32_t horizontalResolution;  // горизонтальное разрешение изображения в пикселях на метр
    int32_t verticalResolution;  // вертикальное разрешение изображения в пикселях на метр
    uint32_t numColors;  // число цветов в цветовой таблице (может быть 0 для 24-битных изображений)
    uint32_t importantColors;  // число "важных" цветов (обычно 0)
} __attribute__((__packed__));

struct RGB {
    RGB() : b(0), g(0), r(0){};

    RGB(uint8_t b, uint8_t g, uint8_t r) : b(b), g(g), r(r){};
    uint8_t b;
    uint8_t g;
    uint8_t r;
} __attribute__((__packed__));

struct Colour {
    double b = 0;
    double g = 0;
    double r = 0;
};

using Vector = std::vector<std::vector<RGB>>;

class Bitmap;

class PixelMatrix {
public:
    PixelMatrix() = default;
    void Resize(Bitmap& bmp, int32_t width, int32_t height);

    void SetPixel(int32_t x, int32_t y, RGB color);

    void SetPixelsMatrix(int32_t height, int32_t width);

    int32_t Width() const;
    int32_t Height() const;

    Vector& GetMatrix();

    Vector GetNeighbours(int32_t row, int32_t column);

protected:
    Vector bitmap;
};

class Bitmap {
public:
    Bitmap() = default;
    PixelMatrix& Pixels();
    BMPHeader& GetHeader();

    DIBHeader& GetDIBHeader();

protected:
    PixelMatrix bitmap;
    BMPHeader header;
    DIBHeader dib_header;
};

void ReadBmp(const std::string& filepath, Bitmap& bmp);

void WriteBmp(const std::string& filepath, Bitmap& bmp);

void Run(Parser& cmd);