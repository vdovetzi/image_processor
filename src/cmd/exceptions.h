#pragma once

#include <string>
#include <string_view>
#include <iostream>
class ApplicationExceptions : public std::exception {
public:
    const char* what() const noexcept override = 0;
};

class ParserArgumentsError : public ApplicationExceptions {
    const char* what() const noexcept override {
        return "Invalid cmd arguments. Check the number of cmd arguments: it should be at least 3 to run or 0 to read "
               "a README file";
    }
};

class FilterParametersError : public ApplicationExceptions {
    const char* what() const noexcept override {
        return "There are no such filters. Try to check the name or the number or types of parameters";
    }
};

class BMPFileError : public ApplicationExceptions {
    const char* what() const noexcept override {
        return "Invalid bmp file, try to check it for compatibility: it should be 24byte and fileFormat should be .bmp";
    }
};

class ZeroParametersError : public ApplicationExceptions {
    const char* what() const noexcept override {
        return "Rerun your program to continue";
    }
};

void TestBMPFile(auto& bmp) {
    if (bmp.GetDIBHeader().bitDepth != 24) {  // NOLINT
        throw BMPFileError();
    } else if (bmp.GetHeader().fileType != 19778) {  // NOLINT
        throw BMPFileError();
    } else if (bmp.GetDIBHeader().planes != 1) {
        throw BMPFileError();
    }
}

void TestFilterParameters(auto& params) {
    bool correct_filter_name = false;
    for (std::string_view filter_name : params.possible_filters) {
        if (params.filter_name == filter_name) {
            correct_filter_name = true;
        }
    }
    if (!correct_filter_name) {
        throw FilterParametersError();
    }
}

void TestParserArguments(auto number_of_parameters, auto arguments) {

    if (number_of_parameters == 1) {
        std::cout << "______________________README_______________________\n"
                     "It's a HSE project, Image Processor for .bmp photos.\n"
                     "You can run program by {file name} {input file} {output file} [-{filter} [param]...] ...\n"
                     "There are some filters, which you can apply by:\n"
                     "-gs: GrayScale filter\n"
                     "-crop width height: Cropping filter\n"
                     "-sharp: Sharpening filter\n"
                     "-blur sigma: GaussianBlurring filter\n"
                     "-edge threshold: EdgeDetection filter\n"
                     "-old: OldPhoto filter\n"
                     "-neg: Negative filter\n";
        throw ZeroParametersError();
    } else if (number_of_parameters < 3) {
        throw ParserArgumentsError();
    }
}