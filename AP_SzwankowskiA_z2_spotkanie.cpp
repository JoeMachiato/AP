#include <cstdio>
#include <vector>

using namespace std;

#define MATRIX_SIZE 26
#define MIN(a, b) ((a) < (b) ? (a) : (b))

const int INF = 1000000000;

int matrixStudents[MATRIX_SIZE][MATRIX_SIZE];
int matrixTeacher[MATRIX_SIZE][MATRIX_SIZE];

void resetMatrices() {
    for(int i = 0; i < MATRIX_SIZE; ++i) {
        for(int j = 0; j < MATRIX_SIZE; ++j) {
            if (i == j) {
                matrixStudents[i][j] = 0;
                matrixTeacher[i][j] = 0;
            } else {
                matrixStudents[i][j] = INF;
                matrixTeacher[i][j] = INF;
            }
        }
    }
}

void Floyd_Warshall(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for(int k = 0; k < MATRIX_SIZE; ++k) {
        for(int i = 0; i < MATRIX_SIZE; ++i) {
            for(int j = 0; j < MATRIX_SIZE; ++j) {
                if(matrix[i][k] < INF && matrix[k][j] < INF) {
                    if(matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                        matrix[i][j] = matrix[i][k] + matrix[k][j]; 
                    }
                }
            }
        }
    }
}

int main() {
    int N;
    
    while (scanf("%d", &N) == 1 && N != 0) {
        resetMatrices();

        for(int i = 0; i < N; ++i) {
            char age, direction, u_char, v_char;
            int cost;
            
            scanf(" %c %c %c %c %d", &age, &direction, &u_char, &v_char, &cost);
            
            int u = u_char - 'A';
            int v = v_char - 'A';

            if (age == 'M') {
                matrixStudents[u][v] = MIN(matrixStudents[u][v], cost);
                if (direction == 'D') {
                    matrixStudents[v][u] = MIN(matrixStudents[v][u], cost);
                }
            } else if (age == 'D') {
                matrixTeacher[u][v] = MIN(matrixTeacher[u][v], cost);
                if (direction == 'D') {
                    matrixTeacher[v][u] = MIN(matrixTeacher[v][u], cost);
                }
            }
        }
        
        Floyd_Warshall(matrixStudents);
        Floyd_Warshall(matrixTeacher);
        
        char startStudent, startTeacher;
        scanf(" %c %c", &startStudent, &startTeacher);
        
        int s_student = startStudent - 'A';
        int s_teacher = startTeacher - 'A';

        int min_cost = INF;
        vector<char> best_places;

        for(int X = 0; X < MATRIX_SIZE; ++X) {
            if(matrixStudents[s_student][X] < INF && matrixTeacher[s_teacher][X] < INF) {
                int cost = matrixStudents[s_student][X] + matrixTeacher[s_teacher][X];
                
                if (cost < min_cost) {
                    min_cost = cost;
                    best_places.clear();
                    best_places.push_back(X + 'A');
                } else if (cost == min_cost) {
                    best_places.push_back(X + 'A');
                }
            }
        }
        
        if (min_cost == INF) {
            printf("Do spotkania nie dojdzie\n");
        } else {
            printf("%d", min_cost);
            for (char place : best_places) {
                printf(" %c", place);
            }
            printf("\n");
        }
    }

    return 0;
}