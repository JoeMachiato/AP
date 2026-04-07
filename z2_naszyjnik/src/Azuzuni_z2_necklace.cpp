#include <algorithm>
#include <array>
#include <cstddef> // size_t
#include <cstdint> // int32_t
#include <cstring> // strlen
#include <iostream>
constexpr size_t NECKLACE_SIZE{10000};

int main (int argc, char *argv[]) {
  int32_t dataCases{};
  std::cin >> dataCases;

  for(int32_t i{}; i < dataCases; ++i) {
    std::array<char, NECKLACE_SIZE> necklace{};
    std::cin.width(NECKLACE_SIZE);
    if(!(std::cin >> necklace.begin())) break;
    
    // BOOTH algorithm
    size_t length = std::strlen(necklace.cbegin());
    size_t index1{};
    size_t index2{1};
    while(index1 < length && index2 < length) {
      size_t i{};
      while(i < length && (necklace[(index1+i)%length] == necklace[(index2+i)%length])) ++i;
      if(i == length) break;

      if(necklace[(index1+i)%length] <= necklace[(index2+i)%length]) {
        index2 += i+1; // skip worse options
        index2 += (index1==index2); // if equal, +=1 to avoid overlap
      } else {
        index1 += i+1;
        index2 += (index1==index2);
      }
    }
    std::cout << std::min(index1,index2) + 1 << '\n';
  }
  return 0;
}
