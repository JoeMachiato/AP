// ACPC10G //
#include <cstdio>
#include <cmath>
#include <vector>
#define NMIN 1
#define NMAX 15
#define MIN(a, b) ((a < b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SWAP(a, b) ((a) ^= (b), (b) ^= (a), (a) ^= (b))

std::vector<int> chessboard[NMAX + 1];
int N;
int knights[NMAX + 1][2];
int coords[NMAX + 1][2];
long long dist[NMAX + 1][NMAX + 1];

inline long long minKnightMoves(long long startX, long long targetX, long long startY, long long targetY) {
    long long deltaX = std::abs(targetX - startX);
    long long deltaY = std::abs(targetY - startY);
    if (deltaX < deltaY) { SWAP(deltaX, deltaY); }

    if (deltaX == 1 && deltaY == 0) return 3;
    if (deltaX == 2 && deltaY == 2) return 4; 

    long long minMoves = MAX((deltaX + 1) / 2, (deltaX + deltaY + 2) / 3);
    if ((minMoves % 2) != (deltaX + deltaY) % 2) { minMoves++; }

    return minMoves;
}
void calculateMinDistances() {
    for(int i = NMIN; i <= N ; ++i) {
        for(int j = NMIN; j <= N; ++j) { dist[i][j] = minKnightMoves(knights[i-1][0], coords[j-1][0], knights[i-1][1], coords[j-1][1]); }
    }
}

inline long long calculate() {
    calculateMinDistances();
    int totalCombinations = 1 << N;

    std::vector<long long> dynamicProgramming(totalCombinations , 1e15);
    dynamicProgramming[0] = 0;

    for(int i = 0; i < totalCombinations; ++i) {
        if(dynamicProgramming[i] == 1e15) continue;

        int index = __builtin_popcount(i);
        if (index == N) continue;

        for(int j = 0; j < N; ++j) {
            if(!(i & (1 << j))) {
            int updatedCombinations = i | (1 << j);
            long long cost = dist[index + 1][j + 1];
        
            dynamicProgramming[updatedCombinations] = MIN( dynamicProgramming[updatedCombinations], dynamicProgramming[i] + cost);
            }
        }
    }
    return dynamicProgramming[totalCombinations - 1];
}

int main() {
    int test = 1;

    while(true) {
        if (scanf("%d", &N) != 1 || N == 0) break;
        
        for(int i = NMIN - 1; i < N; ++i) { scanf("%d %d", &knights[i][0], &knights[i][1]); }
        for(int i = NMIN - 1; i < N; ++i) { scanf("%d %d", &coords[i][0], &coords[i][1]); }

        long long result = calculate();

        printf("%d. %lld\n", test, result);

        test++;
    }

}
