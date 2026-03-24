#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int pages[1005];
int parent[1005];

inline static void solve() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; ++i)
        parent[i] = 0;

    for(int i = 1; i <= n; ++i)
        scanf("%d", &pages[i]);

    vector<int> out_degree(n + 1, 0);

    for(int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        parent[b] = a;
        out_degree[a]++;
    }

    vector<int> culminating_chapters;
    for(int i = 1; i <= n; ++i) {
        if(out_degree[i] == 0) 
            culminating_chapters.push_back(i);  
    }

    int min_total_pages = 2000000000;

    for(size_t i = 0; i < culminating_chapters.size(); ++i) {
        for(size_t j = i + 1; j < culminating_chapters.size(); ++j) {
            
            int leaf1 = culminating_chapters[i];
            int leaf2 = culminating_chapters[j];
            
            vector<bool> visited(n + 1, false);
            int current_pages = 0;

            int current = leaf1;
            while(current != 0) {
                visited[current] = true;
                current_pages += pages[current];
                current = parent[current];
            }

            current = leaf2;
            while(current != 0) {
                if(!visited[current]) {
                    current_pages += pages[current];
                    visited[current] = true;
                }
                current = parent[current];
            }
            min_total_pages = min(min_total_pages, current_pages);
        }
    }
    printf("%d\n", min_total_pages);
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