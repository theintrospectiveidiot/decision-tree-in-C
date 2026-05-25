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

    thing *all_thing;
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

int main() {
    
}
