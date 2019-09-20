# fork-tree.c

This program implements the below process tree. Initial process
generates child A and through recursion the tree is made. each
leaf in the tree sleeps for 10 seconds and then terminates. each
middle node generates its children and waits for them to terminate.
Then it exits too. Exiting status of processes should be printed.

* process tree:</br>
    ------------A------------</br>
    ----------/--\\-----------</br>
    ---------B---C-----------</br>
    --------|----------------</br>
    --------D----------------</br>
