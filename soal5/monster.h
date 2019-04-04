#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>

using namespace std;

enum {
    STANDBY_STAT,
    BATTLE_STAT,
    SHOP_STAT
};

class Monster {
    private:
        string name;
        int hygiene_stat,
            hunger_stat,
            health_stat,
            foodStock;
        const int damage = 20;
        int bath_isNotReady;
        

        pthread_t tid[5];
        
        // fungsi untuk threads
        static void* display(void*);
        static void* regenerasi(void*);
        static void* bathCoolDown(void*);
        static void* kelaparan(void*);
        static void* hygieneDecrease(void*);
        
        

    public:
        Monster(string nama);
        ~Monster();
        void play();
        // fungsi display
        void standby();
        void battle();
        void shop();

        // setter getter
        void addHealth(int);
        int getHealth();
        void addHunger(int);
        int getHunger();
        void addHygiene(int);
        int getHygiene();

        int status;
        bool isLiving;

};