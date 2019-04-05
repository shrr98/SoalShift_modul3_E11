#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <termios.h>

using namespace std;

void* display(void*);
void* listenKeypress(void*);
void restock();
bool isRunning;
int *marketStock;

int main(){
    key_t key = ftok("food store", 65);
    int market = shmget(key, 8, 0666 | IPC_CREAT);
    marketStock = (int*) shmat(market, (void*)0, 0);
    isRunning = true;
    pthread_t tid[2];
    
    pthread_create(&tid[0], NULL, display, NULL);
    pthread_create(&tid[1], NULL, listenKeypress, NULL);

    while(isRunning);

    pthread_cancel(tid[0]);
    pthread_cancel(tid[1]);

    shmdt(marketStock);
    shmctl(market, IPC_RMID, NULL);
    return 0;
}

void* display(void* x){
    while(isRunning){
        system("clear");
        cout << "Shop" << endl <<
        "Food stock : " <<  *marketStock<< endl <<
        "Choices" << endl <<
        "1. Restock" << endl <<
        "2. Exit" << endl;
        sleep(1);
    }
}

void* listenKeypress(void* x){
    char key=0;

    static struct termios old, new1;
    int echo =0;
    while(isRunning){
        tcgetattr(0, &old); /* grab old terminal i/o settings */
        new1 = old; /* make new settings same as old settings */
        new1.c_lflag &= ~ICANON; /* disable buffered i/o */
        if (echo) {
            new1.c_lflag |= ECHO; /* set echo mode */
        } else {
            new1.c_lflag &= ~ECHO; /* set no echo mode */
        }
        tcsetattr(0, TCSANOW, &new1); /* use these new terminal i/o settings now */

        key = getchar();
        tcsetattr(0, TCSANOW, &old);

        if(key=='1'){
            restock();
        }
        else if(key=='2'){
            isRunning = false;
        }
    }
}

void restock(){
    (*marketStock)++;
}