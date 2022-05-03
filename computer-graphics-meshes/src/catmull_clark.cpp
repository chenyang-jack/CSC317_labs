#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>

#include "vertex_triangle_adjacency.h"
#include <algorithm>    // std::swap

std::tuple<int, int> findCommonFace(const int& x, const int& y, const std::vector<std::vector<int>>& VF){
  int f1 = -1, f2 = -1;
  for (int i = 0; i < VF[x].size(); i++){
    for (int j = 0; j < VF[y].size(); j++){      
      if(VF[x][i] == VF[y][j]){
        if(f1 == -1) f1 = VF[x][i];
        else f2 = VF[x][i];
      }
    }
  }
  return std::tie(f1, f2);
}


void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  if(num_iters <= 0) return;

  // vertex as Index determines multiple faces connected to this vertex
  std::vector<std::vector<int>> VerticesFaceList(V.rows());
  // Initalize Vertices Face list
  vertex_triangle_adjacency(F,V.rows(),VerticesFaceList);


  // Generated Face midpoint
  std::vector<Eigen::RowVector3d> newFaceList;
  // Initalize Face point
  for (int f = 0; f < F.rows(); f++){
    newFaceList.push_back( (V.row(F(f,0)) + V.row(F(f,1)) + V.row(F(f,2)) + V.row(F(f,3)))/4 ); 
  }
  
  // list of edgeMidpoints combinly used with edgeList
  std::vector<Eigen::RowVector3d> origEdgeList;
  // generated new edgeMidpoints
  std::vector<Eigen::RowVector3d> newEdgeList;
  
  // vertices x vertices determine the edge point index connected
  std::vector<std::vector<int>> edgeVertList(V.rows());
  for(int i=0;i < V.rows();i++) edgeVertList[i].resize(V.rows());
  for (int i = 0; i < V.rows(); i++){
    for (int j = 0; j < V.rows(); j++){
      edgeVertList[i][j] = -1;
    }
  }
  // Initalize edgeList
  int counter = 0;
  for (int f = 0; f < F.rows(); f++){
    for (int idx = 0; idx < 4; idx++){
      int x = F(f, idx);
      int y = F(f, (idx+1)%4);
      
      if(x > y)std::swap(x,y);

      if(edgeVertList[x][y] == -1){
        edgeVertList[x][y] = counter;
        edgeVertList[y][x] = counter;
        origEdgeList.push_back( (V.row(x)+V.row(y))/2 );
        counter++;
      }
    }
  }
  
  newEdgeList.resize(counter);
  for (int v1 = 0; v1 < V.rows(); v1++){
    for (int v2 = 0; v2 < V.rows(); v2++){
      if(edgeVertList[v1][v2] != -1){
        int f1, f2;
        std::tie(f1,f2) = findCommonFace(v1, v2, VerticesFaceList);
        newEdgeList[edgeVertList[v1][v2]] = (V.row(v1)+V.row(v2)+newFaceList[f1]+newFaceList[f2])/4;
      }
    }
  }
  // New generated VerticesList, oriented same with V
  std::vector<Eigen::RowVector3d> newVerticesList;
  // New Vertices Points
  for (int v = 0; v < V.rows(); v++){
    int n = VerticesFaceList[v].size();

    Eigen::RowVector3d sumFace;
    Eigen::MatrixXd sumF(n, 3);
    for(int i=0; i < n; i++){
      sumF.row(i) = newFaceList[VerticesFaceList[v][i]];
    }sumFace = Eigen::RowVector3d( sumF.colwise().sum() ) / n;

    Eigen::RowVector3d sumEdge;
    Eigen::MatrixXd sumE(n, 3);
    for(int i = 0, count = 0; i < V.rows(), count < n; i++){
      if(edgeVertList[v][i] != -1){
        sumE.row(count) = origEdgeList[edgeVertList[v][i]];
        count++;
      }
    }sumEdge = Eigen::RowVector3d( sumE.colwise().sum() ) / n;

    newVerticesList.push_back( (sumFace + 2 * sumEdge + ((n-3)*V.row(v)) ) / n);
  }


  // Store all Vertices 3D position
  SV.resize(newVerticesList.size() + newEdgeList.size() + newFaceList.size(), 3);
  int count = 0;
  for (auto temp : newVerticesList){
    SV.row(count) = temp;
    count++;
  }
  for (auto temp : newEdgeList){
    SV.row(count) = temp;
    count++;
  }for (auto temp : newFaceList){
    SV.row(count) = temp;
    count++;
  }
  
  std::vector<Eigen::RowVector4i> temp;
  // Indexing
  int Eshift = newVerticesList.size();
  int FCshift = newVerticesList.size() + newEdgeList.size();

  for (int f = 0; f < F.rows(); f++){
    for (int v = 0; v < 4; v++){
      int first = F(f, v);
      
      int x = F(f, v);
      int y = F(f, (v+1)%4);
      if(x > y)std::swap(x,y);

      int second = Eshift + edgeVertList[x][y];
      int third = FCshift + f;

      x = F(f, v);
      y = F(f, (v+3)%4);
      if(x > y)std::swap(x,y);

      int forth = Eshift + edgeVertList[x][y];
      
      temp.push_back(Eigen::RowVector4i(first, second, third, forth));
    }
  }
  
  SF.resize(temp.size(), 4);
  for(int i = 0; i < temp.size(); i++){
    SF.row(i) = temp[i];
  }

  
  VerticesFaceList.clear();
  newFaceList.clear();
  origEdgeList.clear();
  newEdgeList.clear();
  edgeVertList.clear();
  temp.clear();
  catmull_clark(SV, SF, num_iters - 1, SV, SF);
  ////////////////////////////////////////////////////////////////////////////
}
