#include "monster.h"

Monster::Monster(string nama){
        this->name = nama;
        hygiene_stat=100;
        hunger_stat=200;
        health_stat=300;
        bath_isNotReady = 0;
        status = 0;
        isLiving = true;
}

Monster::~Monster(){
    // join all threads disik
    for(int i=0; i<5; i++){
        pthread_join(tid[i], NULL);
    }
}

void Monster::play(){
    pthread_create(&tid[0], NULL, &Monster::display, this);
    pthread_create(&tid[1], NULL, &Monster::regenerasi, this);
    pthread_create(&tid[2], NULL, &Monster::bathCoolDown, this);
    pthread_create(&tid[3], NULL, &Monster::kelaparan, this);
    pthread_create(&tid[4], NULL, &Monster::hygieneDecrease, this);
}

void* Monster::display(void *x){
    Monster* m = (Monster*) x;
    while(m->isLiving){
        switch(m->status){
            case STANDBY_STAT:
                m->standby();
                break;
            case BATTLE_STAT:
                m->battle();
                break;
            case SHOP_STAT:
                m->shop();
                break;
            default:
                break;
        }
        sleep(1);
    }
}

void* Monster::regenerasi(void* x){
    Monster* m = (Monster*) x;
    while(m->isLiving){
       if(m->getHealth()<=0){
            // mati
            m->isLiving=false;
            printf("Game Over:Lack of health\n"); 
        }
        else if(m->status==STANDBY_STAT){
            m->addHealth(5);
            sleep(10);
        }
    }
}

void* Monster::bathCoolDown(void* x){

}

void* Monster::kelaparan(void* x){
    Monster* m = (Monster*) x;
    while(m->isLiving){
       if(m->getHunger()<=0){
            // mati
            m->isLiving=false;
            printf("Game Over:Starvation\n"); 
        }
        else if(m->status!=BATTLE_STAT){
            m->addHunger(-5);
            sleep(10);
        }
    }
}

void* Monster::hygieneDecrease(void* x){
    Monster* m = (Monster*) x;
    while(m->isLiving){
       if(m->getHygiene()<=0){
            // mati
            m->isLiving=false;
            printf("Game Over:Lack of hygiene\n"); 
        }
        else if(m->status!=BATTLE_STAT){
            m->addHygiene(-10);
            sleep(30);
        }
    }
}

void Monster::standby(){  
    cout << "Standby Mode" << endl;
    cout << "Health : " << health_stat << endl;
    cout << "Hunger : " << hunger_stat << endl;
    cout << "Hygiene : " << hygiene_stat << endl;
    cout << "Food left : " << foodStock << endl;
    cout << "Bath will be ready in " << bath_isNotReady << "s" << endl;
    cout << "Choices" << endl;
    printf("1. Eat\n2. Bath\n3. Battle\n4. Shop\n5. Exit\n");
}

void Monster::battle(){

}

void Monster::shop(){

}

void Monster::addHealth(int x){
    health_stat+=x;
}

int Monster::getHealth(){
    return health_stat;
}

void Monster::addHunger(int x){
    hunger_stat+=x;
}

int Monster::getHunger(){
    return hunger_stat;
}

void Monster::addHygiene(int x){
    hygiene_stat+=x;
}

int Monster::getHygiene(){
    return hygiene_stat;
}