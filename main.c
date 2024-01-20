#include <stdio.h>
#include <stdlib.h>

// Define a struct to represent a custom boolean type
struct BitBoolStruct
{
    unsigned char* data;  // Array to store individual bits
    unsigned int size;    // Size of the array in bytes
    unsigned char remainingSpace;  // Remaining space in the last byte
};

// Create an alias for the struct pointer for easier use
typedef struct BitBoolStruct *BitBool;

// Function to construct a BitBool object
BitBool BitBool_Construct()
{
    // Allocate memory for the BitBool structure
    BitBool bitBool = (BitBool)malloc(sizeof(struct BitBoolStruct));
    // Initialize size to 1 byte, allocate memory for the array, and set remainingSpace to 8 bits
    bitBool->size = 1;
    bitBool->data = malloc(sizeof(unsigned char));
    bitBool->remainingSpace = 8;
    return bitBool;
}

// Function to get the total number of bits stored in BitBool object
unsigned int BitBool_GetSize(BitBool bitBool)
{
    // Calculate the size in bits
    return bitBool->size * 8U;
}

// Function to add a bit to the BitBool object
void BitBool_Add(BitBool bitBool, unsigned char bit)
{
    if (bitBool->remainingSpace > 0)
    {
        // Add the bit to the last byte in the array
        *(bitBool->data + bitBool->size - 1) = *(bitBool->data + bitBool->size - 1) | bit % 2 << (bitBool->remainingSpace - 1);
        // Decrease the remaining space in the last byte
        bitBool->remainingSpace--;
    }
    else
    {
        // If there is no space left in the last byte, allocate a new byte
        unsigned char* temp = realloc(bitBool->data, bitBool->size + 1);
        if (temp != NULL)
        {
            bitBool->data = temp;
            // Increase the size of the array
            bitBool->size += 1;
            // Reset the remaining space in the new byte to 8
            bitBool->remainingSpace = 8;
            // Recursively call BitBool_Add to add the bit to the new byte
            BitBool_Add(bitBool, bit);
        }
        else
        {
            // Print an error message if memory allocation fails
            printf("Out of space");
            return;
        }
    }
}

// Function to get the value of a specific bit at a given index
char BitBool_GetBit(BitBool bitBool, unsigned char index)
{
    if (index > bitBool->size * 8)
    {
        // Print an error message if the index is out of bounds
        printf("Out of array");
        return -1;
    }
    // Extract the value of the bit at the specified index
    return (char)((*(bitBool->data + index / 8) >> (7 - (index % 8))) % 2);
}

// Function to print the bits stored in the BitBool object
void BitBool_Print(BitBool bitBool)
{
    printf("|");
    for (short i = 0; i < (bitBool->size * 8); ++i)
    {
        // Print each bit in the array
        printf("%d|", BitBool_GetBit(bitBool, i));
    }
}

// Function to set the value of a specific bit at a given index
void BitBool_SetBit(BitBool bitBool, short index, unsigned char value)
{
    // Create a mask with a 1 at the specified index
    unsigned char mask = 1 << index;
    // Update the value of the bit at the specified index
    *(bitBool->data + index / 8) = ((*(bitBool->data + index / 8) & ~mask) | (value << index % 8));
}

// Function to delete the BitBool object and free the allocated memory
void BitBool_Delete(BitBool bitBool)
{
    // Check if the object and array exist before freeing memory
    if (bitBool == NULL) return;
    if (bitBool->data == NULL) return;
    free(bitBool->data);
    bitBool->data = NULL;
    free(bitBool);
    bitBool = NULL;
}

int main()
{
    return 0;
}
