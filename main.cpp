#include <iostream>
#include <cmath>
#include "KernelImageProcessing.h"
#include <filesystem>
#include <list>
namespace fs = std::filesystem;

int main()
{
    std::list<std::string> images;
    std::string path = "../images/";
    std::string targetPath = "../filtered_images/";
    for (const auto & entry : fs::directory_iterator(path))
        images.push_back(entry.path());

    KernelImageProcessing kip;

    Matrix GaussianBlurFilter = kip.getGaussianBlurMatrix();
    Matrix BoxBlurFilter = kip.getblurKernelMatrix();
    Matrix SharpenFilter = kip.getSharpenKernelMatrix();

    std::vector<Matrix> filters {GaussianBlurFilter, BoxBlurFilter, SharpenFilter};
    const std::vector<std::string> filtersName {"GaussianBlur","BoxBlurFilter", "SharpenFilter"};

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for(int i = 0; i < images.size();i++){
        std::string filePath = images.front();
        images.pop_front();

        cout << "Loading image..." << endl;
        Image image = kip.loadImage(filePath.c_str());

        for(int j = 0; j < filters.size();j ++){
            std::cout << "Convoluting with "+filtersName[j]+" kernel matrix... " << std::endl;
            Image filteredImage = kip.convolute(image,filters[j],true);
            std::cout << "Convolution completed!" << std::endl;

            std::string targetFilePathName = targetPath + filtersName[j] + "_" + std::string(fs::path( filePath ).filename());
            kip.saveImage(filteredImage, targetFilePathName.c_str());
            filteredImage.clear();
            std::cout << "Saved in " << targetFilePathName << std::endl;
        }


    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    int timeDifference = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    std::cout << "Elapsed Time: " << timeDifference << std::endl;


    return 0;
}