#define TOTAL 14

#include "tree.h"
#include "funcs.h"

int main() {
   //feature *stuff = make_feature("coolness", 0, 2, 5);

   /*push_things(stuff, make_thing("cool",    (int[]){0, 0}, 0), 
                      make_thing("cool",    (int[]){0, 1}, 0), 
                      make_thing("uncool",  (int[]){0, 2}, 1),
                      make_thing("cool",    (int[]){0, 3}, 0),
                      make_thing("uncool",  (int[]){0, 4}, 1));
   //print_ftr(stuff);

   feature *ftr2 = make_feature("weirdness", 1, 3, 5);

   push_things(ftr2, make_thing("totally weird",        (int[]){1, 0}, 0),
                     make_thing("not weird at all",     (int[]){1, 1}, 1),
                     make_thing("somewhat weird",       (int[]){1, 2}, 2),
                     make_thing("not weird at all",     (int[]){1, 3}, 1),
                     make_thing("totally weird",        (int[]){1, 4}, 0));
   
   //print_ftr(ftr2);

   feature *ftr3 = make_feature("academics", 2, 2, 5);

   push_things(ftr3, make_thing("good",         (int[]){2, 0}, 0),
                     make_thing("not so good",  (int[]){2, 1}, 1), 
                     make_thing("good",         (int[]){2, 2}, 0),
                     make_thing("good",         (int[]){2, 3}, 0),
                     make_thing("not so good",  (int[]){2, 4}, 1));*/
   //print_ftr(ftr3);
   int label[TOTAL] = {1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0};

   feature *income = make_feature("income", 0, 3, TOTAL);
   push_things(income,  make_thing("high",      (int[]){0,  0}, 0),
                        make_thing("high",      (int[]){0,  1}, 0),
                        make_thing("high",      (int[]){0,  2}, 0),
                        make_thing("medium",    (int[]){0,  3}, 1),
                        make_thing("medium",    (int[]){0,  4}, 1),
                        make_thing("medium",    (int[]){0,  5}, 1),
                        make_thing("low",       (int[]){0,  6}, 2),
                        make_thing("low",       (int[]){0,  7}, 2),
                        make_thing("low",       (int[]){0,  8}, 2),
                        make_thing("medium",    (int[]){0,  9}, 1),
                        make_thing("high",      (int[]){0, 10}, 0),
                        make_thing("medium",    (int[]){0, 11}, 1),
                        make_thing("low",       (int[]){0, 12}, 2),
                        make_thing("high",      (int[]){0, 13}, 0));

   feature *empl = make_feature("employment", 1, 2, TOTAL);
   push_things(empl, make_thing("stable",   (int[]){1,  0}, 0),
                     make_thing("unstable", (int[]){1,  1}, 1),
                     make_thing("stable",   (int[]){1,  2}, 0),
                     make_thing("stable",   (int[]){1,  3}, 0),
                     make_thing("unstable", (int[]){1,  4}, 1),
                     make_thing("stable",   (int[]){1,  5}, 0),
                     make_thing("stable",   (int[]){1,  6}, 0),
                     make_thing("unstable", (int[]){1,  7}, 1),
                     make_thing("stable",   (int[]){1,  8}, 0),
                     make_thing("stable",   (int[]){1,  9}, 0),
                     make_thing("stable",   (int[]){1, 10}, 0),
                     make_thing("unstable", (int[]){1, 11}, 1),
                     make_thing("stable",   (int[]){1, 12}, 0),
                     make_thing("unstable", (int[]){1, 13}, 1));

   feature *c_sc = make_feature("credit score", 2, 3, TOTAL);
   push_things(c_sc, make_thing("good",         (int[]){2,  0}, 0),
                     make_thing("excellent",    (int[]){2,  1}, 1),
                     make_thing("poor",         (int[]){2,  2}, 2),
                     make_thing("good",         (int[]){2,  3}, 0),
                     make_thing("poor",         (int[]){2,  4}, 2),
                     make_thing("good",         (int[]){2,  5}, 0),
                     make_thing("good",         (int[]){2,  6}, 0),
                     make_thing("poor",         (int[]){2,  7}, 2),
                     make_thing("excellent",    (int[]){2,  8}, 1),
                     make_thing("excellent",    (int[]){2,  9}, 1),
                     make_thing("good",         (int[]){2, 10}, 0),
                     make_thing("excellent",    (int[]){2, 11}, 1),
                     make_thing("poor",         (int[]){2, 12}, 2),
                     make_thing("good",         (int[]){2, 13}, 0));

   feature *loan = make_feature("existing loan", 3, 2, TOTAL);
   push_things(loan, make_thing("no",  (int[]){3,  0}, 0),
                     make_thing("no",  (int[]){3,  1}, 0),
                     make_thing("yes", (int[]){3,  2}, 1),
                     make_thing("no",  (int[]){3,  3}, 0),
                     make_thing("no",  (int[]){3,  4}, 0),
                     make_thing("yes", (int[]){3,  5}, 1),
                     make_thing("no",  (int[]){3,  6}, 0),
                     make_thing("yes", (int[]){3,  7}, 1),
                     make_thing("no",  (int[]){3,  8}, 0),
                     make_thing("yes", (int[]){3,  9}, 1),
                     make_thing("no",  (int[]){3, 10}, 0),
                     make_thing("no",  (int[]){3, 11}, 0),
                     make_thing("no",  (int[]){3, 12}, 0),
                     make_thing("yes", (int[]){3, 13}, 1));

   feature *prop = make_feature("property", 4, 2, TOTAL);
   push_things(prop, make_thing("yes",  (int[]){3,  0}, 0),
                     make_thing("yes",  (int[]){3,  1}, 0),
                     make_thing("no",   (int[]){3,  2}, 1),
                     make_thing("yes",  (int[]){3,  3}, 0),
                     make_thing("no",   (int[]){3,  4}, 1),
                     make_thing("no",   (int[]){3,  5}, 1),
                     make_thing("yes",  (int[]){3,  6}, 0),
                     make_thing("no",   (int[]){3,  7}, 1),
                     make_thing("yes",  (int[]){3,  8}, 0),
                     make_thing("yes",  (int[]){3,  9}, 0),
                     make_thing("no",   (int[]){3, 10}, 1),
                     make_thing("yes",  (int[]){3, 11}, 0),
                     make_thing("yes",  (int[]){3, 12}, 0),
                     make_thing("yes",  (int[]){3, 13}, 0));


   /*feature *study_hrs = make_feature("Study Hours", 0, 3, TOTAL);
   push_things(study_hrs, make_thing("High",    (int[]){0, 0}, 0),
                          make_thing("High",    (int[]){0, 1}, 0),  
                          make_thing("Medium",  (int[]){0, 2}, 1),
                          make_thing("Low",     (int[]){0, 3}, 2),
                          make_thing("Low",     (int[]){0, 4}, 2),
                          make_thing("Medium",  (int[]){0, 5}, 1),
                          make_thing("Low",     (int[]){0, 6}, 2),
                          make_thing("Medium",  (int[]){0, 7}, 1));
   
   feature *attendance = make_feature("Attendance", 1, 2, TOTAL);
   push_things(attendance, make_thing("Good", (int[]){0, 0}, 0),
                           make_thing("Poor", (int[]){0, 1}, 1),  
                           make_thing("Good", (int[]){0, 2}, 0),
                           make_thing("Good", (int[]){0, 3}, 0),
                           make_thing("Poor", (int[]){0, 4}, 1),
                           make_thing("Poor", (int[]){0, 5}, 1),
                           make_thing("Good", (int[]){0, 6}, 0),
                           make_thing("Good", (int[]){0, 7}, 0));

   feature *ass_subm = make_feature("Assignment Submitted", 2, 2, TOTAL);
   push_things(ass_subm, make_thing("Yes", (int[]){0, 0}, 0),
                         make_thing("Yes", (int[]){0, 1}, 0),  
                         make_thing("Yes", (int[]){0, 2}, 0),
                         make_thing("No",  (int[]){0, 3}, 1),
                         make_thing("No",  (int[]){0, 4}, 1),
                         make_thing("Yes", (int[]){0, 5}, 0),
                         make_thing("Yes", (int[]){0, 6}, 0),
                         make_thing("No",  (int[]){0, 7}, 1));*/

   //push_nodes(root, make_node(ftr2), make_node(ftr3));
   //print_node(root);
   //node *node1 = make_node(ftr3);
   //print_node(node1);

   //do_stuff(root, label, 2, ftr2, ftr3);
   node *root2 = pre_do_stuff(label, 5, income, empl, loan, prop, c_sc);
   //print_node(root);
   //print_node(root->branch[0]->node);
   //print_node(root->branch[1]->node);
   /*for(int i=0;i<root->branch[0]->node->feature->dis_total;i++) {
       //print_ftr(root->branch[0]->node->branch[i]->node->feature);
   }*/ 
   
   //thing **things = give_arr(stuff, stuff->dis_thing[0]);
   //thing **persona = give_arr_personal(things, stuff->how_many_each[0], ftr3);
   /*for(int i=0;i<root->feature->how_many_each[1];i++) {
       //printf("\nname: %s\npos: %d\tindex: %d\n", persona[i]->name, persona[i]->position[1], persona[i]->index);
   }*/ 
   //feature *l = make_label(label, 5);
   //print_ftr(l);
   //printf("%s's gini impurity indivisually is %lf\n", stuff->dis_thing[1]->name, compute_gini_thingwise(give_arr(stuff, stuff->dis_thing[1]), label,stuff->how_many_each[1]));
    
    //printf("%s's weighted mean gini impurity is %lf\n", stuff->name, compute_gini_overall(stuff, label));

    //printf("\n%lf\n", lowest((double[]){6, 4 ,1, 5}, 4));
    //printf("%d\n", stuff->how_many_each[0]); 
    //printf("%s as a branch has %lf gini impurity for all the [thing]s of %s\n", stuff->dis_thing[0]->name, *compute_gini_overall_for_branch(root, root->branch[0], ftr2, label, stuff->how_many_each[0]), ftr2->name);
    print_node_rec(root2);

}
