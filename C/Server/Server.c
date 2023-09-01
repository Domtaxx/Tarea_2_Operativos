#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include "Server.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#define MAX 4096
#define SA struct sockaddr


int read_until_end_line(char* buff, char* res, int max_len){
    int len = 0;
    memset(res, '\0', max_len);
    for(int i = 0; i<max_len; i++){
        if(buff[i] != EOF && buff[i] != '\n'){
            res[i] = buff[i];
            len++;
        }
        else{
            break;
        }
    }
    return len; 
};
// Function designed for chat between client and server.
void func(int connfd, char* dirCol, char* dirHis, char* dir_logs)
{
    char buff[MAX];
    int msg_count = 0;
    int expected_chunks = 0;
    int image_size = 0;
    char imageName[MAX];
    char buff_data[MAX];
    
    


    int select = 0;
    // infinite loop for chat
    for (;;) {
        
        bzero(buff, MAX);
        bzero(buff_data, MAX);
        // read the message from client and copy it in buffer
        ssize_t numBytesRcvd = recv(connfd, buff, MAX, 0);
        // print buffer which contains the client contents
   
        //and send that buffer to client
        //write(connfd, buff, sizeof(buff));
        if (numBytesRcvd > 0){
            printf("From client: %s\t", buff);
            // if msg contains "Exit" then server exit and chat ended.
            if (strncmp("exit", buff, 4) == 0) {
                printf("Server disconnects connection...\n");
                break;
            }
            else if (strncmp("hist", buff, 4) == 0) {
                printf("Selecting histogram\n");
                FILE *fptr;
                fptr = fopen(dir_logs, "a");   
                fwrite("\nClient has selected histogram\n",31,1,fptr);
                fclose(fptr);
                select = 1;
            }
            else if (strncmp("cols", buff, 4) == 0) {
                printf("Selecting cols\n");
                FILE *fptr;
                fptr = fopen(dir_logs, "a");
                fwrite("\nClient has selected colors\n",28,1,fptr);
                fclose(fptr);
                select = 0;
            }
            else{
                if (select == 0){
                    if(msg_count == 0){
                        msg_count++;
                        bzero(imageName, MAX);
                        read_until_end_line(buff, imageName, MAX);
                    }
                    else if(msg_count > 0){
                        msg_count++;
                        read_until_end_line(buff, buff_data, MAX);
                        image_size = atoi(buff_data);

                        char image_buff[MAX]; 
                        bzero(image_buff, MAX);
                        ssize_t FileBytesRcvd = 1;
                        
                        FILE *fptr;
                        fptr = fopen(dir_logs, "a");
                        bzero(buff, MAX);
                        strcat(buff, "Image location: ");
                        fwrite(buff,16,1,fptr);
                        fclose(fptr);
                        fptr = fopen(dir_logs, "a");
                        bzero(buff, MAX);
                        strcpy(buff, dirCol);
                        strcat(buff, imageName);
                        strcat(buff, "\n                                           ");
                        fwrite(buff,65,1,fptr);
                        fclose(fptr);
                        FILE *fp;

                        bzero(buff, MAX);
                        strcpy(buff, dirCol);
                        strcat(buff, imageName);
                        fp = fopen(buff, "w");
                        int file_count = 0;
                        while (FileBytesRcvd > 0)
                        {
                            bzero(image_buff, MAX);
                            FileBytesRcvd = recv(connfd, image_buff, MAX, 0);
                            if (strncmp("exit", image_buff, 4) == 0) {
                                printf("Client Finished with image\n");
                                break;
                            }
                            if(FileBytesRcvd > 0 ){
                                if (file_count < image_size){
                                    fwrite(image_buff,FileBytesRcvd,1,fp);
                                    file_count = file_count + FileBytesRcvd;
                                }
                            }
                        }
                        fclose(fp);
                        msg_count = 0;

                        // LOGICA DEL HISTOGRAMA
                        char output_pth[MAX];
                        bzero(output_pth, MAX);
                        strcpy(output_pth, dirCol);
                        strcat(output_pth, "/");
                        bzero(buff, MAX);
                        strcpy(buff, dirCol);
                        strcat(buff, imageName);

                        char temp[MAX];
                        get_sub_string(1,MAX-1, imageName, temp);
                        clas_color(buff,temp,output_pth);
                    }
                }
                else{
                    if(msg_count == 0){
                        msg_count++;
                        bzero(imageName, MAX);
                        read_until_end_line(buff, imageName, MAX);
                    }
                    else if(msg_count > 0){
                        msg_count++;
                        read_until_end_line(buff, buff_data, MAX);
                        image_size = atoi(buff_data);

                        char image_buff[MAX]; 
                        bzero(image_buff, MAX);
                        ssize_t FileBytesRcvd = 1;
                        
                        FILE *fptr;
                        fptr = fopen(dir_logs, "a");
                        bzero(buff, MAX);
                        strcat(buff, "Image location: ");
                        fwrite(buff,16,1,fptr);
                        fclose(fptr);
                        fptr = fopen(dir_logs, "a");
                        bzero(buff, MAX);
                        strcpy(buff, dirHis);
                        strcat(buff, imageName);
                        strcat(buff, "\n                                           ");
                        fwrite(buff,65,1,fptr);
                        fclose(fptr);

                        bzero(buff, MAX);
                        strcpy(buff, dirHis);
                        strcat(buff, imageName);
                        FILE *fp;
                        fp = fopen(buff, "w");
                        int file_count = 0;
                        while (FileBytesRcvd > 0)
                        {
                            bzero(image_buff, MAX);
                            FileBytesRcvd = recv(connfd, image_buff, MAX, 0);
                            if (strncmp("exit", image_buff, 4) == 0) {
                                printf("Client Finished with image\n");
                                break;
                            }
                            if(FileBytesRcvd > 0 ){
                                if (file_count < image_size){
                                    fwrite(image_buff,FileBytesRcvd,1,fp);
                                    file_count = file_count + FileBytesRcvd;
                                }
                            }
                        }
                        fclose(fp);
                        msg_count = 0;
                        // LOGICA DEL HISTOGRAMA
                        char output_pth[MAX];
                        bzero(output_pth, MAX);
                        strcpy(output_pth, dirHis);
                        strcat(output_pth, "/res/");

                        bzero(buff, MAX);
                        strcpy(buff, dirHis);
                        strcat(buff, imageName);

                        char temp[MAX];
                        get_sub_string(1,MAX-1, imageName, temp);

                        hist_equa(buff,temp,output_pth);
                    }
                }
            }
        }
        /*
        if (strncmp("func1", buff, 5) == 0) {
            printf("functionality 1");
            
        }*/
    }
}


