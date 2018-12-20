#include <stdio.h>
#include <stdlib.h>

int ** isBeated;
int *x, *y;
int n = 0, k = 0, l = 0;
FILE * fin;
FILE * fout;
int isSolution = 0;

void findAll(int t, int in, int jn){
    int i, j, p;
    if(t == k + l){
        isSolution = 1;
        for(i = 0; i < k + l; i++) {
            fprintf(fout, "(%d, %d) ", x[i], y[i]);
        }
        fprintf(fout, "\n");
        return;
    }
    for(i = in + 1; i < n; i++){
        for(j = 0; j < n; j++){
            if(isBeated[i][j] == 0){
                x[t] = i;
                y[t] = j;
                int jh = 0;
                int ** isBeatedCpy = (int **)malloc(sizeof(int *) * n);
                for(jh = 0; jh < n; jh++){
                    isBeatedCpy[jh] = (int *)malloc(n * sizeof(int));
                    int jl = 0;
                    for(jl = 0; jl < n; jl++){
                        isBeatedCpy[jh][jl] = isBeated[jh][jl];
                    }
                }
                for(p = 0; p < n; p++){
                    isBeated[x[t]][p] = 1;
                    isBeated[p][y[t]] = 1;
                }
                findAll(t + 1, i, j);
                for(jh = 0; jh < n; jh++){
                    int jl = 0;
                    for(jl = 0; jl < n; jl++){
                        isBeated[jh][jl] = isBeatedCpy[jh][jl];
                    }
                }
                for(jh = 0; jh < n; jh++){
                    free(isBeatedCpy[jh]);
                }
                free(isBeatedCpy);
            }
        }
    }
}

int main() {
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    int i = 0;
    fscanf(fin, "%d %d %d", &n, &l, &k);
    x = (int *)malloc(l * sizeof(int));
    y = (int *)malloc(l * sizeof(int));
    isBeated = (int **)malloc(sizeof(int *) * n);
    for(i = 0; i < n; i++){
        isBeated[i] = (int *)malloc(n * sizeof(int));
        int j = 0;
        for(j = 0; j < n; j++){
            isBeated[i][j] = 0;
        }
    }
    for(i = 0; i < k; i++){
        fscanf(fin, "%d %d", &x[i], &y[i]);
        int j = 0;
        for(j = 0; j < n; j++){
            isBeated[x[i]][j] = 1;
            isBeated[j][y[i]] = 1;
        }
    }
    findAll(k, -1, 0);
    if(isSolution == 0){
        fprintf(fout, "no solutions");
    }
    return 0;
}