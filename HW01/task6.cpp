#include <cstdio>
#include <cstdlib>

int main(int argc, char *argv[]) {
    int N = std::atoi(argv[1]);

    for(int i=0; i<=N; i++){
        if (i == N){
            printf("%d\n", i);
        } else {
            printf("%d ", i);
        }
    }
    for(int i=N; i>=0; i--){
        if (i == 0){
            printf("%d\n", i);
        } else {
            printf("%d ", i);
        }
    }
    return 0;
}
