//
// Created by tshech on 8/10/2020.
//

#include <seahorn/seahorn.h>
#include "app_domain.h"
#include "set.h"

#define SET_SIZE 2

extern int nd();


int main() {
    int v1 = nd();
    int index = nd();
    assume (index >= 0 && index < SET_SIZE);

    struct Set *s = set_create();
    set_insert(s, v1);

    bool b = set_has(s, v1);
    if (v1 == set_get_element(s, index)) sassert(b);

    int v2 = nd();
    set_insert(s, v2);

    index = nd();
    assume (index >= 0 && index < SET_SIZE);
    b = set_has(s, v2);
    if (v2 == set_get_element(s, index)) sassert(b);

//    b = set_has(s, v1) && set_has(s, v2);
//    if (v1 == s->ghost_v && v2 == s->ghost_v) sassert(b);
//
//    int v3 = v2 + v1;
//    b = set_has(s, v3);
//    //if (v3 == s->ghost_v) sassert(b);

return 0;
}