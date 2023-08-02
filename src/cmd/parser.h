#pragma once

#include <vector>
#include <string>

struct AppliedFilter {
    std::string_view filter_name;
    std::vector<std::string_view> filter_params;
    std::vector<std::string_view> possible_filters = {"-crop", "-gs", "-blur", "-sharp", "-edge", "-old", "-neg"};

    void Clear() {
        filter_name = "";
        filter_params.clear();
    }

    bool Emty() const {
        return (filter_name.empty() && filter_params.empty());
    }
};

using FiltersAndParams = std::vector<AppliedFilter>;

class Parser {
public:
    Parser(int argc, char **argv);

    std::string_view GetInputFile() const;

    std::string_view GetOutputFile() const;

    std::string_view GetProgramName() const;

    FiltersAndParams &GetFilters();

protected:
    // TODO: написать кучу проверок
    FiltersAndParams filter_param_;
    int program_name_ = 0;
    int input_file_name_ = 1;
    int output_file_name_ = 2;
    std::string_view input_;
    std::string_view output_;
    std::string_view program_;
};
