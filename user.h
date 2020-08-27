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

int create_user(char* user_name, char* password, struct Set* all_users_id);

#endif //INC_236346_USER_H
