# C++ threading /mutex demos

## Counter demos

Source File  | Contents
-----------  | --------
counter1.cpp | The base demo. 
counter2.cpp | Adds a bfl. What's wrong with this?
counter3.cpp | Switches to fine grained locking. What's wrong with this?
counter4.cpp | Sometimes the right answer is an absolute partitioning of data with a rollup.
counter5.cpp | Gurney Halleck calls for atomics. Mutex free.

## Blabby demos

Source File | Contents
----------- | --------
blabby1.cpp | The base demo. Threads step on each other.
blabby2.cpp | A mutex is added.
blabby3.cpp | There's just a "one in a million chance" this will deadlock.
