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

//gets user name, password and set of all the users
//create a new user, gives him a unique key and returns it
Suser create_user(char* user_name, char* password, struct Set* all_users_id);

//gets a user and return its unique key
void delete_user(Suser user);

//gets a user and delete it to avoid memory leaks
int get_user_key(Suser user);

#endif //INC_236346_USER_H
