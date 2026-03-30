#include <cstdio>

using namespace std;

inline static int binarySearch(int *arr, int n, int target) {
    int L = 0;
    int R = n - 1;
    int answer = n;
    
    while(L <= R) {
        int m = L + (R - L) / 2;
        if(arr[m] < target)
            L = m + 1; 
        else { 
            answer = m;
            R = m - 1;
        }
    }
    return answer;
}

inline static void solve() {
    int p;
    scanf("%d", &p);

    int tails[100000];
    int length = 0;

    for(int i = 0; i < p; ++i) {
        int value;
        scanf("%d", &value);
        
        int pos = binarySearch(tails, length, value);
        tails[pos] = value;
        
        if(pos == length) length++;
    }
    printf("%d\n", length);
}

int main() {
    int tc;
    if (scanf("%d", &tc) == 1) {
        while (tc--) 
            solve();
    }
    return 0;
}