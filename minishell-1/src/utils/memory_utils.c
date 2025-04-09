#include <stdlib.h>

void *ft_malloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
    {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void ft_free(void *ptr)
{
    if (ptr)
    {
        free(ptr);
        ptr = NULL;
    }
}

void **ft_free_matrix(void **matrix)
{
    size_t i;

    if (!matrix)
        return NULL;
    for (i = 0; matrix[i]; i++)
    {
        ft_free(matrix[i]);
    }
    ft_free(matrix);
    return NULL;
}