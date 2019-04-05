#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <string>
#include <sys/shm.h>
#include <sys/ipc.h>


using namespace std;

enum {
    STANDBY_STAT,
    BATTLE_STAT,
    SHOP_STAT
};

typedef int Enemy;
typedef int* MarketStock;

class Monster {
    private:
        string name;
        int hygiene_stat,
            hunger_stat,
            health_stat,
            foodStock;
        const int damage = 20;
        int bath_isNotReady;
        Enemy enemy;
        MarketStock marketStock;
        

        pthread_t tid[6];
        
        // fungsi untuk threads
        static void* display(void*);
        static void* regenerasi(void*);
        static void* bathCoolDown(void*);
        static void* kelaparan(void*);
        static void* hygieneDecrease(void*);
        static void* listenKeypress(void*);
        

        

    public:
        Monster(string nama);
        ~Monster();
        void play();
        // fungsi display
        void standby();
        void battle();
        void shop();


        void eat();
        void bath();
        void bathCooldown();

        void attack();
        void buy();

        // setter getter
        void addHealth(int);
        int getHealth();
        void addHunger(int);
        int getHunger();
        void addHygiene(int);
        int getHygiene();

        int status;
        bool isLiving;
        bool isRunning;
        string msg;
};