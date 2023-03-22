# cpp-hw_1
create a dynamic array that can have any kind of objects and any size to be chosen
the functions it has:
PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func, PRINT_FUNC print_func) : creates an empty array

void DeleteAdptArray(PAdptArray arr) : deletes the whole array and free's the allocation's

PElement GetAdptArrayAt(PAdptArray array, int index): returns a copy of the element if it exsists and not NULL 

Result SetAdptArrayAt(PAdptArray pAdptArray, int index, PElement element) :  we get an index and an element, we save a copy of
the element in the given index and we free the previous element if there is one in the specific index 

int GetAdptArraySize(PAdptArray arr): returns the size of the array

void PrintDB(PAdptArray arr): prints the array

more specific explainations can be found inside the of the file. 
