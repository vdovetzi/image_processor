#include "parser.h"
#include <map>
#include "exceptions.h"
Parser::Parser(int argc, char** argv) {
    TestParserArguments(argc, argv);
    program_ = argv[program_name_];
    input_ = argv[input_file_name_];
    output_ = argv[output_file_name_];
    std::map<std::string_view, std::vector<std::string_view>> tmp;
    std::string_view filter;

    if (argc > 3) {
        for (int i = 3; i < argc; ++i) {
            if (*argv[i] == '-') {
                if (!tmp.empty()) {
                    filter_param_.push_back({filter, tmp.at(filter)});
                    tmp.clear();
                }
                filter = argv[i];
                tmp[filter];
            } else {
                tmp[filter].push_back(argv[i]);
            }
        }
        filter_param_.push_back({filter, tmp.at(filter)});
    }
}
std::string_view Parser::GetInputFile() const {
    return input_;
}
std::string_view Parser::GetOutputFile() const {
    return output_;
}
std::string_view Parser::GetProgramName() const {
    return program_;
}
FiltersAndParams& Parser::GetFilters() {
    return filter_param_;
}
