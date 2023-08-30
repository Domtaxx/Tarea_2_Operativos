#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#define MAX 4096
#define SA struct sockaddr
   
// Function designed for chat between client and server.
void func(int connfd)
{
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);
   
        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);
        bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n');
   
        // and send that buffer to client
        write(connfd, buff, sizeof(buff));
   
        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server disconnects connection...\n");
            break;
        }
        if (strncmp("func1", buff, 5) == 0) {
            printf("functionality 1");
            break;
        }
    }
}
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

// Function to get substr in C
void get_sub_string(int pos, int len, char string[], char* substring)
{
    memset(substring, '\0', len);
    strncpy(substring,string+(pos),len);
    return;
}
void server_loop(int sockfd){
    struct sockaddr_in cli;
    int len = sizeof(cli);
    // Accept the data packet from client and verification
    int connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");
   
    // Function for chatting between client and server
    func(connfd);

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
    fptr = fopen("/home/domtaxx/Documents/Git/Tarea_2_Operativos/Server/serer.conf", "r+");
    
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
            printf("Puerto%s\n", Data);
            port = atoi(Data);
        }
        else if (strncmp("DirCol", config_buff, 6) == 0) {
            printf("DirCol%s\n", Data);
            strncpy(dir_col,Data,MAX);
        }
        else if (strncmp("DirHis", config_buff, 6) == 0) {
            printf("DirHis%s\n", Data);
            strncpy(dir_his,Data,MAX);
        }
        else if (strncmp("DirLog", config_buff, 6) == 0) {
            printf("DirLog%s\n", Data);
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
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    
    for(;;){
        server_loop(sockfd);
    }
   
    // After chatting close the socket
    close(sockfd);
}

