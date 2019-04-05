#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h>
#include <pthread.h> 

pthread_t tid[5];

int WakeUp_Status=0;
int Spirit_Status=100;
int cAgmal=0;
int cIraj=0;
int i;
int aTidur=0;
int iBangun=0;

void* savefile(void *arg){
	pthread_t id=pthread_self();
	if(pthread_equal(id,tid[0]))
	{   
        while(1){
            while(i!=0){}
            printf("WakeUp_Status :%d\nSpirit_Status :%d\n",WakeUp_Status,Spirit_Status);
            i=3;
        }
    }
	else if(pthread_equal(id,tid[1]))
	{
        while(1){
            while(i!=1){}
            if(cAgmal!=3){
                WakeUp_Status=WakeUp_Status+15;
                printf("WakeUp_Status :%d\n",WakeUp_Status);
                if(WakeUp_Status>=100){
                    i=3;
                }
                cIraj++;
                if(cIraj==3){
                    i=2;
                    continue;
                }
            } else if(cAgmal==3){
                cAgmal=0;
                printf("Iraj Ayo Tidur disabled 10 s\n");
                iBangun=1;
                i=3;
                sleep(10);
                iBangun=0;
            }i=3;
        }
    }
    else if(pthread_equal(id,tid[2]))
    {
        while(1){
            while(i!=2){}
            if(cIraj!=3){
                Spirit_Status=Spirit_Status-20;
                printf("Spirit_Status :%d\n",Spirit_Status);
                if(Spirit_Status<=0){
                    i=3;
                }
                cAgmal++;
                if(cAgmal==3){
                    i=1;
                    continue;
                }
            } else if(cIraj==3){
                printf("Agmal Ayo Bangun disabled 10 s\n");
                cIraj=0;
                aTidur=1;
                i=3;
                sleep(10);
                aTidur=0;
            }i=3;
        }
    }	
}

int main() 
{
    i=3;
    int x;
    int counter1=0;
    int counter2=0;
	int err;
    pthread_create(&(tid[0]),NULL,&savefile,NULL);
    pthread_create(&(tid[1]),NULL,&savefile,NULL);
    pthread_create(&(tid[2]),NULL,&savefile,NULL);
    printf("1. All Status\n2. Agmal Ayo Bangun\n3. Iraj Ayo Tidur\n\nInput :");
	while(1) 
	{
        while(i!=3){}
        if(WakeUp_Status>=100){
            printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");
            break;
        }else if(Spirit_Status<=0){
            printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            break;
        }
        scanf("%d",&x);
        if(x==1){
            i=0;
        } else if(x==2 && !iBangun){
            i=1;
        } else if(x==3 && !aTidur){
            i=2;           
        }
	}
	exit(0);
	return 0;
} 

