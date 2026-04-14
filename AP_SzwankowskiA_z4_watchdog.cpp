#include <cstdio>
#include <vector>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

using namespace std;

struct Hatch {
    int x;
    int y;
};

static inline int dist_square(int x1, int y1, int x2, int y2) { 
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2); 
}

inline static void solve() {
    int S, H;
    scanf("%d %d", &S, &H);

    vector<Hatch> hatches(H);
    for (int i = 0; i < H; ++i)
        scanf("%d %d", &hatches[i].x, &hatches[i].y);
    
    for(int x = 1; x < S; ++x) {
        for(int y = 1; y < S; ++y) { 
            bool on_hatch = false;

            for(int i = 0; i < H; ++i) {
                if(hatches[i].x == x && hatches[i].y == y) {
                    on_hatch = true;
                    break;
                }
            }

            if(on_hatch) continue;

            int max_leash = MIN(MIN(x, S - x), MIN(y, S - y));
            int max_leash_square = max_leash * max_leash;

            bool can_reach_all = true;
            for(int i = 0; i < H; ++i) {
                if (dist_square(x, y, hatches[i].x, hatches[i].y) > max_leash_square) {
                    can_reach_all = false;
                    break;
                }
            }

            if(can_reach_all) {
                printf("%d %d\n", x, y);
                return;
            }
        }
    }
    printf("impossible\n");
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