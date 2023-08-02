#include "bmp.h"
#include "../filters/base.h"
#include "../cmd/exceptions.h"
void ReadBmp(const std::string& filepath, Bitmap& bmp) {
    std::fstream file;
    file.open(filepath, std::ios_base::in | std::ios_base::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }
    BMPHeader& header = bmp.GetHeader();
    DIBHeader& dib_header = bmp.GetDIBHeader();
    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    file.read(reinterpret_cast<char*>(&dib_header), sizeof(dib_header));

    TestBMPFile(bmp);
    const std::streamsize padding = dib_header.width % 4;
    bmp.Pixels().SetPixelsMatrix(dib_header.height, dib_header.width);
    for (int32_t i = dib_header.height - 1; i >= 0; --i) {
        for (int32_t j = 0; j < dib_header.width; ++j) {
            RGB pixel;
            file.read(reinterpret_cast<char*>(&pixel), sizeof(pixel));
            bmp.Pixels().SetPixel(i, j, pixel);
        }
        file.ignore(padding);
    }
    file.close();
}

void WriteBmp(const std::string& filepath, Bitmap& bmp) {
    std::ofstream file;
    file.open(filepath, std::ios_base::out | std::ios_base::binary);
    BMPHeader& header = bmp.GetHeader();
    DIBHeader& dib_header = bmp.GetDIBHeader();
    if (!file.is_open()) {
        throw std::runtime_error("file is not open");
    }

    file.write(reinterpret_cast<char*>(&header), sizeof(header));
    file.write(reinterpret_cast<char*>(&dib_header), sizeof(dib_header));

    const std::streamsize padding = dib_header.width % 4;
    for (int32_t i = dib_header.height - 1; i >= 0; --i) {
        for (int32_t j = 0; j < dib_header.width; ++j) {
            file.write(reinterpret_cast<char*>(&bmp.Pixels().GetMatrix()[i][j]),
                       sizeof(bmp.Pixels().GetMatrix()[i][j]));
        }

        char shit[padding + 1];
        file.write(reinterpret_cast<const char*>(&shit), padding);
    }
    file.close();
}
PixelMatrix& Bitmap::Pixels() {
    return bitmap;
}
BMPHeader& Bitmap::GetHeader() {
    return header;
}
DIBHeader& Bitmap::GetDIBHeader() {
    return dib_header;
}

void PixelMatrix::Resize(Bitmap& bmp, int32_t width, int32_t height) {
    const int32_t width_now = bmp.Pixels().Width();
    const int32_t height_now = bmp.Pixels().Height();
    bmp.Pixels().GetMatrix().resize(std::min(height_now, height));
    for (auto& coloumn : bmp.Pixels().GetMatrix()) {
        coloumn.resize(std::min(width_now, width));
    }
    bmp.GetDIBHeader().height = bmp.Pixels().Height();
    bmp.GetDIBHeader().width = bmp.Pixels().Width();
}
void PixelMatrix::SetPixel(int32_t x, int32_t y, RGB color) {
    bitmap[x][y] = color;
}
int32_t PixelMatrix::Width() const {
    return static_cast<int32_t>(bitmap[0].size());
}
int32_t PixelMatrix::Height() const {
    return static_cast<int32_t>(bitmap.size());
}
Vector& PixelMatrix::GetMatrix() {
    return bitmap;
}
void PixelMatrix::SetPixelsMatrix(int32_t height, int32_t width) {
    for (size_t i = 0; i < height; ++i) {
        this->GetMatrix().emplace_back(std::vector<RGB>());
        for (size_t j = 0; j < width; ++j) {
            this->GetMatrix()[i].push_back(RGB());
        }
    }
}
Vector PixelMatrix::GetNeighbours(int32_t row, int32_t column) {
    Vector ans = {{{}, {}, {}}, {{}, {}, {}}, {{}, {}, {}}};

    for (int32_t x = -1; x <= 1; ++x) {
        for (int32_t y = -1; y <= 1; ++y) {
            int32_t x_c = std::min(std::max(row + x, 0), this->Height() - 1);
            int32_t y_c = std::min(std::max(column + y, 0), this->Width() - 1);
            ans[x + 1][y + 1] = this->GetMatrix()[x_c][y_c];
        }
    }
    return ans;
}

void Run(Parser& cmd) {
    Bitmap bmp;
    ReadBmp(std::string(cmd.GetInputFile()), bmp);
    ApplyFilters(cmd.GetFilters(), bmp);
    WriteBmp(std::string(cmd.GetOutputFile()), bmp);
}
