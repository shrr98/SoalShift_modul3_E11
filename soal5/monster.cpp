#include "monster.h"

Monster::Monster(string nama){
        this->name = nama;
        hygiene_stat=100;
        hunger_stat=200;
        health_stat=300;
        bath_isNotReady = 0;
        status = 0;
        isLiving = true;
        isRunning = true;
}

Monster::~Monster(){
    // join all threads disik
    for(int i=0; i<6; i++){
        pthread_cancel(tid[i]);
    }

    shmdt(marketStock);
    cout << "monster deleted" << endl;
}

void Monster::play(){
    key_t key = ftok("food store",65); 
    int market = shmget(key,8,0666|IPC_CREAT); 
    marketStock = (MarketStock) shmat(market, (void*)0, 0);

    pthread_create(&tid[0], NULL, &Monster::display, this);
    pthread_create(&tid[1], NULL, &Monster::regenerasi, this);
    pthread_create(&tid[2], NULL, &Monster::bathCoolDown, this);
    pthread_create(&tid[3], NULL, &Monster::kelaparan, this);
    pthread_create(&tid[4], NULL, &Monster::hygieneDecrease, this);
    pthread_create(&tid[5], NULL, &Monster::listenKeypress, this);

    while(isRunning);
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
    system("clear");
    cout << m->msg << "1. Exit" << endl;
}

void* Monster::regenerasi(void* x){
    Monster* m = (Monster*) x;
    while(m->isLiving){
       if(m->getHealth()<=0){
            // mati
            m->isLiving=false;
            m->msg = "Game Over:Lack of health\n"; 
        }
        else if(m->status==STANDBY_STAT){
            sleep(10);
            m->addHealth(5);
        }
    }
}

void* Monster::bathCoolDown(void* x){
    Monster* m = (Monster*) x;
    while(m->isLiving){
        m->bathCooldown();
        sleep(1);
    }
}

void Monster::bathCooldown(){
    if(bath_isNotReady==0)
        return;
    bath_isNotReady--;
}

void* Monster::kelaparan(void* x){
    Monster* m = (Monster*) x;
    while(m->isLiving){
       if(m->getHunger()<=0){
            // mati
            m->isLiving=false;
            m->msg = "Game Over:Starvation\n"; 
        }
        else if(m->status!=BATTLE_STAT){
            sleep(10);
            m->addHunger(-5);
        }
    }
}

void* Monster::hygieneDecrease(void* x){
    Monster* m = (Monster*) x;
    while(m->isLiving){
       if(m->getHygiene()<=0){
            // mati
            m->isLiving=false;
            m->msg = "Game Over:Lack of hygiene\n"; 
        }
        else if(m->status!=BATTLE_STAT){
            sleep(30);
            m->addHygiene(-10);
        }
    }
}

void* Monster::listenKeypress(void *x){
    Monster* m = (Monster*) x;
    char key=0;

    static struct termios old, new1;
    int echo =0;

    while(m->isLiving){
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

        if(!m->isLiving){
            if(key=='1'){
                m->isRunning=false;
                break;
            }
            continue;
        }

        if(m->status == STANDBY_STAT){
            switch(key){
                case '1':
                    //eat
                    m->eat();
                    break;
                case '2':
                    //bath
                    m->bath();
                    break;
                case '3':
                    //battle
                    m->enemy = 100;
                    m->battle();
                    m->status = BATTLE_STAT;
                    break;
                case '4':
                    //shop
                    m->shop();
                    m->status = SHOP_STAT;
                    break;
                case '5':
                    //exit
                    system("clear");
                    printf("exit\n");
                    m->isRunning=false;
                    break;
                default:
                    break;
            }
        }
        else if(m->status == BATTLE_STAT){
            switch(key){
                case '1':
                    m->attack();
                    break;
                case '2':
                    m->status = STANDBY_STAT;
                    break;
                default:
                    break;
            }
        }
        else if(m->status == SHOP_STAT){
            switch(key){
                case '1':
                    m->buy();
                    break;
                case '2':
                    m->status = STANDBY_STAT;
                    break;
                default:
                    break;
            }
        }
    }
}

void Monster::standby(){  
    system("clear");
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
    system("clear");
    cout << "Battle Mode" << endl <<
    "Monster’s Health : " << health_stat << endl <<
    "Enemy’s Health : " << enemy << endl;
    cout << "Choices" << endl <<
    "1. Attack" << endl <<
    "2. Run" << endl;
}

void Monster::shop(){
    system("clear");
    cout << "Shop Mode" << endl <<
        "Shop food stock : " << *marketStock << endl <<
        "Your food stock : " << foodStock << endl <<
        "Choices" << endl <<
        "1. Buy" << endl <<
        "2. Back" << endl;

}

void Monster::eat(){
    if(foodStock>0){
        foodStock--;
        hunger_stat+=15;
    }
    else {
        printf("[!] you have no food\n");
    }
}

void Monster::bath(){
    if(bath_isNotReady == 0){
        hygiene_stat+=30;
        this->bath_isNotReady=20;
        cout << bath_isNotReady<< endl;
    }
    else{
        printf("[!] the bath is not ready yet\n");
    }
}

void Monster::attack(){
    enemy-=damage;
    if(enemy<=0){
        printf("YOU WIN!!!\n");
        sleep(1);
        status = STANDBY_STAT;
        return;
    }
    sleep(1);
    health_stat-=damage;
    if(health_stat<=0){
        printf("YOU LOSE...\n");
        sleep(1);
        status = STANDBY_STAT;
        return;
    }
}

void Monster::buy(){
    if(*marketStock>0){
        (*marketStock)--;
        foodStock++;
    }
    else{
        printf("[!] No food available in the Shop\n");
    }
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