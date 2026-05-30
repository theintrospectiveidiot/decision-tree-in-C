## decision tree in C

produces a basic decision tree for an arbitrary dataset with n-ary branches, implemented in C. 

the necessary data structures are in [tree.h](https://github.com/theintrospectiveidiot/decision-tree-in-C/blob/master/tree.h) and the functions for the tree to work are in [funcs.h](https://github.com/theintrospectiveidiot/decision-tree-in-C/blob/master/funcs.h).

u can feed or "fit" your data with `make_feature()` and `push_things()`.
also, don't forget to add `#define TOTAL n` at the top, where n is the no. of rows of your dataset.

## P. S. 

it was fun fighting with weird bugs while implementing this.


