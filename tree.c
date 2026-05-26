#include "tree.h"

thing **give_arr(node *node, branch *b) {
    if(strcmp(b->thing->name, node->feature->dis_thing[b->thing->index]->name)) {
        printf("\nthe branch (%s) doesnt belong to the node [%s]\n", b->thing->name, node->feature->name);
        exit(1);
    }
    int n = 0;
    thing **arr = malloc(sizeof(thing *)*(node->feature->how_many_each[b->thing->index]));
    for(int i=0;i<node->feature->total;i++) {
        if (b->thing->index == node->feature->thing[i]->index) {
            arr[n] = node->feature->thing[i];
            n += 1;
        }
    }
    return arr;
}

int main() {
   feature *stuff = make_feature("coolness", 0, 2, 5);

   push_things(stuff, make_thing("cool",    (int[]){0, 0}, 0), 
                      make_thing("cool",    (int[]){0, 1}, 0), 
                      make_thing("uncool",  (int[]){0, 2}, 1),
                      make_thing("cool",    (int[]){0, 3}, 0),
                      make_thing("uncool",  (int[]){0, 4}, 1));
   //print_ftr(stuff);

   feature *ftr2 = make_feature("weirdness", 1, 3, 5);

   push_things(ftr2, make_thing("totally weird",    (int[]){1, 0}, 0),
                     make_thing("somewhat weird",   (int[]){1, 1}, 1),
                     make_thing("somewhat weird",   (int[]){1, 2}, 1),
                     make_thing("not weird at all", (int[]){1, 3}, 2),
                     make_thing("totally weird",    (int[]){1, 4}, 0));
   
   //print_ftr(ftr2);

   feature *ftr3 = make_feature("academics", 2, 2, 5);

   push_things(ftr3, make_thing("good",         (int[]){2, 0}, 0),
                     make_thing("not so good",  (int[]){2, 1}, 1), 
                     make_thing("good",         (int[]){2, 2}, 0),
                     make_thing("good",         (int[]){2, 3}, 0),
                     make_thing("not so good",  (int[]){2, 4}, 1));
   //print_ftr(ftr3);

   node *root = make_node(stuff);
   push_nodes(root, make_node(ftr2), make_node(ftr3));
   print_node(root);
   node *node1 = make_node(ftr2);
   print_node(node1);

   int label[5] = {1, 0, 1, 0, 1};

   thing **things = give_arr(root, root->branch[0]);
   for(int i=0;i<root->feature->how_many_each[0];i++) {
       printf("\nname: %s\npos: %d\tindex: %d\n", things[i]->name, things[i]->position[1], things[i]->index);
   } 
   
}
