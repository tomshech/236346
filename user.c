//
// Created by tshech on 8/10/2020.
//

#include "user.h"

#define BUFFER_SIZE 8
#define MIN_LENGTH 4
#define N 2

extern char *str_nd();
extern int nd();
extern unsigned int uint_nd();

void *xmalloc(size_t sz) {
    void *p;
    p = malloc(sz);
    assume((p) > 0);
    return p;
}

void str_copy(char* dest, char* src, int size){
    for (int l = 0; l < size; l++) {
        dest[l] = src[l];
    }
}

void credential_check_and_store(char* credential, char* credential_dst) {
    assume(credential > 0);

    int size = 0;
    for (; size < BUFFER_SIZE && credential[size] != '\0'; size++);
    credential_dst = (char *) xmalloc(BUFFER_SIZE);

    str_copy(credential_dst, credential, size);

    credential_dst[size] = '\0';
    unsigned int i = uint_nd();
    assume(i < size);
    sassert(credential[i] == credential_dst[i]);
}

struct user_t{
    char *m_User_name;
    char *m_Password;
    int m_UserId;
    //to be defined
    struct Set* m_Friends_id_list;
    //to be defined
    //messagesList m_ListofMessages
};

int create_user(char* user_name, char* password, struct Set* all_users_id){
    Suser user = (Suser)xmalloc(sizeof(struct user_t));
    credential_check_and_store(user_name, user->m_User_name);

    user->m_Friends_id_list = set_create();

    int key = nd();
    user->m_UserId = key;
    set_insert(all_users_id, key);
    return key;
}