//
// Created by tshech on 8/10/2020.
//

#include "app_domain.h"


#define SET_SIZE 2

extern int nd();
extern unsigned int uint_nd();
extern char *str_nd();

typedef struct Entry {
    void *data;
    struct Entry *next;
} Entry;

typedef struct List {
    Entry *head;
} List;

extern List* get_users_from_DB();



int main() {
    int remembered_key;
    bool is_remember = false;
    struct Set* all_users_id = set_create();

    for (int i = 0; i < SET_SIZE; ++i) {
        char* username = str_nd();
        char* password = str_nd();
        int key = create_user(username,password, all_users_id);
        if (!(is_remember) && is_one_of_the_ghost(all_users_id, key)){
            is_remember = !is_remember;
            remembered_key = key;
        }
    }
    bool b = set_has(all_users_id, remembered_key);
    if (is_remember){
        int value = set_get_element(all_users_id, remembered_key);
        if (remembered_key == value){
            sassert(b);
        }
    }

    struct Set* posts = set_create();
    for (int i = 0; i < SET_SIZE; ++i) {
        int key = nd();
        int comments = nd();
        assume(comments >= 0);
        create_post(key, comments, posts);
    }
    int best_post_key = get_best_post(posts);
    int nd_key = nd();
    if (is_one_of_the_ghost(posts, nd_key) && set_has(posts, nd_key)){
        sassert(best_post_key >= nd_key);
    }

    if (is_remember){
        set_delete(all_users_id, remembered_key);
        sassert(!(set_has(all_users_id, remembered_key)));
    }
//    b = false;
//    List *users = get_users_from_DB();
//    Entry *it;
//    struct set_element* ghosts = get_set_elements(all_users_id);
//    it = users->head;
//    assume (it != NULL);
//    for (int i=0; i < SET_SIZE;){
//        assume (it->next != NULL);
//        //assume(it->data == get_set_element(ghosts[i]));
//        if (set_has(all_users_id, get_set_element(ghosts[i]))){
//            assume(*((int*)(it->data)) == get_set_element(ghosts[i]));
//            i++;
//            if (!b)
//                b = (remembered_key == *((int*)(it->data)));
//        }
//        it = it->next;
//    }
//    sassert(b);


//    int v1 = nd();
//    int index_1 = nd();
//    assume (index_1 >= 0 && index_1 < SET_SIZE);
//
//    struct Set *s = set_create();
//    set_insert(s, v1);
//
//    bool b = set_has(s, v1);
//    if (v1 == set_get_element(s, index_1)) sassert(b);
//
//    int v2 = nd();
//    set_insert(s, v2);
//
//    int index_2 = nd();
//    assume (index_2 >= 0 && index_2 < SET_SIZE && index_1 != index_2);
//    b = set_has(s, v2);
//    if (v2 == set_get_element(s, index_2)) sassert(b);
//
//    b = set_has(s, v1) && set_has(s, v2);
//    if (v1 == set_get_element(s, index_1) && v2 == set_get_element(s, index_2)) sassert(b);
//
//    set_delete(s, v1);
//    b = set_has(s, v1);
//    if (v1 == set_get_element(s, index_1)) sassert(!b);

//    int v3 = v2 + v1;
//    b = set_has(s, v3);
//    //if (v3 == s->ghost_v) sassert(b);

return 0;
}
