#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>
using GRAPH = std::unordered_map<char, std::unordered_map<char, int32_t>>;

std::pair<char,char> MakeGraph(GRAPH& data, int32_t streets, std::unordered_map<char,bool>& queue) {
  std::pair<char,char> entryPoints{0,0};
  for(int32_t i{}; i<streets; ++i) {
    char access{};
    std::cin >> access;

    char direction{};
    std::cin >> direction;

    char startPoint{};
    std::cin >> startPoint;

    char endPoint{};
    std::cin >> endPoint;

    int32_t cost{};
    std::cin >> cost;

    if(access == 'M' && entryPoints.first == 0)
      entryPoints.first = startPoint;
    else if(access == 'D' && entryPoints.second == 0)
      entryPoints.second = startPoint;

    data[startPoint][endPoint] = cost;
    queue[startPoint]=false;
    if(direction == 'D') {
      data[endPoint][startPoint] = cost;
      queue[endPoint]=false;
    }
  }

  std::cin >> entryPoints.first;
  std::cin >> entryPoints.second;
  return entryPoints;
}

// returns map with costs to each node in queue, from startPoint
std::unordered_map<char, int32_t> Dijkstra(char startPoint, GRAPH& graph, std::unordered_map<char,bool>& visitedQueue) {
  std::unordered_map<char, int32_t> result{};
for (auto& neighbors : graph) {
    for (auto& node : neighbors.second) {
        if (result.find(node.first) == result.end()) {
            result[node.first] = std::numeric_limits<int32_t>::max();
        }
    }
}

  std::priority_queue<std::pair<int32_t,char>, std::vector<std::pair<int32_t, char>>, std::greater<>> pq{};
  pq.push({0,startPoint});

  result[startPoint] = 0;

  while(!pq.empty()) {
    auto top = pq.top();
    pq.pop();

    // if top's cost > result's cost skip
    if(top.first > result[top.second]) continue;

    for(auto& node : graph[top.second]) {
      if((result[top.second] + node.second) >= result[node.first]) 
        continue;
      result[node.first] = result[top.second] + node.second;
      pq.push({result[node.first],node.first});
    }
  }


  return result;
}

void CanMeet(std::unordered_map<char, int32_t> dijkstra1, std::unordered_map<char, int32_t> dijkstra2) {
  constexpr auto maxInt32 = std::numeric_limits<int32_t>::max();
  std::vector<std::pair<char, int32_t>> temp{};
  for(auto& node : dijkstra1) {
    if(node.second != maxInt32 && dijkstra2[node.first] != maxInt32) 
      if(node.second != 0 && dijkstra2[node.first] != 0)
      temp.push_back({node.first,node.second+dijkstra2[node.first]});
  }
  for(auto& value : temp) {
    std::cout << value.second << ' ' << value.first << ' ';
  }
  if(temp.empty()) std::cout << "Do spotkania nie dojdzie";
  std::cout << '\n';
}

int main (int argc, char *argv[]) {
  int32_t streets{-1};
  while(std::cin >> streets && streets != 0) {
    GRAPH graph{};
    std::unordered_map<char,bool> queue{false};
    std::pair<char, char> entries{MakeGraph(graph, streets, queue)};
    CanMeet(Dijkstra(entries.first, graph,queue), Dijkstra(entries.second, graph, queue));
  }


  return 0;
}
