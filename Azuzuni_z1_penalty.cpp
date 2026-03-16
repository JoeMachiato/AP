#include <cstdint> // int64_t
#include <iostream>

int main (int argc, char *argv[]) {
  int16_t groups{};     // G > 0
  int16_t teams{};      // Teams inside group
  int16_t advancing{};  // Advancing from each team
  int16_t directAdv{};  // Directly advancing teams

  while(std::cin >> groups >> teams >> advancing >> directAdv) {
    if(groups <= 0 || advancing <= 0 || teams < advancing || directAdv < 0) break;
    uint64_t numOfGames{static_cast<uint64_t>(groups) * teams * (teams -1) / 2};
    uint64_t finalTeams{static_cast<uint64_t>(groups) * advancing + directAdv};
    uint64_t roundedTeams{1};
    while((roundedTeams<<=1) < finalTeams);
    std::cout << "\x1b[1m" << groups << '*' << advancing << '/' << teams << '+' << directAdv << '=' 
              << numOfGames + (roundedTeams-1) << '+' << roundedTeams-finalTeams << "\x1b[0m\n";
  }
  return 0;
}
