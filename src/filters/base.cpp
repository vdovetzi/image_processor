#include "base.h"
#include "grayscale.h"
#include "crop.h"
#include "sharpening.h"
#include "edge.h"
#include "oldphoto.h"
#include "negative.h"
#include "gaussianblur.h"
#include <map>
#include "../cmd/exceptions.h"
void ApplyFilters(std::vector<AppliedFilter>& filter_to_apply, Bitmap& bmp) {
    GrayScaleFilter gs;
    CropFilter crop;
    SharpeningFilter sharp;
    NegativeFilter neg;
    EdgeDetectionFilter edge;
    GaussianBlurFilter gaus;
    OldPhotoFilter old;
    std::map<std::string_view, BaseFilter*> filter_pointers;
    filter_pointers["-gs"] = &gs;
    filter_pointers["-crop"] = &crop;
    filter_pointers["-neg"] = &neg;
    filter_pointers["-sharp"] = &sharp;
    filter_pointers["-blur"] = &gaus;
    filter_pointers["-edge"] = &edge;
    filter_pointers["-old"] = &old;
    for (const AppliedFilter& filter : filter_to_apply) {
        TestFilterParameters(filter);
        filter_pointers[filter.filter_name]->Apply(filter.filter_params, bmp);
    }
}