# polymorphism_without_inheritance
An example of polymorphism without inheritance for my own learning. 

Notice the commit history, different iterations are included there. 

Derived from https://www.youtube.com/watch?v=QGcVXgEVMJg&ab_channel=NDCConferences

Notes from video about why inheritance is bad:

Deep Problem #1:
deeper problem is that you changed semantics of the copy assignment, and equality of my document 
when you copy the document you get two pointers to the same objects or, you get a copy of the objects in both
leads to incidental data-structures, thread saftey concerts, a shared pointer is as good a global, you don't know whos on the other end of it
we define an ooperaton in terms of the operation's sematnitcs, reference or value semantics
if we take into accunt the relationships (pointers) becomes one bigger data structure
shared structure also breaks our ability to reason locally about code

regular types where the regular ooperations are implemented with standard names are said to have value semantics
when objects are reffered to indirectly through a shared reference or pointer those objects are said to have value semantics

Deep Problem #2:
-calls are indirect through cirtual calls including the destructor
my_class_t is always heap allocated
access to class_t must be synchronized

C++ compiler doesn't understand reference semantics, compiler can't avoid heap allocation, can sometimes devirtualize calls


Deep Problem #3:
-Polymorphism is intrusive
-document can no longer hold a drawable integer 
if I want to use somebod elses class I need to put some wrapper around their class, to turn it into a drawable class: every file had a bunch of header files and inherits from a ton

Summary:
the requirement of a polymorphic type by definition comes from it's use
we want to handle objects that share a particular attribute as if they were the same, not that we need to create one object that has all the objects we want to treat the same as derived classes
so when we use inheritance to represent this relationship we are building the use of the object into the objects, what we want to do is seperate the use of the objects from the objets themselves.

there is no such thing as polymorphic types, only polymorphic use of similar types

!!!by using inheritance to capture polymorphic use, we shift the burden of use to the type implementaiton, tighly coupling types!!!
!!!inheritance implies variable size, which implies heap allocation!!!!!!!
!!!heap allocation forces a further burden to manage the object lifetime!!!
!!!indirection, heap allocation, and virtualization impacts performance!!!
!!!object lifetime management leads to garbage collection or reference counting!!!
!!!this encourages shared ownership and the proliferation of incedntal datastructures!!!
!!shared ownership leads to synchronization issues, breaks local reasoning, and further impacts performance!!!

inheritance is the base class of evil


//Notes after implementation:
often times theres no performance loss, but infact there is performace gains form not having to use the heap
