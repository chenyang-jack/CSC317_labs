#include "demosaic.h"
#include <cmath>

bool pointCheck(const int& w,const int& h,const int& width,const int& height);
int avg(const std::vector<int>& color);

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  bool isGreen = true, isBlue = true;
  std::vector<int> colorAvg;
  for(int h = 0; h < height; h++){
    if(h%2 == 0){
      isGreen = true;
      isBlue = true;
    }else{
      isGreen = false;
      isBlue = false;
    }
    for(int w = 0; w < width; w++){
      int idx = h*width*3 + w*3;
      if(isGreen){
        rgb[idx+1] = bayer[h*width + w];
        
        //UpDown
        if(pointCheck(w, h-1, width, height)) 
          colorAvg.push_back(bayer[(h-1)*width + w]);
        if(pointCheck(w, h+1, width, height)) 
          colorAvg.push_back(bayer[(h+1)*width + w]);
        int color1 = avg(colorAvg);
        colorAvg.clear();
        //LeftRight
        if(pointCheck(w-1, h, width, height)) 
          colorAvg.push_back(bayer[h*width + w-1]);
        if(pointCheck(w+1, h, width, height)) 
          colorAvg.push_back(bayer[h*width + w+1]);
        int color2 = avg(colorAvg);
        colorAvg.clear();

        if(isBlue){
          rgb[idx] = color1;
          rgb[idx+2] = color2;
        }else{
          rgb[idx] = color2;
          rgb[idx+2] = color1;
        }
        isGreen = false;
        continue;
      }
      
      isGreen = true;
      //green
      if(pointCheck(w, h-1, width, height)) 
        colorAvg.push_back(bayer[(h-1)*width + w]);
      if(pointCheck(w, h+1, width, height)) 
        colorAvg.push_back(bayer[(h+1)*width + w]);
      if(pointCheck(w-1, h, width, height)) 
        colorAvg.push_back(bayer[h*width + w-1]);
      if(pointCheck(w+1, h, width, height)) 
        colorAvg.push_back(bayer[h*width + w+1]);
      rgb[idx+1] = avg(colorAvg);
      colorAvg.clear();

      //red or blue
      if(pointCheck(w-1, h-1, width, height)) 
        colorAvg.push_back(bayer[(h-1)*width + (w-1)]);
      if(pointCheck(w-1, h+1, width, height)) 
        colorAvg.push_back(bayer[(h+1)*width + (w-1)]);
      if(pointCheck(w+1, h-1, width, height)) 
        colorAvg.push_back(bayer[(h-1)*width + (w+1)]);
      if(pointCheck(w+1, h+1, width, height)) 
        colorAvg.push_back(bayer[(h+1)*width + (w+1)]);
      int colorRB = avg(colorAvg);
      colorAvg.clear();
      
      if(isBlue) {
        //red
        rgb[idx] = colorRB;
        rgb[idx+2] = bayer[h*width + w];
      }else{
        //blue
        rgb[idx+2] = colorRB;
        rgb[idx] = bayer[h*width + w];
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

bool pointCheck(const int& w,const int& h,const int& width,const int& height){
  if(w < 0 || w >= width || h < 0 || h >= height) return false;
  return true;
}

int avg(const std::vector<int>& color){
  int sum = 0;
  for(int a : color) sum+=a;
  return round((float)sum/color.size());
}