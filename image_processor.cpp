#include "src/cmd/parser.h"
#include "src/bmploading/bmp.h"
#include <iostream>
#include "src/cmd/exceptions.h"

int main(int argc, char** argv) {
    try {
        Parser cmd = Parser(argc, argv);
        Run(cmd);

        return 0;
    } catch (const ApplicationExceptions& error) {
        std::cerr << error.what() << std::endl;
    } catch (...) {
        std::cerr << "Undefined error occurred while running your program.\n "
                     "Some advice: check types of parameters "
                     "while using a filter. If that's not the problem, so these is an exactly your error:\n ";
        throw;
    }
}
