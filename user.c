//
// Created by tshech on 8/10/2020.
//

#include "user.h"

#define BUFFER_SIZE 16
#define MIN_LENGTH 8

extern char *str_nd();
extern int nd();
extern unsigned int uint_nd();

void str_copy(char* dest, char* src, int size){
    int offset = 0;
    //below we can even take array_size to be sizeof(char) * BUFFER_SIZE and it will be safe,
    // but since I have already calculated the real size and it's more precise than BUFFER_SIZE, i will take that
    unsigned int array_size = sizeof(char) * size; //actually, equals to size, but just because sizeof(char) equals to 1
    for (int l = 0; l < size; l++) {
        offset = sizeof(char) * l;
        sassert (offset < array_size);
        sassert (offset >= 0);
        dest[l] = src[l];
    }
}

void credential_check_and_store(char* credential, char* credential_dst) {
    assume(credential > 0);

    int size = 0;
    //calculate real size of the credential
    for (; size < BUFFER_SIZE && credential[size] != '\0'; size++);
    credential_dst = (char *) safe_malloc(BUFFER_SIZE);

    str_copy(credential_dst, credential, size);

    credential_dst[size] = '\0';

    //random pick of a character in the bounds of the buffer
    //verifies that str_cpy worked as expected
    unsigned int i = uint_nd();
    assume(i < size);
    sassert(credential[i] == credential_dst[i]);
}

//struct user_t definition
struct user_t{
    char *m_User_name;
    char *m_Password;
    int m_UserId;
};

Suser create_user(char* user_name, char* password, struct Set* all_users_id){
    Suser user = (Suser)safe_malloc(sizeof(struct user_t));
    credential_check_and_store(user_name, user->m_User_name);
    credential_check_and_store(password, user->m_Password);

    int key = nd();
    //each user gets a unique key
    if (is_one_of_the_ghost(all_users_id, key)){
        //if it's one of the ghosts, then it is not part of the set
        assume (!set_has(all_users_id, key));
    }
    user->m_UserId = key;
    set_insert(all_users_id, key);
    return user;
}

int get_user_key(Suser user){
    return user->m_UserId;
}

void delete_user(Suser user){
    free(user->m_User_name);
    free(user->m_Password);
    free(user);
}