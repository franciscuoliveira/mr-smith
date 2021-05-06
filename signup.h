#ifndef SIGNUP_DOT_H    /* This is an "include guard" */
#define SIGNUP_DOT_H    /* prevents the file from being included twice. */
                     /* Including a header file twice causes all kinds */
                     /* of interesting problems.*/

/**
 * This is a function declaration.
 * It tells the compiler that the function exists somewhere.
 */

#include <stdbool.h>

#define CHAR_MAX 35

void newUser(); 

void createUsername(char username[CHAR_MAX]);
bool createPassword(char password[CHAR_MAX]);
void checkUsername(char username[CHAR_MAX]);
int isMatch(char password[CHAR_MAX]);
bool isStrong(char password[CHAR_MAX]);
void encryptPassword(char password[CHAR_MAX]);
bool isUsernameAvailable(char* username);
void removeSpaces(char* s);


#endif /* SIGNUP_DOT_H */