#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CHAR_MAX 30

void newUser(); 
void login();
void createUsername(char username[CHAR_MAX]);
bool createPassword(char password[CHAR_MAX]);
void checkUsername(char username[CHAR_MAX]);
int isMatch(char password[CHAR_MAX]);
bool isStrong(char password[CHAR_MAX]);

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
    char username[CHAR_MAX];                                                    
    char password[CHAR_MAX];

    fDB = fopen("database.txt", "wb");                                          // Opens file in binary write mode because the hashes will have weird characters

    // Check if the file opened correctly
    if (fDB == NULL) {
        printf("\nError with file. \nLeaving...");
        exit(EXIT_FAILURE);
    }

    // TODO check for repeated usernames
    createUsername(username);  
    checkUsername(username);

    // FIXME the characters should be hidden as the user writes
    do {
        createPassword(password);
    } 
    while (!createPassword(password));

    printf("\nYour new username: %s", username);
    //printf("\n\nYour new password: %s\n", password);

    /*TESTING */
    FILE *f;
    f = fopen("database.txt", "w");
    fputs(username, f);
    fputs(" ", f);
    fputs(password, f);
    fputs("\n", f);

    /* END TESTING */
}

void createUsername(char username[CHAR_MAX]) {
    int len = 0;

    do {
        printf("\nPlease choose a username with 4 to 30 characters lenght:\n");     
        fgets(username, CHAR_MAX, stdin);
        username[strcspn(username, "\n")] = '\0';                   // Removes the \n from the end of string
        
        len = strlen(username);
    } while (len < 4);

}

void checkUsername(char username[CHAR_MAX]) {
    bool isUsername = false;
    int k = 0;
    do
    {
        /* If the username has more than 30 characters, only the first 30 will be stored.
        * This asks the user whether they're happy with the username
        */ 
        printf("\n%s is your username. Are you happy? \nPress Y to continue or N to choose a new username.\n", username);
        //scanf("%d", &k);
        k = getchar();
        getchar();                      // avoids the EOL 

        if (k == 78 || k == 110) {                  
            createUsername(username);
        }
        else if (k == 89 || k == 121) {             
            isUsername = true;
        } 
        else {
            continue;                    
        }

    } while (!isUsername);

}

// Returns encrypted password
bool createPassword(char password[CHAR_MAX]) {
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

    bool isSet = false;
    // Choose password and verify constraints
    do {

        printf("\nPlease choose a password with 8 to 30 characters length. \nYour password should contain upper and lower case letters, numbers and special characters.\n");
        
        //fgets(password, CHAR_MAX, stdin);
        //password[strcspn(password, "\n")] = '\0';                   // Removes the \n from the end of string
        
        gets(password);                                               // FIXME check for better options
    } while (!isStrong(password));

    if(isMatch(password) == 1) {
        printf("\nFEITO\n");
        return true;
    }
    else {
        printf("\nYour passwords don't match!\n");
        return false;
    }
}

bool isStrong(char password[CHAR_MAX]) {
    int len, i, digi = 0, up = 0, low = 0, schar = 0;

    len = strlen(password);

    for (i = 0; password[i] != NULL; i++) {
        if(password[i] >= 'A' && password[i] <= 'Z')
            up++;
        if(password[i] >= 'a' && password[i] <= 'z')
            low++;
        if(password[i] >= '0' && password[i] <= '9')
            digi++;
        if(password[i] == '@' || password[i] == '#' || password[i] == '$' || password[i] == '!')
            schar++;
    }

    if (len < 8) {
        printf("\nYour password should have at least 8 characters\n");
        return false;
    }
    else if (len > 30) {
        printf("\nYour password should have up to 30 characters\n");
        return false;
    }        
    else if (up == 0) {
        printf("\nYour password should have at least one uppercase letter\n");
        return false;
    }
    else if (low == 0) {
        printf("\nYour password should have at least one lowercase letter\n");
        return false;
    }
    else if (digi == 0) {
        printf("\nYour password should have at least one number\n");
        return false;
    }
    else if (schar == 0) {
        printf("\nYour password should have at least one special character ('@', '#', '$', '!'\n");   
        return false;
    }
    else
        return true;
}

int isMatch(char password[CHAR_MAX]) {
    char password2[CHAR_MAX];
    int ret;

    printf("\nWrite your password again for confirmation: \n");
    gets(password2);

    return(strcmp(password, password2));
}