#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CHAR_MAX 30

void newUser(); 
void login();
const char* createUsername(char username[30]);

int main() {

    int opt = 0;

    printf("Welcome! \nChoose an option from the menu bellow:\n");
    printf("1 - Login\n");
    
    printf("2 - Create new user\n");
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

/*
 * Creates new user
 * Stores password in data base
 * Returns to main menu
*/

void newUser() {
    
    FILE *fDB;
    char username[CHAR_MAX];                                                    // FIXME pass by reference
    char password[CHAR_MAX];
    bool isUsername = false;
    int k = 0;

    fDB = fopen("database.txt", "wb");                                          // Opens file in binary write mode because the hashes will have weird characters

    // Check if the file opened correctly
    if (fDB == NULL) {
        printf("\nError with file. \nLeaving...");
        exit(EXIT_FAILURE);
    }

    // TODO check for repeated usernames
    createUsername(username);

    /* If the username has more than 30 characters, only the first 30 will be stored.
     * This asks the user whether they're happy with the username
     */ 
    do
    {
        printf("%s is your username. \nAre you happy? \nPress 1 to continue or 0 to choose a new username.", username);
        scanf("%d", &k);
        getchar();

        if (k == 0) {
            createUsername(username);
        }
        else if (k == 1) {
            isUsername = true;
        }         

    } while (!isUsername);
}

// FIXME function should return void, use pointer
const char* createUsername(char username[30]) {
    int len = 0;

    do {
        printf("\nPlease choose a username with 4 to 30 characters lenght. \nNew Username:");
        fgets(username, CHAR_MAX, stdin);
        username[strcspn(username, "\n")] = '\0';                   // Removes the \n from the end of string
        
        len = strlen(username);
    } while (len < 4);

    return username;
}