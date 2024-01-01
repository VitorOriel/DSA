# Doubly Linked List

The linked list is a very flexible dynamic data structure: items may be added to it or deleted from it at will. A programmer need not worry about how many items a program will have to accommodate: this allows us to write robust programs which require much less maintenance. A very common source of problems in program maintenance is the need to increase the capacity of a program to handle larger collections: even the most generous allowance for growth tends to prove inadequate over time [1].

A doubly linked list is a data structure in which each node contains a data element and two pointers, one pointing to the next node in the sequence and another pointing to the previous node. This bidirectional linkage allows for easy traversal in both forward and backward directions.


## Time complexity
| Operation | Big-O |
| :---: | :---: |
| access | O(n) |
| search | O(n) |
| insert | O(1) |
| delete | O(n) |


## References
1. https://lisha.ufsc.br/teaching/sce/ine6511-2003-2/work/gp/lists.html