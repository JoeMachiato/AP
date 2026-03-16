#include <cstdint> // int64_t
#include <limits>  // std::numeric_limits<>::max()
#include <iostream>

int main (int argc, char *argv[]) {
  //uint16_t gives us exact range from 0 to 2^16
  //this should work with C++14
  //but in case of issues compile with C++17 to prevent failbit error (compiler dependant)
  uint16_t groups{};     // G > 0
  uint16_t teams{};      // Teams inside group
  uint16_t advancing{};  // Advancing from each team
  uint16_t directAdv{};  // Directly advancing teams

  while(std::cin >> groups >> teams >> advancing >> directAdv) {
    if(  teams >= advancing 
      && groups >= std::numeric_limits<uint16_t>::max()    
      && advancing >= std::numeric_limits<uint16_t>::max() 
      && directAdv >= std::numeric_limits<uint16_t>::max()
    ) break;
    uint64_t numOfGames{static_cast<uint64_t>(groups) * teams * (teams -1) / 2};
    uint64_t finalTeams{static_cast<uint64_t>(groups) * advancing + directAdv};
    uint64_t roundedTeams{1};
    while(roundedTeams < finalTeams) roundedTeams <<= 1;
    std::cout << "\x1b[1m" << groups << '*' << advancing << '/' << teams << '+' << directAdv << '=' 
              << numOfGames + (roundedTeams-1) << '+' << roundedTeams-finalTeams << "\x1b[0m\n";
  }
  return 0;
}
