Tommy Lu

In my code I declare my pointers as

int* ptr

However you can also do it like so

int *ptr

Both is perfectly valid to the complier but for clarity you should probably do it like the latter

int *ptr

So that when you declare pointers, you remember to declare them all, in the cases below ptr1 and ptr2 are not pointers and only ptr is.

int* ptr, ptr1, ptr2
int *ptr, ptr1, ptr2

until they are declared like so

int *ptr, *ptr1, *ptr2
