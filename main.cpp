#include <iostream>
#include <cmath>
#include "KernelImageProcessing.h"
#include <filesystem>
#include <list>
#include "CSV.h"
namespace fs = std::filesystem;

std::vector<int> testTime;

int main()
{
    std::vector<std::string> images;
    std::string path = "../images/";
    std::string targetPath = "../filtered_images/";
    for (const auto & entry : fs::directory_iterator(path)){
        images.push_back(entry.path());
    }


    //images.push_back("../images/road-7504719-4500.png");
    //images.push_back("../images/road-7504719-6000.png");
    //images.push_back("../images/road-7504719_1920.png");
    //images.push_back("../images/road-7504719_1280.png");
    //images.push_back("../images/road-7504719_640.png");

    KernelImageProcessing kip;

    Matrix GaussianBlurFilter = kip.getGaussianBlurMatrix();
    Matrix BoxBlurFilter = kip.getblurKernelMatrix();
    Matrix SharpenFilter = kip.getSharpenKernelMatrix();

    std::vector<Matrix> filters {GaussianBlurFilter, BoxBlurFilter, SharpenFilter};
    const std::vector<std::string> filtersName {"GaussianBlur","BoxBlurFilter", "SharpenFilter"};


    for(int k = 0; k < 50; k++) {
        bool init = false;
        std::chrono::steady_clock::time_point begin;
        for (int i = 0; i < k; i++) {
            std::string filePath = images[i];

            cout << "Loading image..." << endl;
            Image image = kip.loadImage(filePath.c_str());

            if(init == false){
                init = true;
                begin = std::chrono::steady_clock::now();
            }




            for (int j = 0; j < 1; j++) {

                std::cout << "Convoluting with " + filtersName[j] + " kernel matrix... " << std::endl;


                Image filteredImage = kip.convolute(image, filters[j], true);


                std::cout << "Convolution completed!" << std::endl;

                //std::string targetFilePathName = targetPath + filtersName[j] + "_" + std::string(fs::path( filePath ).filename());
                //kip.saveImage(filteredImage, targetFilePathName.c_str());
                //filteredImage.clear();
                //std::cout << "Saved in " << targetFilePathName << std::endl;
            }



        }
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        int timeDifference = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        std::cout << "Elapsed Time: " << timeDifference << std::endl;

        testTime.push_back(timeDifference);
    }

    CSV v("../data.csv");
    std::cout << "test Time size: " << testTime.size() << std::endl;
    v.customWrite("Length,seq_time",testTime,testTime.size());

    return 0;
}