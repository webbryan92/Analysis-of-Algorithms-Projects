Queue Templates:

Queue0 - is an implementation of Queue using raw C++ Nodes & Pointers 
         and is for demonstrating how to build linked lists using nodes & pointers.

Queue1 - is an implementation layered on component ChainPosition.
         ChainPosition is an abstraction for nodes & pointers and
         allows the software developer of Queue1 to think abstractly
         about building linked lists instead of thinking directly with
         memory addresses used in raw nodes & pointers.

Queue2 - is an implementation layered on component List and
         is for demonstrating how to layer one component on another.


-----------------------------------------------------------------

QueueOfText - is the same as Queue0 except it is not a template, rather
              QueueOfText has type text fixed as the only item that
              can be stored by a queue declared from QueueOfText

-----------------------------------------------------------------

QueueChecking - is a checking component for all the Queue templates.
                It wraps the Queue and when a Queue operation is called
                by a client program, and that operation has a non-trivial
                requires clause, QueueChecking will check to see if the
                requirement for calling has been met by the client program.