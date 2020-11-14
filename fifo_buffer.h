/*
*	Liam Taylor
*	Fifo buffer type definition and function prototypes
*/

/* possibly remove if not supported by Xilinx SDK compiler */
#pragma once 

/*
* bool is defined as a macro in stdbool.h as type _Bool. We probably don't want to include it in
* the main program but we want to return a value telling us if the operation succeeded so 
* it must be defined here.
*/
#ifndef bool
	#define bool _Bool 
	#define true 1
	#define false 0
#endif // !BOOL

/* number of bytes the buffer can hold */
#define BUFFER_SIZE 8

typedef struct fifo_buffer{
	
	char buffer[BUFFER_SIZE];
	
	/* 
	*  beginning and end indices of valid entrys in the array; the number of bytes open in
	*  the array
	*/
	unsigned short beginning, end, space_left; 

}fifo_buffer, * fifo_buffer_ptr;

/* 
* All operations return true if they complete; false if they do not.
* Put operations fail if they do not have enough space in the buffer to insert
* the value. Get operations fail if there is not enough occupied bytes to return
* the requested type.
*/

/* Initializes the values of a new fifo buffer*/
bool fifo_buffer_init(fifo_buffer_ptr new_buffer_ptr);


/* Byte operations */

/* Inserts byte into buffer */
bool fifo_buffer_put_char(fifo_buffer_ptr buffer_ptr, char insert);

/* Removes byte from buffer and stores at addres pointed to by passed pointer */
bool fifo_buffer_get_char(fifo_buffer_ptr buffer_ptr, char* value);


/* Uint16 operations */

/* Inserts uint16 into buffer */
bool fifo_buffer_put_uint16(fifo_buffer_ptr buffer_ptr, unsigned short insert);

/* Removes uint16 from buffer and stores at address pointed to by passed pointer */
bool fifo_buffer_get_uint16(fifo_buffer_ptr buffer_ptr, unsigned short* value); 


/* Uint32 operations */

/* Inserts uint32 into buffer */
bool fifo_buffer_put_uint32(fifo_buffer_ptr buffer_ptr, unsigned int insert);

/* Removes uint32 from buffer and stores at address pointed to by passed pointer */
bool fifo_buffer_get_uint32(fifo_buffer_ptr buffer_ptr, unsigned int* value);