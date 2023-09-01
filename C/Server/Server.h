#ifndef SERVER_H
#define SERVER_H
int read_until_end_line(char* buff, char* res,int max_len);
void get_sub_string(int pos, int len, char string[], char* substring);
void func(int connfd, char* dirCol, char* dirHis, char* dir_logs);
void server_loop(int sockfd, char* dirCol, char* dirHis, char* dir_logs);
unsigned char** crateArray(int height, int width) ;

unsigned char* convertToSingleArray(unsigned char** arrayOfPointers, size_t numRows, size_t numCols) ;

void getImage();


// Función para realizar la ecualización de histograma
void equalizeHistogram(int histogram[], int width, int height) ;

int hist_equa(char* read_from_path, char* input_filename, char* write_to_path) ;
#endif