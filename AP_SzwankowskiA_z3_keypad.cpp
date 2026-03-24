#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>

int keypad(char c) {
    if(c >= 'a' && c <= 'c') return 2;
    if(c >= 'd' && c <= 'f') return 3;
    if(c >= 'g' && c <= 'i') return 4;
    if(c >= 'j' && c <= 'l') return 5;
    if(c >= 'm' && c <= 'o') return 6;
    if(c >= 'p' && c <= 's') return 7;
    if(c >= 't' && c <= 'v') return 8;
    if(c >= 'w' && c <= 'z') return 9;

    return 0;
}

int main() {
    int tc, N, Q;
    if (scanf("%d", &tc) == 1) {
        while (tc--) {
            scanf("%d %d", &N, &Q);
            
            std::unordered_map<std::string, int> freq;
            char buffer[11];

            for(int i = 0; i < N; ++i) {
                scanf("%s", buffer);
                std::string num_str = "";

                for(int j = 0; buffer[j] != 0; ++j)
                    num_str += (char)(keypad(buffer[j]) + '0');
                freq[num_str]++;
            }
            for(int i = 0; i < Q; ++i) {
                scanf("%s", buffer);
                std::string q_str(buffer);

                std::unordered_map<std::string, int>::iterator iterate = freq.find(q_str);
                if(iterate != freq.end()) printf("%d\n", iterate->second);
                else printf("0\n");

            }
        }
    }
    return 0;
}