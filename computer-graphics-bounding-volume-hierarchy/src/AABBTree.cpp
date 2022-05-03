#include "AABBTree.h"
#include "insert_box_into_box.h"

#include <iostream>
using namespace std;

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

std::vector<std::shared_ptr<Object> > cpyObjs;

void swap(int i, int j){
  std::shared_ptr<Object> temp = cpyObjs[i];
  cpyObjs[i] = cpyObjs[j];
  cpyObjs[j] = temp;
}

int partition(int left, int right, int pivotIdx, int axisIdx){
  // pivot point value, median
  double pivot = cpyObjs[pivotIdx]->box.center()(axisIdx);
  swap(pivotIdx, right);

  // init smaller value starting location
  int storeIdx = left;
  for(int i = left; i <= right; i++){
    // if value smaller swap to the store smaller location
    if(cpyObjs[i]->box.center()(axisIdx) < pivot){
      swap(storeIdx, i);
      storeIdx++;
    }
  }
  swap(storeIdx, right);
  return storeIdx;
}

// return position of split, normally half
int quickSplit(int left, int right, int k, int axisIdx){
  if(left == right) return left;

  srand (time(NULL));
  int pivotIdx = rand() % (right - left) + left;
  pivotIdx = partition(left, right, pivotIdx, axisIdx);
  
  if(k == pivotIdx) return k;
  else if (k < pivotIdx) 
    return quickSplit(left, pivotIdx-1, k, axisIdx);
  else 
    return quickSplit(pivotIdx + 1, right, k, axisIdx);
}

void splitObjbyAxis(const std::vector<std::shared_ptr<Object> > & objects, int axisIdx){
  cpyObjs.clear();
  cpyObjs = objects;

  int size = objects.size();
  int k = size/2 - size%2;  
  quickSplit(0, size-1, k, axisIdx);
}


AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for (const auto & object : objects){
      insert_box_into_box(object->box, this->box);
  }
  // Exception if statement: object# 0, 1
  if(objects.size() <= 1){throw;}
  
  else if(objects.size() >= 2){
    // Determine the Longest Axis
    double xAxis = this->box.max_corner(0) - this->box.min_corner(0);
    double yAxis = this->box.max_corner(1) - this->box.min_corner(1);
    double zAxis = this->box.max_corner(2) - this->box.min_corner(2);

    int axisIdx = -1;
    if(xAxis > yAxis && xAxis > zAxis) axisIdx = 0;
    if(yAxis > xAxis && yAxis > zAxis) axisIdx = 1;
    if(zAxis > xAxis && zAxis > yAxis) axisIdx = 2;

#pragma region QuickSplit
    // Quick split (Slow generating when Distance Detection)
    splitObjbyAxis(objects, axisIdx);
    int midPoint = (int)objects.size()/2;
    std::vector<std::shared_ptr<Object> > leftObjs(cpyObjs.begin(), cpyObjs.begin() + midPoint);
    std::vector<std::shared_ptr<Object> > rightObjs(cpyObjs.begin() + midPoint, cpyObjs.end());
#pragma endregion

#pragma region SpacialMidpoint   
    // //Obj Median Quick Sort Finished Above
    // std::vector<std::shared_ptr<Object> > leftObjs;
    // std::vector<std::shared_ptr<Object> > rightObjs;
    
    // double axisMid = this->box.center()(axisIdx);
    // for(auto ptr : objects){
    //   // insert to left else to right
    //   if(ptr->box.center()(axisIdx) < axisMid){
    //     leftObjs.push_back(ptr);
    //   }else rightObjs.push_back(ptr);
    // }

    // int mid = (int)objects.size()/2;
    // if(leftObjs.size() == objects.size()) {
    //   rightObjs.insert(rightObjs.end(), leftObjs.begin() + mid, leftObjs.end());
    //   leftObjs.erase(leftObjs.begin() + mid, leftObjs.end());
    // }
    // else if(rightObjs.size() == objects.size()){
    //   leftObjs.insert(leftObjs.end(), rightObjs.begin() + mid, rightObjs.end());
    //   rightObjs.erase(rightObjs.begin() + mid, rightObjs.end());
    // }
#pragma endregion

    if(leftObjs.size() == 1){
      this->left = leftObjs[0];
      insert_box_into_box(leftObjs[0]->box, this->left->box);
    }
    else if(leftObjs.size() > 1)
      this->left = std::make_shared<AABBTree>(leftObjs, a_depth+1);

    if(rightObjs.size() == 1){
      this->right = rightObjs[0];
      insert_box_into_box(rightObjs[0]->box, this->right->box);
    }
    else if(rightObjs.size() > 1)
      this->right = std::make_shared<AABBTree>(rightObjs, a_depth+1);
  }
  ////////////////////////////////////////////////////////////////////////////
}
