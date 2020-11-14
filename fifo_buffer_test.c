// fifo_buffer_test.c : Testbench to help debug 
//

#include <stdio.h>
#include <stdlib.h>

#include "fifo_buffer.h"


//functions under test are those defined by fifo_buffer.h (excluding init)
#define NUM_FUNCTIONS_UNDER_TEST 6
//number of operations to be tested
#define NUM_OPERATIONS 20


//Uncommnent here to use the older test program
//#define OLD_DEBUG 1

//Uncomment to perfrom random operations 
#define RANDOM_OPS 1


//function to display the buffer
void debug_display_buffer(fifo_buffer_ptr buffer_ptr) {
    int bytes_to_print = BUFFER_SIZE - buffer_ptr->space_left;
    int beginning = buffer_ptr->beginning;
    int end = buffer_ptr->end;

    printf("Buffer from beginning to end: ");
    for (int i = 0; i < bytes_to_print; i++) {
        
        if ((beginning + i) < BUFFER_SIZE) {
            printf("%hhX, ", buffer_ptr->buffer[beginning + i]);
        }
        else {
            printf("%hhX, ", buffer_ptr->buffer[beginning + i - BUFFER_SIZE]);
        }
        
    }
    printf("\n");

}


int main()
{
    /***************************/
    //Common setup to old and new testbench

    //create buffer and buffer pointer
    fifo_buffer test;
    fifo_buffer_ptr testptr = &test;
    
    //to hold the return value to determine if an operation succeeded
    bool success=false;
    
    /*to insert random numbers*/
    time_t t;
    srand((unsigned) time(&t));
    
    
    /***************************/
    //New debug

    success = fifo_buffer_init(testptr);
    printf("Buffer intiaization returned: %d\n\n", success);
    if (success == false) return 1;
    
    unsigned int inserted_uint32;
    unsigned short inserted_uint16;
    char inserted_char;
    
    unsigned int returned_uint32 = 0xFFFFFFFF;
    unsigned short returned_uint16 = 0xFFFF;
    char returned_char = 0xFF;

    
#ifndef RANDOM_OPS /* Used to pick specific values and operations to be performed */
    /* Chage these values to perform the desired operations on the buffer */
    int order_of_operations[7] = { 4,0,5,1,4,2,5 };
    int numbers_to_insert[7] = { 0x1C151CA6, 0x36, 0x00000000, 0x00000000, 0xA67B4D18, 0x151C, 0x00 };
    int op_to_perform;

    for (int i = 0; i < 7; i++)
    {
        op_to_perform = order_of_operations[i];
        switch (op_to_perform) {
            case 0: //put char
                inserted_char = (char)numbers_to_insert[i];
                success = fifo_buffer_put_char(testptr, inserted_char);
                printf("Operation #%d, Success flag: %d, Attempted to insert: %hhX as char, Beginning after op %u, End after op: %u\n",
                    i, success, inserted_char, testptr->beginning, testptr->end);
                debug_display_buffer(testptr);
                break;

            case 1: //get char
                success = fifo_buffer_get_char(testptr, &returned_char);
                printf("Operation #%d, Success flag: %d, char retrieved: %hhX, Beginning after op %u, End after op: %u\n",
                    i, success, returned_char, testptr->beginning, testptr->end);
                debug_display_buffer(testptr);
                break;

            case 2: //put uint16
                inserted_uint16 = numbers_to_insert[i];
                success = fifo_buffer_put_uint16(testptr, inserted_uint16);
                printf("Operation #%d, Success flag: %d, Attempted to insert: %hX as uint16, Beginning after op %u, End after op: %u\n",
                    i, success, inserted_uint16, testptr->beginning, testptr->end);
                debug_display_buffer(testptr);
                break;

            case 3: //get uint16
                success = fifo_buffer_get_uint16(testptr, &returned_uint16);
                printf("Operation #%d, Success flag: %d, uint16 retrieved: %hX, Beginning after op %u, End after op: %u\n",
                    i, success, returned_uint16, testptr->beginning, testptr->end);
                debug_display_buffer(testptr);
                break;

            case 4: //put uint32
                inserted_uint32 = numbers_to_insert[i];
                success = fifo_buffer_put_uint32(testptr, inserted_uint32);
                printf("Operation #%d, Success flag: %d, Attempted to insert: %X as uint32, Beginning after op %u, End after op: %u\n",
                    i, success, inserted_uint32, testptr->beginning, testptr->end);
                debug_display_buffer(testptr);
                break;

            case 5: //get uint32
                success = fifo_buffer_get_uint32(testptr, &returned_uint32);
                printf("Operation #%d, Success flag: %d, uint32 retrieved: %X, Beginning after op %u, End after op: %u\n",
                    i, success, returned_uint32, testptr->beginning, testptr->end);
                debug_display_buffer(testptr);
                break;

            default:
                printf("Error: operation that tried to be tested test is not defined in test bench\n");
                return 1;
                break;
        }
        printf("Index: ");
        for (int j = 0; j < BUFFER_SIZE; j++)
        {
            printf("%8u ", j);
        }
        printf("\nValue: ");
        for (int j = 0; j < BUFFER_SIZE; j++)
        {
            printf("%*hhX ", 8, testptr->buffer[j]);
        }
        printf("\n\n");
    }
#endif

#ifdef RANDOM_OPS /* Performs NUM_OPERATIONS random operations with random numbers */
    
    int op_to_perform;
    int order_of_operations[NUM_OPERATIONS];
    
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        op_to_perform = rand() % NUM_FUNCTIONS_UNDER_TEST; //random value to determine order of operations 
        order_of_operations[i] = op_to_perform; //random value to determine order of operations 

        switch (op_to_perform) {
            case 0: //put char
                inserted_char = (char)rand();
                success = fifo_buffer_put_char(testptr, inserted_char);
                printf("Operation #%d, Success flag: %d, Attempted to insert: %hhX as char, Beginning after op %u, End after op: %u\n",
                    i, success, inserted_char, testptr->beginning, testptr->end);
                debug_display_buffer(testptr);
                break;
            
            case 1: //get char
                success = fifo_buffer_get_char(testptr, &returned_char);
                printf("Operation #%d, Success flag: %d, char retrieved: %hhX, Beginning after op %u, End after op: %u\n",
                    i, success, returned_char, testptr->beginning, testptr->end);
                debug_display_buffer(testptr);
                break;
            
            case 2: //put uint16
                inserted_uint16 = rand();
                success = fifo_buffer_put_uint16(testptr, inserted_uint16);
                printf("Operation #%d, Success flag: %d, Attempted to insert: %hX as uint16, Beginning after op %u, End after op: %u\n",
                    i, success, inserted_uint16, testptr->beginning, testptr->end);
                debug_display_buffer(testptr);
                break;
            
            case 3: //get uint16
                success = fifo_buffer_get_uint16(testptr, &returned_uint16);
                printf("Operation #%d, Success flag: %d, uint16 retrieved: %hX, Beginning after op %u, End after op: %u\n",
                    i, success, returned_uint16, testptr->beginning, testptr->end);
                debug_display_buffer(testptr);
                break;
            
            case 4: //put uint32
                inserted_uint32 = rand() + (rand() << 16);
                success = fifo_buffer_put_uint32(testptr, inserted_uint32);
                printf("Operation #%d, Success flag: %d, Attempted to insert: %X as uint32, Beginning after op %u, End after op: %u\n",
                    i, success, inserted_uint32, testptr->beginning, testptr->end);
                debug_display_buffer(testptr);
                break;
            
            case 5: //get uint32
                success = fifo_buffer_get_uint32(testptr, &returned_uint32);
                printf("Operation #%d, Success flag: %d, uint32 retrieved: %X, Beginning after op %u, End after op: %u\n",
                    i, success, returned_uint32, testptr->beginning, testptr->end);
                debug_display_buffer(testptr);
                break;
            
            default:
                printf("Error: operation that tried to be tested test is not defined in test bench\n");
                return 1;
                break;
        }
        printf("Index: ");
        for (int j = 0; j < BUFFER_SIZE; j++)
        {
            printf("%8u ", j);
        }
        printf("\nValue: ");
        for (int j = 0; j < BUFFER_SIZE; j++)
        {
            printf("%*hhX ", 8, testptr->buffer[j]);
        }
        printf("\n\n");
    }
#endif

    printf("\nTests completed\n");
    return 0;
    
    
    /***************************/
    //Original debug
#ifdef OLD_DEBUG
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
    
    debug_display_buffer(testptr);

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

    success = fifo_buffer_get_uint32(testptr, &test_return_32);//operation should fail
    printf("Operation fail? (0 here): %d  Open bytes in buffer: %d\n", success, testptr->space_left);

    return 0;
#endif
}
