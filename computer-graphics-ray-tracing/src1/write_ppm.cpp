#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
        const std::string & filename,
        const std::vector<unsigned char> & data,
        const int width,
        const int height,
        const int num_channels) {
    assert(
            (num_channels == 3 || num_channels == 1) &&
            ".ppm only supports RGB or grayscale images");
    // p3 is for rgb, p2 is for grey
    ////////////////////////////////////////////////////////////////////////////
    // Replace with your code here:
    std::ofstream file(filename);
    if(!file){
        return false;
    }
    if (num_channels == 1){
        file << "P2"<<std::endl;
        file << width << ' '<<height<<std::endl;
        file << 255 << std::endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j<width; j++){
                file << (int)data[i * width + j]<<" ";
            }
            file << std::endl;
        }
//        file << "P5"<<std::endl;
//        file << width << ' '<<height<<std::endl;
//        file << "255" << std::endl;
//        for (int i = 0; i < height * width; i++) {
//            file << data[i];
//        }
    }
    if (num_channels == 3) {
        file << "P3"<<std::endl;
        file << width << ' '<<height<<std::endl;
        file << 255 << std::endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j<width; j++){
                file << (int)data[i * width * 3 + j * 3]<<" "<<(int)data[i * width * 3 + j * 3 + 1]<< " "<<(int)data[i * width * 3 + j * 3 + 2]<<"  ";
            }
            file << std::endl;
        }
//        file << "P6"<<std::endl;
//        file << width << ' '<<height<<std::endl;
//        file << "255" << std::endl;
//        for (int i = 0; i < height * width * 3; i++) {
//                file << data[i];
//        }
        ////////////////////////////////////////////////////////////////////////////
    }
    return true;
}
