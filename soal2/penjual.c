#include <unistd.h> 
#include <stdio.h> 
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <pthread.h>

#define PORT 3000

int shmid;


void* printStock(void* x){
    int* shared_mem;
    while(1){
        shared_mem = (int*) shmat(shmid,(void*)0,0);
        if(shared_mem!=NULL){
            printf("Stok : %d\n", *shared_mem);
        }
        shmdt(shared_mem);
        sleep(5);
    }

    return NULL;
}


int jual(char *buffer){
    if( (strcmp(buffer, "tambah"))==0 ){
        int *shared_mem = (int*) shmat(shmid,(void*)0,0); 

        // change stok
        if(shared_mem != NULL){
            *shared_mem = (*shared_mem) +1;
            shmdt(shared_mem); 
            return 1;
        }
        else printf("shared memory gagal");
    }
    return 0;
}

void* server(void* x){
    int server_fd, client, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[8] = {0}; 
    char *respon[] = {"transaksi gagal", "transaksi berhasil"}; 

     // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    while(1){
        if (listen(server_fd, 1) < 0) 
        { 
            perror("listen"); 
            exit(EXIT_FAILURE); 
        } 
        if ((client = accept(server_fd, (struct sockaddr *)&address,  
                        (socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
            exit(EXIT_FAILURE); 
        } 
        valread = read( client , buffer, 8);
        int sukses = jual(buffer);
        send(client , respon[sukses] , strlen(respon[sukses]) , 0 ); 
        printf("%s\n", buffer);
        printf("%s\n", respon[sukses]); 
    }
    return NULL;
}


int main(int argc, char const *argv[]) 
{ 
    pthread_t tid[2];

    key_t key = ftok("stok",65); 

    // shmget returns an identifier in shmid 
    shmid = shmget(key,1024,0666|IPC_CREAT); 
   

    //pthread_create(&tid[1], NULL, printStock, NULL);
    pthread_create(&tid[0], NULL, &server, NULL);
    pthread_create(&tid[1], NULL, printStock, NULL);
    
    pthread_join(tid[0], NULL);
} 