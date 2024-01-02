#include <stdio.h>
#include <stdlib.h>

// Define a struct to represent a custom boolean type
struct BitBool
{
    unsigned char* arr;  // Array to store individual bits
    unsigned int size;    // Size of the array in bytes
    unsigned char space;  // Remaining space in the last byte
};

// Create an alias for the struct pointer for easier use
typedef struct BitBool *BitBoolType;

// Function to construct a BitBoolType object
BitBoolType construct()
{
    // Allocate memory for the BitBoolType structure
    BitBoolType a = (BitBoolType)malloc(sizeof(struct BitBool));
    // Initialize size to 1 byte, allocate memory for the array, and set space to 8 bits
    a->size = 1;
    a->arr = malloc(sizeof(unsigned char));
    a->space = 8;
    return a;
}

// Function to get the total number of bits stored in BitBoolType object
unsigned int getsize(BitBoolType a)
{
    // Calculate the size in bits
    return a->size * 8U;
}

// Function to add a bit to the BitBoolType object
void add(BitBoolType a, unsigned char arg)
{
    if (a->space > 0)
    {
        // Add the bit to the last byte in the array
        *(a->arr + a->size - 1) = *(a->arr + a->size - 1) | arg % 2 << (a->space - 1);
        // Decrease the remaining space in the last byte
        a->space--;
    }
    else
    {
        // If there is no space left in the last byte, allocate a new byte
        unsigned char* temp = realloc(a->arr, a->size + 1);
        if (temp != NULL)
        {
            a->arr = temp;
            // Increase the size of the array
            a->size += 1;
            // Reset the remaining space in the new byte to 8
            a->space = 8;
            // Recursively call add to add the bit to the new byte
            add(a, arg);
        }
        else
        {
            // Print an error message if memory allocation fails
            printf("out of space");
            return;
        }
    }
}

// Function to get the value of a specific bit at a given index
char getbit(BitBoolType a, unsigned char index)
{
    if (index > a->size * 8)
    {
        // Print an error message if the index is out of bounds
        printf("out of array");
        return -1;
    }
    // Extract the value of the bit at the specified index
    return (char)((*(a->arr + index / 8) >> (7 - (index % 8))) % 2);
}

// Function to print the bits stored in the BitBoolType object
void print(BitBoolType a)
{
    printf("|");
    for (short i = 0; i < (a->size * 8); ++i)
    {
        // Print each bit in the array
        printf("%d", getbit(a, i));
        printf("|");
    }
}

// Function to set the value of a specific bit at a given index
void setbit(BitBoolType a, short index, unsigned char value)
{
    // Create a mask with a 1 at the specified index
    unsigned char mask = 1 << index;
    // Update the value of the bit at the specified index
    *(a->arr + index / 8) = ((*(a->arr + index / 8) & ~mask) | (value << index % 8));
}

// Function to delete the BitBoolType object and free the allocated memory
void delete(BitBoolType a)
{
    // Check if the object and array exist before freeing memory
    if (a == NULL) return;
    if (a->arr == NULL) return;
    free(a->arr);
    a->arr=NULL;
    a=NULL;
}
int main()
{
    return 0;
}
