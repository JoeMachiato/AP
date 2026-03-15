#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>

template<size_t SIZE=10000>
int32_t GetLongestPath(const std::array<int16_t, SIZE>& path1, const std::array<int16_t, SIZE>& path2) {
  if(path1.size() == 0 && path2.size() == 0) return 0;

  int32_t totalSum{};
  int32_t path1Sum{};
  int32_t path2Sum{};
  size_t p1{};//index for path1;
  size_t p2{};//index for path2;

  while(p1<path1.size() && p2<path2.size()) {
    if(path1[p1] < path2[p2]) 
      path1Sum+=path1[p1++];
    
    else if(path1[p1] > path2[p2]) 
      path2Sum+=path2[p2++];
    
    else if(path1[p1] == path2[p2]) {
      path1Sum+=path1[p1++];
      path2Sum+=path2[p2++];
      totalSum+=std::max(path1Sum,path2Sum);
      path1Sum=0;
      path2Sum=0;
    }
  }

  while( p1<path1.size() )
    path1Sum+=path1[p1++];
  
  while( p2<path2.size() )
    path2Sum+=path2[p2++];

  totalSum+=std::max(path1Sum,path2Sum);
  path1Sum=0;
  path2Sum=0;

  return totalSum;
}

int main(int argc, char* argv[]) {
  constexpr size_t SIZE{10000};
  std::array<int16_t, SIZE> path1{};
  std::array<int16_t, SIZE> path2{};
  int16_t length{};

  while(std::cin >> length, length!=0){
    for(int16_t i{}; i<length && i<SIZE; ++i) std::cin >> path1[i];

    std::cin >> length;
    for(int16_t i{}; i<length && i<SIZE; ++i) std::cin >> path2[i];
    
    if(length >= SIZE) break;
    std::cout << GetLongestPath(path1, path2) << '\n';
  }

  return 0;
}
