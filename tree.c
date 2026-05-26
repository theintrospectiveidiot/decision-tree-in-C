#include "tree.h"

thing **give_arr(feature *feature, thing *th) {
    if(strcmp(th->name, feature->dis_thing[th->index]->name)) {
        printf("\nthe branch (%s) doesnt belong to the node [%s]\n", th->name, feature->name);
        exit(1);
    }
    int n = 0;
    thing **arr = malloc(sizeof(thing *)*(feature->how_many_each[th->index]));
    for(int i=0;i<feature->total;i++) {
        if (th->index == feature->thing[i]->index) {
            arr[n] = feature->thing[i];
            n += 1;
        }
    }
    return arr;
}

double compute_gini_thingwise(thing **data, int *label, int how_many) {
    
    double yes = 0, no = 0;
    double gini;

    for(int i=0;i<how_many;i++) {
        if (label[data[i]->position[1]]) {
            yes += 1;
            //printf("pos:%d\tit was yes\n", data[i]->position[1]);
        }
        else {
            no += 1;
            //printf("pos:%d\tit was no\n", data[i]->position[1]);
        }
    }

    gini = 1 - (yes/how_many)*(yes/how_many) - (no/how_many)*(no/how_many);

    return gini;
}

double compute_gini_overall(feature *ftr, int *label) {
    
    double gini_weighted = 0;

    for(int i=0;i<ftr->dis_total;i++) {
        thing **arr = give_arr(ftr, ftr->dis_thing[i]);
        double ind_gi = compute_gini_thingwise(arr, label, ftr->how_many_each[i]);
        gini_weighted += (((double) ftr->how_many_each[i]) / ((double) ftr->total)) * ind_gi;
        //printf("%s's ind gi is %lf\n", ftr->dis_thing[i]->name, ind_gi);
        free(arr);
    }

    return gini_weighted;
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

   thing **things = give_arr(stuff, stuff->dis_thing[1]);
   for(int i=0;i<root->feature->how_many_each[1];i++) {
       printf("\nname: %s\npos: %d\tindex: %d\n", things[i]->name, things[i]->position[1], things[i]->index);
   } 
    
   //printf("%s's gini impurity indivisually is %lf\n", stuff->dis_thing[1]->name, compute_gini_thingwise(give_arr(stuff, stuff->dis_thing[1]), label,stuff->how_many_each[1]));
    
    printf("%s's weighted mean gini impurity is %lf\n", stuff->name, compute_gini_overall(stuff, label));
}
