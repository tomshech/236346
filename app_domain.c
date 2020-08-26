//
// Created by tshech on 8/10/2020.
//

#include "app_domain.h"


#define SET_SIZE 2

extern int nd();
extern unsigned int uint_nd();
extern char *str_nd();

static int8_t* g_bgn;
static int8_t* g_end;
static int g_active;
extern int8_t* nd_ptr(void);

extern Suser* users_nd();

typedef struct Entry {
    int user_id;
    int rank;
    struct Entry *next;
} Entry;

typedef struct List {
    Entry *head;
} List;

Entry *mk_node (int user_id, int rank) {
    Entry* res = (Entry*) xmalloc(sizeof(struct Entry));
    res->user_id = user_id;
    res->rank = rank;
    res->next = NULL;
    return res;
}

List *mk_list() {
    List *res = (List*) xmalloc(sizeof(struct List));
    res->head = NULL;
    return res;
}

//void insert(List *lst, int user_id, int rank) {
//    Entry *en = mk_entry (user_id, rank);
//    en->next = lst->head;
//    lst->head = en;
//}
Entry* exists(List *lst, int user_id){
    for (Entry* it = lst->head; it != NULL; it = it->next){
        if (it->user_id == user_id){
            return it;
        }
    }
    return NULL;
}

Entry* ranked_user(List *lst, int giver_id, int given_id, int rank){
    Entry* user_to_add = exists(lst, given_id);
    if (!user_to_add){
        Entry *node = mk_node (given_id, 0);
        //save address
        assume (rank > 0);
        node->rank += rank;
        node->next = lst->head;
        lst->head = node;

        if (!g_active && nd()){
            g_active = !g_active;
            assume((int8_t*)node == g_bgn);
            assume(g_bgn + sizeof(struct Entry) == g_end);
        }
        else {
            assume((int8_t*)node > g_end);
        }
        return node;
    }
    else {
        return user_to_add;
    }
}

bool exists_in_set(Suser* set, Suser element){
    for (int i = 0; i < 5; ++i) {
        if (set[i] == element){
            return true;
        }
    }
    return false;
}

extern List* get_users_from_DB();



int main() {
    int remembered_key;
    bool is_remember = false;
    struct Set* all_users_id = set_create();

    //verify an element is really inserted into the set of users
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

    //verify that sorting the set is working
    struct Set* posts = set_create();
    for (int i = 0; i < SET_SIZE; ++i) {
        int key = nd();
        int comments = nd();
        assume(comments >= 0);
        create_post(key, comments, posts);
    }
    int best_post_key = get_best_post(posts);
    int nd_key = nd();
    if (is_one_of_the_ghost(posts, nd_key) && set_has(posts, nd_key) && best_post_key != -1){
        sassert(best_post_key >= nd_key);
    }

    //verify that delete from the set is working
    if (is_remember){
        set_delete(all_users_id, remembered_key);
        sassert(!(set_has(all_users_id, remembered_key)));
    }

    //verify that
    List* ranked_users;
    Entry *it;
    g_active = 0;
    int user1_key = nd();
    int user2_key = nd();
    assume (user1_key != user2_key && set_has(all_users_id, user1_key) && set_has(all_users_id, user2_key));
    Entry* user1 = ranked_user(ranked_users, user1_key, user2_key, 5);

    for (it = ranked_users->head; it != NULL; it = it->next){
        if (g_active){
            sassert((int8_t*)it == g_bgn);
        }
    }

//    Suser* users = users_nd();
//    Suser* best_users = xmalloc(5* sizeof(Suser));
//    int k = 0;
//    for (int j = 0; j < 5; ++j) {
//        assume(users[j] != NULL);
//        //if(nd()){
//            best_users[k++] = users[j];
//        //}
//    }
//    int l = nd();
//    assume (l >= 0 && l < k);
//    sassert(best_users[l] == users[l]);
//    //sassert(exists_in_set(users, best_users[l]));


return 0;
}
