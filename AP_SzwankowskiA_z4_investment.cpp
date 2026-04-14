#include <cstdio>
#include <vector>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

using namespace std;

struct Bond {
    int weight;
    int profit;
};

inline void solve() {
    int capital, years, available_bonds_count;

    scanf("%d %d", &capital, &years);
    scanf("%d", &available_bonds_count);

    vector<Bond> bonds(available_bonds_count);

    for(int i = 0; i < available_bonds_count; ++i) {
        int value, interest;
        scanf("%d %d", &value, &interest);
        
        bonds[i].weight = value / 1000;
        bonds[i].profit = interest;
    }

    for(int y = 0; y < years; ++y) {
        int capacity = capital / 1000;
        
        vector<int> dp(capacity + 1, 0);

        for(int i = 0; i < available_bonds_count; ++i) {
            for(int w = bonds[i].weight; w <= capacity; ++w) {
                dp[w] = MAX(dp[w], dp[w - bonds[i].weight] + bonds[i].profit);
            }
        }
        
        capital += dp[capacity];
    }

    printf("%d\n", capital);
}

int main() {
    int tc;
    if (scanf("%d", &tc) == 1) {
        while (tc--) {
            solve();
        }
    }
    return 0;
}