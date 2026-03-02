// ANARC05B //
#include <cstdio>
#define MAX(a,b) ((a)>(b)?(a):(b))

int buffA[10001], buffB[10001];

int main() {
    int n1, n2;
    
    while (scanf("%d", &n1) == 1 && n1 != 0) {
        for (int i = 0; i < n1; i++) scanf("%d", &buffA[i]);
        scanf("%d", &n2);
        for (int i = 0; i < n2; i++) scanf("%d", &buffB[i]);
        long long sumA = 0, sumB = 0, result = 0;
        int i = 0, j = 0;
        while (i < n1 && j < n2) {
            if (buffA[i] != buffB[j]) {
                buffA[i] < buffB[j] ? sumA += buffA[i++] : sumB += buffB[j++];
            } else {
                result += MAX(sumA, sumB) + buffA[i];
                sumA = sumB = 0;
                i++; j++;
            }
        }
        while (i < n1) sumA += buffA[i++];
        while (j < n2) sumB += buffB[j++];
        result += MAX(sumA, sumB);
        
        printf("%lld\n", result);
    }
    return 0;
}



