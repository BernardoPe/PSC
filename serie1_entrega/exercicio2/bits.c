#include <limits.h>
#include <stdio.h>

#define ULONG_BIT (CHAR_BIT * sizeof(unsigned long))

unsigned long getbits(unsigned long data[], int index, int length) {

    if (length > ULONG_BIT) 
        return 0;

    int start_index = index / ULONG_BIT; //array index
    int start_bit = index % ULONG_BIT; //first bit
    unsigned long result = 0;

    if (length == ULONG_BIT) 
        return (data[start_index] >> start_bit); 
    
    if (start_bit + length <= ULONG_BIT) //check if value belongs to two array indexes or not 
        result = (data[start_index] >> start_bit) & ((1UL << length) - 1); //mask the value through length
    else {
        int first_part_length = ULONG_BIT - start_bit;
        int second_part_length = length - first_part_length;
        result = (data[start_index] >> start_bit) & ((1UL << first_part_length) - 1); //get first index part
        result |= (data[start_index + 1] & ((1UL << second_part_length) - 1)) << first_part_length; //add second index part
    }
    
    return result;
}

void setbits(unsigned long data[], int index, int length, unsigned long value) {
    int start_index = index / ULONG_BIT;
    int start_bit = index % ULONG_BIT;

    if (length > ULONG_BIT) {
        return;
    }
    
    if (start_bit + length <= ULONG_BIT) {
        unsigned long mask = ((1UL << length) - 1) << start_bit;
        data[start_index] = (data[start_index] & ~mask) | ((value << start_bit) & mask); //sets the mask bits to the value and all other bits in the array index to 0
    } else {
        int first_part_length = ULONG_BIT - start_bit;
        int second_part_length = length - first_part_length;
        unsigned long first_mask = ((1UL << first_part_length) - 1) << start_bit;
        unsigned long second_mask = (1UL << second_part_length) - 1;
        data[start_index] = (data[start_index] & ~first_mask) | ((value << start_bit) & first_mask);
        data[start_index + 1] = (data[start_index + 1] & ~second_mask) | (value >> first_part_length);
    }
}