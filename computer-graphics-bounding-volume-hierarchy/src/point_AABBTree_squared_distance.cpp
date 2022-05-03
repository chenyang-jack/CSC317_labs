#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

#include <memory>
#include <vector>
#include <limits>

#include "CloudPoint.h"

#include <bits/stdc++.h>

typedef std::pair<double, std::shared_ptr<Object> > Node;

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  if(root == NULL) return false;
  
  // Initalize priority queue with assending order
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> queue;

  // Initalize the first queue val and set distance to +inf(Sincie it is not a answer-Cldpoint)
  Node closest(std::numeric_limits<double>::infinity(), root);

  // Initalize Temperary variables used in iteration
  double tempSqrd = point_box_squared_distance(query,root->box);
  std::shared_ptr<Object> tempDesc = root;
  
  queue.push(closest);

  // Dyjstra style BFS 
  while(!queue.empty()){
    Node curr = queue.top();
    queue.pop();

    // If current object is a Clould point and also legally closer that stored
    std::shared_ptr<CloudPoint> cld = std::dynamic_pointer_cast<CloudPoint>(curr.second);
    if(cld){
      // Check the real distance between point and query (not the AABB distance)
      bool inRange = cld->point_squared_distance(query,min_sqrd, max_sqrd, tempSqrd, tempDesc);
      if(inRange && tempSqrd < closest.first)
        closest = {tempSqrd, cld};
    }

    std::shared_ptr<AABBTree> aabb = std::dynamic_pointer_cast<AABBTree>(curr.second);
    if(aabb){
      // push the left and right node into queue
      if(aabb->left){
        tempSqrd = point_box_squared_distance(query, aabb->left->box);
        if(tempSqrd < closest.first)
          queue.push({tempSqrd, aabb->left});
        
      }
      if(aabb->right){
        tempSqrd = point_box_squared_distance(query, aabb->right->box);
        if(tempSqrd < closest.first)
          queue.push({tempSqrd, aabb->right});
        
      }
    }
  }

  sqrd = closest.first;
  descendant = closest.second;
  return !std::isinf(closest.first);
  ////////////////////////////////////////////////////////////////////////////
}
