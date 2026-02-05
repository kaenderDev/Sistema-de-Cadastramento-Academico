#include "array.h"


Array array_create(size_t element_size, size_t size) {      //cria o array e retorna ele
    Array arr;
    arr.element_size = element_size;
    arr.size = size;
    arr.data = malloc(element_size * size);
    return arr;
}


void array_set(Array* arr, size_t index, void* value) {     //coloca um valor dentro do array
    memcpy(
        (char*)arr->data + index * arr->element_size,      
        value,
        arr->element_size
    );
}


void* array_get_ptr(Array* arr, size_t index) {             //calculo de endereco e retorna o ponteiro do valor
    return (char*)arr->data + index * arr->element_size;
}


void array_free(Array* arr) {                               // libera a memoria e aterra
    free(arr->data);
    arr->data = NULL;
}

