#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int num;
    unsigned long long faktorial;
} Pair;

void* faktorial(void* x){
    Pair *number =  (Pair*) x;
    unsigned long long fakt=1;
    int o;
    for(o=2; o <= number->num; o++){
        fakt*=o;
    }
    number->faktorial = fakt;
}

void sort(Pair* number, int n){
    int i, o;
    for(i=0; i<n-1; i++){
        for(o=0; o<n-i-1; o++){
            if(number[o].num > number[o+1].num){
                Pair temp = number[o];
                number[o] = number[o+1];
                number[o+1] = temp;
            }
        }
    }
}

void print(Pair* number, int n){
    int i;
    for(i=0; i<n; i++){
        printf("%d! = %llu\n", number[i].num, number[i].faktorial);
    }
}

int main(int argc, char **argv){
    int n = argc - 1;
    Pair number[n];
    int i;
    pthread_t tid[n];

    for(i=0; i<n; i++){
        number[i].num = atoi(argv[i+1]);
        number[i].faktorial = 1;
        pthread_create(&tid[i], NULL, faktorial, &number[i]);
    }

    for(i=0; i<n; i++){
        pthread_join(tid[i], NULL);
    }

    sort(number, n);
    print(number, n);
    return 0;

}