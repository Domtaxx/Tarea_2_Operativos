#ifndef SERVER_H
#define SERVER_H
int read_until_end_line(char* buff, char* res,int max_len);
void get_sub_string(int pos, int len, char string[], char* substring);
void func(int connfd, char* dirCol, char* dirHis, char* dir_logs);
void server_loop(int sockfd, char* dirCol, char* dirHis, char* dir_logs);
#endif