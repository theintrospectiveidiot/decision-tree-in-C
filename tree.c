#include <stdio.h>

typedef struct thing {
    char *name;
    int *position;
    int index;
} thing;

typedef struct feature {
    char *name;
    int x_pos;
    
    thing *dis_thing;
    int dis_total;

    thing *thing;
    int total;
} feature;

typedef struct branch branch;
typedef struct node node;

struct node {
    feature *feature;
    struct branch **branch;
};

struct branch {
    thing *thing;
    struct node *node;
};

feature *make_feature(char *name, int x, int dis_total, int total) {
    feature *some_ftr = malloc(sizeof(feature));
    
    some_ftr->name = strdup(name);
    some_ftr->x_pos = x;
    some_ftr->dis_total = dis_total;
    some_ftr->dis_thing = malloc(sizeof(thing)*dis_total);
    some_ftr->total = total;
    some_ftr->thing = malloc(sizeof(thing)*total);

    return some_ftr;
}

int main() {
    
}
