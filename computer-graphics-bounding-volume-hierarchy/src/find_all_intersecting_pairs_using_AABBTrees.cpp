#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

typedef std::tuple<std::shared_ptr<Object>,std::shared_ptr<Object> > Node;

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  leaf_pairs = {};
  std::list<Node> nonOrderList;

  if(box_box_intersect(rootA->box, rootB->box))
    nonOrderList.emplace_back(rootA, rootB);


  std::shared_ptr<Object> objA, objB;
  std::shared_ptr<AABBTree> treeA, treeB;


  while(!nonOrderList.empty()){
    std::tie(objA, objB) = nonOrderList.front();
    nonOrderList.pop_front();

    treeA = std::dynamic_pointer_cast<AABBTree>(objA);
    treeB = std::dynamic_pointer_cast<AABBTree>(objB);


    if(!treeA && !treeB){
      leaf_pairs.emplace_back(objA, objB);
    }
    
    else if(!treeB){
      if(box_box_intersect(treeA->left->box, objB->box))
        nonOrderList.emplace_back(treeA->left, objB);
      if(box_box_intersect(treeA->right->box, objB->box))
        nonOrderList.emplace_back(treeA->right, objB);
    }
    
    else if(!treeA){
      if(box_box_intersect(objA->box, treeB->left->box))
        nonOrderList.emplace_back(objA, treeB->left);
      if(box_box_intersect(objA->box, treeB->right->box))
        nonOrderList.emplace_back(objA, treeB->right);
    }

    else{
      if(box_box_intersect(treeA->left->box, treeB->left->box))
        nonOrderList.emplace_back(treeA->left, treeB->left);

      if(box_box_intersect(treeA->left->box, treeB->right->box))
        nonOrderList.emplace_back(treeA->left, treeB->right);

      if(box_box_intersect(treeA->right->box, treeB->left->box))
        nonOrderList.emplace_back(treeA->right, treeB->left);

      if(box_box_intersect(treeA->right->box, treeB->right->box))
        nonOrderList.emplace_back(treeA->right, treeB->right);
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
