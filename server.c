#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>

int server()
{
        char fileName[100];
        char fileBuffer[2000];
        int sd, connfd, len;

        for(int i=0; i<=100;i++)
        {
                fileName[i] ='\0';
        }

        struct sockaddr_in server_address, client_address;

        sd = socket(AF_INET, SOCK_DGRAM, 0);

        if(sd == -1)
        {
                printf("Error creating server socket.\n");
                exit(0);
        }
        else
        {
                printf("Server socket created.\n");
        }

        bzero(&server_address, sizeof(server_address));

        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(8000);
		
		  memset(&(server_address.sin_zero), '\0', 8);

        if(bind(sd, (struct sockaddr *)&server_address, sizeof(server_address)) != 0)
        {
                printf("Error in binding.\n");
        }
        else
        {
                printf("Binded.\n");
        }

        len = sizeof(client_address);


        recvfrom(sd, fileName, 1024, 0, (struct sockaddr *)&client_address, &len);
        printf("File received: %s\n", fileName);

        FILE *fp;
        recvfrom(sd, fileBuffer, 1024, 0, (struct sockaddr *)&client_address, &len);

        int fsize = strlen(fileBuffer);
        fp = fopen(fileName, "w");

        if(fp)
        {
                fwrite(fileBuffer, fsize, 1, fp);
                printf("File received.\n");
        }

        else
        {
                printf("Error creating output file.\n");
        }

        memset(fileName, '\0', sizeof(fileName));
        fclose(fp);

        return 0;
		}

int main(){
server();
}