#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <utility>
#include <vector>

using POINT_TYPE = int64_t;
constexpr POINT_TYPE INF{0x3f3f3f3f3f3f3f3f}; // 1e18 in hex is faster for memcpy

struct Point {
  POINT_TYPE x{};
  POINT_TYPE y{};

  inline bool operator==(const Point& other) const { return (x==other.x && y==other.y); }
  inline Point operator-(const Point& other) const { return {x-other.x,y-other.y};}
  static inline Point abs(const Point& other) {return {std::abs(other.x),std::abs(other.y)};}
  static inline void swap(Point& other) {std::swap(other.x,other.y);}
};

int main (int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);

  int32_t cases{};
  for(size_t index{1}; std::cin >> cases && cases != 0; ++index) {
    std::vector<Point> start(cases,{INF,INF});
    for(int32_t i{}; i < cases; ++i) { std::cin >> start[i].x >> start[i].y; }
    
    std::vector<Point> end(cases,{INF,INF});
    for(int32_t i{}; i < cases; ++i) { std::cin >> end[i].x >> end[i].y; }

    std::vector<std::vector<POINT_TYPE>> moves(cases,std::vector<POINT_TYPE>(cases,INF));

    for(int32_t i{}; i< cases; ++i) { 
      for(int32_t j{}; j < cases; ++j) {
        Point distance = Point::abs(start[i] - end[j]);
        if(distance.x < distance.y) Point::swap(distance);
        moves[i][j] = std::max((distance.x + 1) / 2,(distance.x + distance.y + 2) / 3);
        if(distance == Point{1,0}) moves[i][j] = 3;
        if(distance == Point{2,2}) moves[i][j] = 4;
        moves[i][j] += ((moves[i][j]&1) != ((distance.x+distance.y)&1)); // (+= 1) or (+= 0)
      }
    }

    int64_t masksCount{1 << cases}; // 2^cases possible states
    std::vector<POINT_TYPE> cost(masksCount, INF);
    cost[0] = 0;
    
    for(int64_t mask{}; mask < masksCount; ++mask) {
      if(cost[mask] >= INF) continue;
      
      int32_t count{}; // count bits == 1 inside mask
      for(int32_t i{}; i<cases; ++i)
        count += (mask >> i)&1;
      if(count == cases) continue;

      for(int32_t knight{}; knight < cases; ++knight) {
        if(mask & (1 << knight)) continue;
        int64_t nextMask{mask | (1 << knight)};
        cost[nextMask] = std::min(cost[nextMask], cost[mask] + moves[knight][count]);
      }
    }

    std::cout << index << ". " << cost[(1 << cases)-1] << '\n';
  }
  return 0;
}
