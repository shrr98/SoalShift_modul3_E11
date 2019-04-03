#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h>
#include <pthread.h> 

pthread_t tid[3];

void* savefile(void *arg){
	pthread_t id=pthread_self();
	if(pthread_equal(id,tid[0]))
	{
		system("mkdir /home/arifdarma/Documents/FolderProses1");
		system("ps -aux | head > /home/arifdarma/Documents/FolderProses1/SimpanProses1.txt");
		system("zip -jm /home/arifdarma/Documents/FolderProses1/KompresProses1.zip /home/arifdarma/Documents/FolderProses1/SimpanProses1.txt");
		sleep(15);
		system("unzip /home/arifdarma/Documents/FolderProses1/KompresProses1.zip -d /home/arifdarma/Documents/FolderProses1/");
	}
	else if(pthread_equal(id,tid[1]))
	{
		system("mkdir /home/arifdarma/Documents/FolderProses2");
		system("ps -aux | head > /home/arifdarma/Documents/FolderProses2/SimpanProses2.txt");
		system("zip -jm /home/arifdarma/Documents/FolderProses2/KompresProses2.zip /home/arifdarma/Documents/FolderProses2/SimpanProses2.txt");
		sleep(15);
		system("unzip /home/arifdarma/Documents/FolderProses2/KompresProses2.zip -d /home/arifdarma/Documents/FolderProses2/");
	}	
}

int main() 
{
	int i=0;
	int err;
	while(i<2) 
	{
		err=pthread_create(&(tid[i]),NULL,&savefile,NULL); 
		if(err!=0) 
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
		else
		{
			printf("\n create thread success\n");
		}
		i++;
	}
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	exit(0);
	return 0;
} 

