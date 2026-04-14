#include <cstdio>
#include <vector>

#define MAX_STRENGTH 60

using namespace std;

struct Card {
    char figure;
    char suit;
    int strength;
};

int calculate_strength(char figure, char suit) {
    static int weight = 4;
    int figure_value = 0;
    int suit_value = 0;

    switch(figure) {
        case '2': figure_value = 2; break;
        case '3': figure_value = 3; break;
        case '4': figure_value = 4; break;
        case '5': figure_value = 5; break;
        case '6': figure_value = 6; break;
        case '7': figure_value = 7; break;
        case '8': figure_value = 8; break;
        case '9': figure_value = 9; break;
        case 'T': figure_value = 10; break;
        case 'J': figure_value = 11; break;
        case 'Q': figure_value = 12; break;
        case 'K': figure_value = 13; break;
        case 'A': figure_value = 14; break;
        default: break; 
    }

    switch(suit) {
        case 'C': suit_value = 0; break;
        case 'D': suit_value = 1; break;
        case 'S': suit_value = 2; break;
        case 'H': suit_value = 3; break;
        default: break;
    }

    return figure_value * weight + suit_value;
}

bool compare_cards(const Card& a, const Card& b) { return a.strength < b.strength; }

inline static void bucket_sort(vector<Card>& cards) {
    if(cards.empty()) return;
    
    int index = 0;
    vector<Card> buckets[MAX_STRENGTH];
    
    for(int i = 0; i < (int)cards.size(); ++i) buckets[cards[i].strength].push_back(cards[i]);
    
    for(int i = 0; i < MAX_STRENGTH; ++i) {
        for(int j = 0; j < (int)buckets[i].size(); ++j)
            cards[index++] = buckets[i][j];
    }
}

inline static void solve() {
    int k;
    scanf("%d", &k);
    vector<Card> adam(k);
    vector<Card> eve(k);
    char buffer[3];
    
    for(int i = 0; i < k; ++i) {
        scanf("%s", buffer);
        adam[i].figure = buffer[0];
        adam[i].suit = buffer[1];
        adam[i].strength = calculate_strength(adam[i].figure, adam[i].suit);
    }

    for(int i = 0; i < k; ++i) {
        scanf("%s", buffer);
        eve[i].figure = buffer[0];
        eve[i].suit = buffer[1];
        eve[i].strength = calculate_strength(eve[i].figure, eve[i].suit);
    }
    
    int points = 0;
    int adam_ptr = 0;
    int eve_ptr = 0;
    
    bucket_sort(adam);
    bucket_sort(eve);
    
    while (adam_ptr < k && eve_ptr < k) {
        if (eve[eve_ptr].strength > adam[adam_ptr].strength) {
            points++;
            adam_ptr++;
            eve_ptr++;
        } 
        else { eve_ptr++; }
    }
    printf("%d\n", points);
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