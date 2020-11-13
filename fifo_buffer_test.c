// fifo_buffer_test.c : Testbench to help debug 
//

#include <stdio.h>
#include <stdlib.h>

#include "fifo_buffer.h"

int main()
{
    //create buffer and buffer pointer
    fifo_buffer test;
    fifo_buffer_ptr testptr = &test;
    
    //to hold the return value to determine if an operation succeeded
    bool success=false;

    /*to insert random numbers*/
    time_t t;
    srand((unsigned) time(&t));
    
    //init test
    printf("Testing init function: \n");
    fifo_buffer_init(testptr);
    printf("Space left in buffer: %d\n", testptr->space_left);
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("Buffer Index: %d   Value at buffer: %c\n", i, testptr->buffer[i]);
    }


    //*************************
    //inserting bytes
    printf("\nTesting inserting bytes: \n");
    printf("Bytes in buffer before operations: %d\n", testptr->space_left);
    for (int i = 0; i < BUFFER_SIZE; i++) {
        success = fifo_buffer_put_char(testptr, (char)rand());
        printf("Insertion %d succeeded? (1 == true): %d  Space left in buffer: %d\n", i, success, testptr->space_left);
    }
    printf("\n");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("Buffer Index: %d   Value at buffer: %hhX\n", i, testptr->buffer[i]);
    }

    //retrieving bytes
    printf("\nTesting getting bytes: \n");
    char test_return_char;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        success = fifo_buffer_get_char(testptr, &test_return_char);
        printf("Value returned: %hhX   Open bytes in buffer: %d   Get operation succeeded if 1: %d\n", test_return_char, testptr->space_left, success);
        if (success != 1) break;
    }

    success = fifo_buffer_get_char(testptr, &test_return_char);//operation should fail
    printf("Operation fail? (0 here): %d  Open bytes in buffer: %d\n", success, testptr->space_left);


    //*************************
    //inserting uint16 
    printf("\nTesting adding uint16: \n");
    printf("Bytes in buffer before operations: %d\n", testptr->space_left);
    for (int i = 0; i < BUFFER_SIZE/2; i++) {
        success = fifo_buffer_put_uint16(testptr,(unsigned short)rand());
        printf("Insertion %d succeeded? (1 == true): %d  Space left in buffer: %d\n", i, success, testptr->space_left);
    }
    printf("\n");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("Buffer Index: %d   Value at buffer: %hhX\n", i, testptr->buffer[i]);
    }
    
    //retrieving 16 bit integers
    printf("\nTesting getting uint16: \n");
    unsigned short test_return_number;
    for (int i = 0; i < BUFFER_SIZE / 2; i++) {
        success = fifo_buffer_get_uint16(testptr, &test_return_number);
        printf("Value returned: %hX   Open bytes in buffer: %d   Get operation succeeded if 1: %d\n", test_return_number, testptr->space_left, success);
        if (success != 1) break;
    }
    
    success = fifo_buffer_get_uint16(testptr, &test_return_number);//operation should fail
    printf("Operation fail? (0 here): %d  Open bytes in buffer: %d\n", success, testptr->space_left);


    //*************************
    //inserting 32 bit integers
    printf("\nTesting adding uint32: \n");
    printf("Bytes in buffer before operations: %d\n", testptr->space_left);
    int random_int;
    for (int i = 0; i < BUFFER_SIZE / 4; i++) {
        random_int = rand() + (rand() << 16);
        success = fifo_buffer_put_uint32(testptr, random_int);
        printf("Insertion %d value: %X Succeeded? (1 == true): %d  Space left in buffer: %d\n", i, random_int, success, testptr->space_left);
    }
    printf("\n");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("Buffer Index: %d   Value at buffer: %hhX\n", i, testptr->buffer[i]);
    }

    //retrieving 32 bit integers
    printf("\nTesting getting uint32: \n");
    unsigned int test_return_32;
    for (int i = 0; i < BUFFER_SIZE / 4; i++) {
        success = fifo_buffer_get_uint32(testptr, &test_return_32);
        printf("Value returned: %X   Open bytes in buffer: %d    Get operation succeeded if 1: %d\n", test_return_32, testptr->space_left, success);
        if (success != 1) break;
    }

    success = fifo_buffer_get_uint32(testptr, &test_return_number);//operation should fail
    printf("Operation fail? (0 here): %d  Open bytes in buffer: %d\n", success, testptr->space_left);

    return 0;
}
