#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

#define MAX_MATRIX 26

inline void solve(int A, int K, const std::vector<std::string>& cypher, const std::string& message) {
    int Matrix[MAX_MATRIX][MAX_MATRIX] = {0};
    std::vector<int> buffer(A, 0);
    
    for (int i = 0; i < K - 1; ++i) {
        const std::string& word1 = cypher[i];
        const std::string& word2 = cypher[i + 1];
        
        size_t min_len = std::min(word1.length(), word2.length());
        for (int j = 0; j < min_len; ++j) {
            if (word1[j] != word2[j]) {
                int u = word1[j] - 'a';
                int v = word2[j] - 'a';
                
                if (Matrix[u][v] == 0) {
                    Matrix[u][v] = 1;
                    buffer[v]++;
                }
                break;
            }
        }
    }

    std::queue<int> q;
    
    for (int i = 0; i < A; ++i) {
        if (buffer[i] == 0) {
            q.push(i);
        }
    }

    std::string result = "";
    bool polysemy = false;

    while (!q.empty()) {
        if (q.size() > 1) {
            polysemy = true;
        }

        int u = q.front();
        q.pop();
        result += (char)(u + 'a');

        for (int v = 0; v < A; ++v) {
            if (Matrix[u][v] == 1) {
                buffer[v]--;
                if (buffer[v] == 0) {
                    q.push(v);
                }
            }
        }
    }

    if (polysemy || result.size() != A) {
        std::cout << "Nie do odszyfrowania\n";
        return;
    }

    char decypher[26];
    for(int i = 0; i < A; ++i) {
        decypher[result[i] - 'a'] = 'a' + i;
    }
    
    std::string decrypted = "";
    for(char c : message) {
        if (c >= 'a' && c < 'a' + A) {
            decrypted += decypher[c - 'a'];
        } else {
            decrypted += c;
        }
    }
    
    std::cout << decrypted << "\n";
    
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    if (!(std::cin >> N)) return 0;

    while (N--) {
        int A, K;
        std::cin >> A >> K;

        std::vector<std::string> cypher(K);
        for (int i = 0; i < K; ++i) {
            std::cin >> cypher[i];
        }

        std::string encryptedMessage;
        std::cin >> std::ws;
        std::getline(std::cin, encryptedMessage);

        solve(A, K, cypher, encryptedMessage);
    }

    return 0;
}