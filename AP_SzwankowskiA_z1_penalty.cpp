// ACPC10E //
#include <cstdio>

int main() {
    long long G, T, A, D;
    freopen("plik.in", "r", stdin);
    while (scanf("%lld %lld %lld %lld", &G, &T, &A, &D) == 4 && G > 0 && A > 0 && T >= A && D >= 0) {
        long long numGS = G * (T * (T - 1) / 2);
        long long koTeams = G * A + D;
        
        long long totalTeams = koTeams;
        if (totalTeams > 0) {
            totalTeams--;
            totalTeams |= totalTeams >> 1;
            totalTeams |= totalTeams >> 2;
            totalTeams |= totalTeams >> 4;
            totalTeams |= totalTeams >> 8;
            totalTeams |= totalTeams >> 16;
            totalTeams |= totalTeams >> 32;
            totalTeams++;
        } else {totalTeams = 1;}

        long long Y = totalTeams - koTeams;
        long long X = numGS + (totalTeams - 1);
        
        printf("%lld*%lld/%lld+%lld=%lld+%lld\n", G, A, T, D, X, Y);
    }
    freopen("plik.out", "w", stdout);
    return 0;
}

