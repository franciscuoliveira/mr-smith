#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "signup.h" 

#define CHAR_MAX 30

void login();

int main() {

    int opt = 0;

    printf("Welcome! \nChoose an option from the menu bellow:\n");
    printf("1 - Sign In\n");
    printf("2 - Sign Up\n");
    printf("3 - Quit\n");

    scanf("%d", &opt);
    getchar();                                                                  // Deals with the \n stored in buffer

    switch (opt) {
        case 1:
            login();
            printf("Loggin in...\n");
            break;
        case 2:
            newUser();
            break;
        case 3:
            printf("Quiting...");
            exit(EXIT_SUCCESS);                       
            break;
    }

    return 0;
}

void login() {}


