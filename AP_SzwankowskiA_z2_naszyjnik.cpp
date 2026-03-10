#include <iostream>
#include <string>

#define MIN(a,b) ((a)<(b)?(a):(b))

inline int algoBooth(const std::string& s) {
    int n = s.length();
    
    int i = 0, j = 1; 

    while(i < n && j < n) {
        int k = 0;
        while(k < n && s[(i + k) % n] == s[(j + k) % n]) k++;

        if(k == n) break;
        
        s[(i + k) % n] > s[(j + k) % n] ? (i += k + 1, i += (i == j)) : (j += k + 1, j += (i == j));
    }

    return MIN(i, j) + 1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    while(std::cin >> N) {
        for(int i = 0; i < N; ++i) {
            std::string necklace;
            std::cin >> necklace;

            int result = algoBooth(necklace);
            std::cout << result << "\n";
        }
    }
    return 0;
}