// Function to get substr in C
void get_sub_string(int pos, int len, char string[], char* substring)
{
    memset(substring, '\0', len);
    strncpy(substring,string+(pos),len);
    return;
}
void server_loop(int sockfd, char* dirCol, char* dirHis, char* dir_logs){
    struct sockaddr_in cli;
    int len = sizeof(cli);
    
    // Accept the data packet from client and verification
    int connfd = accept(sockfd, (SA*)&cli, &len);
    struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&cli;
    struct in_addr ipAddr = pV4Addr->sin_addr;
    char ip_add[MAX];
    char str[INET_ADDRSTRLEN];
    bzero(str, 16);
    inet_ntop( AF_INET, &ipAddr, str, INET_ADDRSTRLEN );
    bzero(ip_add, MAX);
    strcat(ip_add,"\n***********************************\nClient IP: ");
    strcat(ip_add, str);
    strcat(ip_add," Port: ");
    bzero(str, 16);
    sprintf(str, "%d", cli.sin_port);
    strcat(ip_add, str);
    strcat(ip_add,"\n");
    FILE *fptr;
    fptr = fopen(dir_logs, "a+");
    if (fptr == NULL){
        fptr = fopen(dir_logs, "w");
    }
    fwrite(ip_add,70,1,fptr);
    fclose(fptr);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");
   
    // Function for chatting between client and server
    func(connfd, dirCol, dirHis, dir_logs);

};

// Driver function
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    int port;
    char dir_logs[MAX];
    char dir_his[MAX];
    char dir_col[MAX];

    // Read config
    FILE *fptr;
    // Open a file in read mode
    fptr = fopen("/etc/server/config.conf", "r+");
    
    if (NULL == fptr) {
        perror("file can't be opened \n");
        return -1;
    }
    char config_buff[MAX];
    char RawData[MAX];
    int new_start = 0;
    for(int i = 0; i < 4; i++){
        fgets(config_buff, MAX, fptr);
        new_start = read_until_end_line(config_buff, RawData, MAX);
        char Data[MAX];
        get_sub_string(7,MAX,RawData, Data);
        if (strncmp("Puerto", config_buff, 6) == 0) {
            printf("Puerto:%s\n", Data);
            port = atoi(Data);
        }
        else if (strncmp("DirCol", config_buff, 6) == 0) {
            printf("DirCol:%s\n", Data);
            strncpy(dir_col,Data,MAX);
        }
        else if (strncmp("DirHis", config_buff, 6) == 0) {
            printf("DirHis:%s\n", Data);
            strncpy(dir_his,Data,MAX);
        }
        else if (strncmp("DirLog", config_buff, 6) == 0) {
            printf("DirLog:%s\n", Data);
            strncpy(dir_logs,Data,MAX);
        }
    }
    fclose(fptr);

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
   
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
   
    // Now server is ready to listen and verification
    
    strcat(dir_logs, "/Activity.log");
    for(;;){
        if ((listen(sockfd, 5)) != 0) {
            printf("Listen failed...\n");
            exit(0);
        }   
        else{
            
            
            printf("Server listening..\n");
            server_loop(sockfd,dir_col,dir_his, dir_logs);
        }
    }
   
    // After chatting close the socket
    close(sockfd);
}
