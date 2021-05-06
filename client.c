#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int client()
{
        int fd;
        char fileName[2000], file_buffer[2000000], c;
        struct sockaddr_in server_address;

        //socket file descriptor
        if((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
                perror("Error creating socket");
                exit(EXIT_FAILURE);
        }

        memset(&server_address, 0, sizeof(server_address));

        bzero(&server_address, sizeof(server_address));

        //server information
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(8000); //Random port number, can be changed later
        server_address.sin_addr.s_addr = INADDR_ANY;
        //server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

        printf("Enter file name: \n");
        scanf("%s", fileName);
        sendto(fd, fileName, strlen(fileName), 0, (struct sockaddr *)&server_address, sizeof(struct sockaddr));


        FILE *fp;
        fp=fopen(fileName, "r");
		
        if(fp)
        {
                printf("Reading file content...\n");
                fseek(fp,0,SEEK_END);
                size_t file_size=ftell(fp);
                fseek(fp, 0, SEEK_SET);
                if(fread(file_buffer, file_size, 1, fp) <= 0)
                {
                        printf("Unable to copy file to buffer or file is empty.\n");
                        exit(1);
                }
        }

        else
        {
                printf("Error opening file.\n");
                exit(0);
        }



        if(sendto(fd, file_buffer, strlen(file_buffer), 0, (struct sockaddr *)&server_address, sizeof(struct sockaddr))>        {
                printf("File not sent.\n");
        }

        else
        {
                printf("File sent.\n");
        }

        fclose(fp);

        return 0;
}


int main(){
client()
}