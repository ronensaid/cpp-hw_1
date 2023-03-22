#include "AdptArray.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
typedef struct AdptArray_ {
    PElement* Pelements;
    int size;
    COPY_FUNC copyF;
    DEL_FUNC delF;
    PRINT_FUNC printF;
} AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func, PRINT_FUNC print_func) {
    // to make sure we aren't sending NULL pointers, return NULL
    if (copy_func == NULL || del_func == NULL || print_func == NULL) {
        return NULL;
    }
    //allcoate memory for the array
    PAdptArray pAdptArray = malloc(sizeof(AdptArray));
    if (pAdptArray == NULL) {
        return NULL;
    }
    //initilize an empty array
    pAdptArray->size = 0;
    pAdptArray->Pelements = NULL;
    pAdptArray->copyF = copy_func;
    pAdptArray->delF = del_func;
    pAdptArray->printF = print_func;
    return pAdptArray;
}
//deletes the whole array and free's the allocation's
void DeleteAdptArray(PAdptArray arr) {
    if (arr != NULL) {
        for (int i = 0; i < arr->size; i++) {
            if (arr->Pelements[i] != NULL) {
                arr->delF(arr->Pelements[i]);
            }
        }
        free(arr->Pelements);
        free(arr);
    }
}
//returns a copy of the element if it exsists and not NULL 
PElement GetAdptArrayAt(PAdptArray array, int index) {
    if (index < 0 || index >= array->size) {
        return NULL;
    }
    PElement element = array->Pelements[index];
    if (element == NULL) {
        return NULL;
    }
    return array->copyF(element);
}    
// we get an index and an element, we save a copy of the element in the given index and we
// free the previous element if there is one in the specific index 
Result SetAdptArrayAt(PAdptArray pAdptArray, int index, PElement element) {
    //in all of the following conditions we check the the allocations are not NULL and the the index is not NULL etc... 
    if (pAdptArray == NULL || index < 0) {
        return FAIL;
    }
    //if the elements are NULL then we set them to be zero's 
    if (pAdptArray->Pelements == NULL) {
        pAdptArray->Pelements = calloc(index + 1, sizeof(PElement));
        if (pAdptArray->Pelements == NULL) {
            return FAIL;
        }
        pAdptArray->size = index + 1;
    }
    //if the index is bigger than the size then we reallocate memory for it.
    else if (index >= pAdptArray->size) {
        PElement* new_elements = realloc(pAdptArray->Pelements, (index + 1) * sizeof(PElement));
        if (new_elements == NULL) {
            return FAIL;
        }
        pAdptArray->Pelements = new_elements;
        //we set the (index + 1 - pAdptArray->size) * sizeof(PElement) bytes of pAdptArray->elements + pAdptArray->size to 0 
        memset(pAdptArray->Pelements + pAdptArray->size, 0, (index + 1 - pAdptArray->size) * sizeof(PElement));
        pAdptArray->size = index + 1;
    }
    //if the element at the given index is not NULL then we delete it
    if (pAdptArray->Pelements[index] != NULL) {
        pAdptArray->delF(pAdptArray->Pelements[index]);
    }
    //if the given element is NULL then we set it NULL at the given index
    if (element == NULL) {
        pAdptArray->Pelements[index] = NULL;
    }
    //else we save a copy of it in the given index.
    else {
        PElement copy = pAdptArray->copyF(element);
        if (copy == NULL) {
            return FAIL;
        }
        pAdptArray->Pelements[index] = copy;
    }
    return SUCCESS;
}
//returns the size of the array
int GetAdptArraySize(PAdptArray arr) {
    if (arr == NULL) return 0;
    return arr->size;
}
//prints the array
void PrintDB(PAdptArray arr) {
    if (arr->printF == NULL) {
        return;
    }

    for (int i = 0; i < arr->size; i++) {
        if (arr->Pelements[i] != NULL) {
            arr->printF(arr->Pelements[i]);
        }
    }
}
