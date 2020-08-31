//
// Created by tshech on 8/10/2020.
//

#ifndef INC_236346_USER_H
#define INC_236346_USER_H

#include "seahorn/seahorn.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"

typedef struct user_t *Suser;

//gets a src, dst addresses and size and copy from source to destination
// safe copy - copy only first size characters that must to be smaller than BUFFER_SIZE
void str_copy(char *dest, char *src, int size);

//gets user credential and verifies that the credential is correctly copied to the dst address
void credential_check_and_store(char *credential, char *credential_dst);

//gets user name, password and set of all the users
//create a new user, gives him a unique key and returns it
//"stores" the user in the DB
Suser create_user(char *user_name, char *password, struct Set *all_users_id);

//gets a user and return its unique key
void delete_user(Suser user);

//gets a user and delete it to avoid memory leaks
int get_user_key(Suser user);

#endif //INC_236346_USER_H
