#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CHAR_MAX 30

void newUser(); 
void login();
const char* createUsername(char username[CHAR_MAX]);
const char* createPassword(char password[CHAR_MAX]);

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

    createPassword(password);
}

// FIXME function should return void, use pointer
const char* createUsername(char username[CHAR_MAX]) {
    int len = 0;

    do {
        printf("\nPlease choose a username with 4 to 30 characters lenght. \nNew Username:");
        fgets(username, CHAR_MAX, stdin);
        username[strcspn(username, "\n")] = '\0';                   // Removes the \n from the end of string
        
        len = strlen(username);
    } while (len < 4);

    return username;
}

// Returns encrypted password
const char* createPassword(char password[CHAR_MAX]) {
    /* DO
     * Ask the user for password
     * read the password from user
     * check for special characters
     * ask for the password again
     * compare with previous password
     * while passwords are different
     * encrypt password  with sha512 + salt
     * delete plain text password from variable
     * return encrypted password
     */

    int len, i, a, digi = 0, up = 0, low = 0, schar = 0;
    bool isStrong = true;

    // Choose password and verify constraints
    do {
        printf("\nPlease choose a password with 8 to 30 characters lenght. \nYour password should contain upper and lower case letters, numbers and special characters.");
        //fgets(password, CHAR_MAX, stdin);
        //password[strcspn(password, "\n")] = '\0';                   // Removes the \n from the end of string
        gets(password);                                               // FIXME check for better options
        len = strlen(password);

        // Check password size
        if (len < 8) {
            isStrong = false;
            printf("\nYour password should have at least 8 characters");
            continue;
        }
        else if (len > 30) {
            printf("FGSDFs");
            isStrong = false;
            printf("\nYour password should have up to 30 characters");
            continue;
        }
        else {
            isStrong = true;
        }

        for (i = 0; password[i] != NULL; i++) {
            if(password[i]>='A' && password[i]<='Z')
                up++;
            if(password[i]>='a' && password[i]<='z')
                low++;
            if(password[i]>='0' && password[i]<='9')
                digi++;
            if(password[i]=='@'||password[i]=='#'||password[i]=='$')
                schar++;
        }

        if (up == 0) {
            printf("There must be at least one uppercase letter");
            isStrong = false;
        }
        if (low == 0) {
            printf("There must be at least one lowercase letter");
            isStrong = false;
        }
        if (digi == 0) {
            printf("There must be at least one number");
            isStrong = false;
        }
        if (schar == 0) {
            printf("There must be at least one special character");
            isStrong = false;
        }
    } while (!isStrong);

}