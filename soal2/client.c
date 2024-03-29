
#include <stdio.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT_J 3000
#define PORT_B 4000

int main(int argc, char const *argv[]) 
{ 
    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr;
    char buffer[64] = {0}; 
    
    char query[8];
    int valid;
    while (1){
        valid = 0;
        memset(buffer, 0, sizeof(buffer));
        printf("query : ");
        scanf("%s", query);
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
        { 
            printf("\n Socket creation error \n"); 
            return -1; 
        } 
    
        memset(&serv_addr, '0', sizeof(serv_addr)); 
    
        serv_addr.sin_family = AF_INET;
        if( (strcmp(query, "beli"))==0 ){
            serv_addr.sin_port = htons(PORT_B); 
            valid = 1;
        }
        else if( (strcmp(query, "tambah"))==0 ){
            serv_addr.sin_port = htons(PORT_J); 
            valid = 1;
        }

        if (!valid)
            continue;

        // Convert IPv4 and IPv6 addresses from text to binary form 
        if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
        { 
            printf("\nInvalid address/ Address not supported \n"); 
            return -1; 
        } 
    
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
        { 
            printf("\nConnection Failed \n"); 
            return -1; 
        } 
        send(sock , query , strlen(query) , 0 );
        valread = read( sock , buffer, sizeof(buffer)); 
        printf("%s\n",buffer ); 
        close(sock);
    }
    return 0; 
} 