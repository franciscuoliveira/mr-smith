#include <stdio.h>
#include <stdlib.h>
int main(){
        char a[1000];
        char b[1000];
        char c[1000];
	FILE *fptr;
        if((fptr = fopen("database.txt", "r")) == NULL){
                printf("ERROR");
                exit(1);
        }
        //reads text until " " is encountered
        fscanf(fptr, "%[^' '] %[^' '] %[^\n]",a,b,c);
        printf("%s %s",b,c);
	printf("Data from the file: \n%s",c);
        fclose(fptr);

        return 0;
}
