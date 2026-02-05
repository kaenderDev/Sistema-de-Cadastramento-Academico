#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <string.h>

typedef struct {  
    void* data;            // Valor no array
    size_t element_size;   // tamanho do elemento no array em bytes
    size_t size;           // tamanho do array
} Array;

Array array_create(size_t element_size, size_t size);   //criar o array
void array_set(Array* arr, size_t index, void* value);  // coloca o valor em uma posicao 
void* array_get_ptr(Array* arr, size_t index);          // pega o ponteiro do elemento 
void array_free(Array* arr);                            // libera a memoria


#define ARRAY_GET(type, arr, index) \
        (*(type*)array_get_ptr(arr, index))   //typecast com macro 
#endif         