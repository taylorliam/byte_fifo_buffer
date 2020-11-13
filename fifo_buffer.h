/*
	Liam Taylor
	Fifo buffer type definition and function prototypes
*/

#pragma once

/*
bool is defined as a macro in stdbool.h as type _Bool. I don't want to include it in
he main program but we want to return a value telling if the operation succeeded so 
it must be defined here.
*/
#ifndef bool
	#define bool _Bool 
	#define true 1
	#define false 0
#endif // !BOOL



//number of bytes the buffer can hold; 
//try to stick to powers of 2
#define BUFFER_SIZE 32 

typedef struct fifo_buffer{
	
	char buffer[BUFFER_SIZE];
	unsigned short beginning, end, space_left;

}fifo_buffer, * fifo_buffer_ptr;

//Initializes the values of a new fifo buffer
bool fifo_buffer_init(fifo_buffer_ptr new_buffer_ptr);


/* Byte operations */
//Inserts byte into buffer
bool fifo_buffer_put_char(fifo_buffer_ptr buffer_ptr, char insert);

//Removes byte from buffer and stores at addres pointed to by passed pointer
bool fifo_buffer_get_char(fifo_buffer_ptr buffer_ptr, char* value);


/* Uint16 operations */
//Inserts uint16 into buffer
bool fifo_buffer_put_uint16(fifo_buffer_ptr buffer_ptr, unsigned short insert);

//Removes uint16 from buffer and stores at address pointed to by passed pointer
bool fifo_buffer_get_uint16(fifo_buffer_ptr buffer_ptr, unsigned short* value); 


/* Uint32 operations */
//Inserts uint32 into buffer
bool fifo_buffer_put_uint32(fifo_buffer_ptr buffer_ptr, unsigned int insert);

//Removes uint16 from buffer and stores at address pointed to by passed pointer
bool fifo_buffer_get_uint32(fifo_buffer_ptr buffer_ptr, unsigned int* value);