/*
	Liam Taylor
	Definition of functions to interact with a fifo buffer
*/

#include "fifo_buffer.h"


/*
Initialization for a new buffer. Sets all buffers to initially be zero and
sets the position in the buffer to the first byte. 
Not efficient for very large buffers but should only have to be run on 
startup.
*/

bool fifo_buffer_init(fifo_buffer_ptr new_buffer_ptr) { 
	
	new_buffer_ptr->beginning = 0;
	new_buffer_ptr->end = 0;
	new_buffer_ptr->space_left = BUFFER_SIZE;
	
	for (int i = 0; i < BUFFER_SIZE; i++) {
		new_buffer_ptr->buffer[i] = 0x00;
	}
	return true;
}


/*
8 bit char(Byte) operations
*/
bool fifo_buffer_put_char(fifo_buffer_ptr buffer_ptr, char insert) {
	
	if (buffer_ptr->space_left > 0) { //enough space to add the byte
		//different cases to ensure array is circular
		if (buffer_ptr->end < BUFFER_SIZE - 1) {
			//insert values into buffer	
			buffer_ptr->buffer[buffer_ptr->end] = insert;

			//update end of buffer and number of available bytes in the buffer
			buffer_ptr->end += 1;
			buffer_ptr->space_left -= 1;
		}
		else {
			buffer_ptr->buffer[buffer_ptr->end] = insert & 0x00FF;

			buffer_ptr->end = 0;
			buffer_ptr->space_left -= 1;
		}
		return true;
	}
	else {
		//not enough space in buffer; operation failed
		return false;
	}
}

bool fifo_buffer_get_char(fifo_buffer_ptr buffer_ptr, char* value) {

	if (buffer_ptr->space_left < BUFFER_SIZE) { //ensure there is a byte to return
		
		//different cases to make the array circular
		if (buffer_ptr->beginning < BUFFER_SIZE - 1) {
			*value = buffer_ptr->buffer[buffer_ptr->beginning];

			buffer_ptr->beginning += 1;
			buffer_ptr->space_left += 1;
		}
		else {
			*value = buffer_ptr->buffer[buffer_ptr->beginning];

			buffer_ptr->beginning = 0;
			buffer_ptr->space_left += 1;
		}
		return true;
	}
	else return false; //no uint16 in buffer; operation failed
}


/*
16 bit unsigned integer operations
*/
bool fifo_buffer_put_uint16(fifo_buffer_ptr buffer_ptr, unsigned short insert) {
	
	if(buffer_ptr->space_left > 1){ //enough space to add the number
		//different cases to ensure array is circular
		if(buffer_ptr->end < BUFFER_SIZE-2){
			//insert values into buffer	
			buffer_ptr->buffer[buffer_ptr->end] = insert & 0x00FF;
			buffer_ptr->buffer[buffer_ptr->end + 1] = insert >> 8;

			//update end of buffer and number of available bytes in the buffer
			buffer_ptr->end += 2;
			buffer_ptr->space_left -= 2;
		}
		else if (buffer_ptr->end == BUFFER_SIZE - 2) {
		
			buffer_ptr->buffer[buffer_ptr->end] = insert & 0x00FF;
			buffer_ptr->buffer[buffer_ptr->end + 1] = insert >> 8;

			buffer_ptr->end = 0;
			buffer_ptr->space_left -= 2;
		}
		else {
			buffer_ptr->buffer[buffer_ptr->end] = insert & 0x00FF;
			buffer_ptr->buffer[0] = insert >> 8;

			buffer_ptr->end = 1;
			buffer_ptr->space_left -= 2;
		}
		return true;
	}
	else {
		//not enough space in buffer; operation failed
		return false;
	}
	
 }

bool fifo_buffer_get_uint16(fifo_buffer_ptr buffer_ptr, unsigned short * value) {
	
	if (buffer_ptr->space_left < BUFFER_SIZE - 1) { //ensure there is a uint16 in the buffer to return
		//different cases to make the array circular
		if (buffer_ptr->beginning < BUFFER_SIZE - 2) {
			*value = (unsigned short)buffer_ptr->buffer[buffer_ptr->beginning] & 0x00FF;
			*value += (unsigned short)buffer_ptr->buffer[buffer_ptr->beginning + 1] << 8;

			buffer_ptr->beginning += 2;
			buffer_ptr->space_left += 2;
		}
		else if (buffer_ptr->beginning == BUFFER_SIZE - 2) {
			*value = (unsigned short)buffer_ptr->buffer[buffer_ptr->beginning] & 0x00FF;
			*value += (unsigned short)buffer_ptr->buffer[buffer_ptr->beginning + 1] << 8;

			buffer_ptr->beginning = 0;
			buffer_ptr->space_left += 2;
		}
		else {
			*value = (unsigned short)buffer_ptr->buffer[buffer_ptr->beginning] & 0x00FF;
			*value += (unsigned short)buffer_ptr->buffer[0] << 8;

			buffer_ptr->beginning = 1;
			buffer_ptr->space_left += 2;
		}
		return true;
	}
	else return false; //no uint16 in buffer; operation failed

}


/*
32 bit unsigned integer operations
*/
bool fifo_buffer_put_uint32(fifo_buffer_ptr buffer_ptr, unsigned int insert){
	
	if (buffer_ptr->space_left > 3) { //enough space to add the 32 bit integer
		
		//different cases to ensure array is circular
		if (buffer_ptr->end < BUFFER_SIZE - 4) {
			//insert values into buffer	
			buffer_ptr->buffer[buffer_ptr->end] = insert & 0x000000FF;
			buffer_ptr->buffer[buffer_ptr->end + 1] = insert >> 8 & 0x000000FF;
			buffer_ptr->buffer[buffer_ptr->end + 2] = insert >> 16 & 0x000000FF;
			buffer_ptr->buffer[buffer_ptr->end + 3] = insert >> 24 & 0x000000FF;


			//update end of buffer and number of available bytes in the buffer
			buffer_ptr->end += 4;
			buffer_ptr->space_left -= 4;
		}
		else if (buffer_ptr->end == BUFFER_SIZE - 4) { 

			//insert values into buffer	
			buffer_ptr->buffer[buffer_ptr->end] = insert & 0x000000FF;
			buffer_ptr->buffer[buffer_ptr->end + 1] = insert >> 8 & 0x000000FF;
			buffer_ptr->buffer[buffer_ptr->end + 2] = insert >> 16 & 0x000000FF;
			buffer_ptr->buffer[buffer_ptr->end + 3] = insert >> 24 & 0x000000FF;


			//update end of buffer and number of available bytes in the buffer
			buffer_ptr->end += 0;
			buffer_ptr->space_left -= 4;
		}
		else if (buffer_ptr->end == BUFFER_SIZE - 3) {

			//insert values into buffer	
			buffer_ptr->buffer[buffer_ptr->end] = insert & 0x000000FF;
			buffer_ptr->buffer[buffer_ptr->end + 1] = insert >> 8 & 0x000000FF;
			buffer_ptr->buffer[buffer_ptr->end + 2] = insert >> 16 & 0x000000FF;
			buffer_ptr->buffer[0] = insert >> 24 & 0x000000FF;


			//update end of buffer and number of available bytes in the buffer
			buffer_ptr->end = 1;
			buffer_ptr->space_left -= 4;
		}
		else if (buffer_ptr->end == BUFFER_SIZE - 2) {

			//insert values into buffer	
			buffer_ptr->buffer[buffer_ptr->end] = insert & 0x000000FF;
			buffer_ptr->buffer[buffer_ptr->end + 1] = insert >> 8 & 0x000000FF;
			buffer_ptr->buffer[0] = insert >> 16 & 0x000000FF;
			buffer_ptr->buffer[1] = insert >> 24 & 0x000000FF;


			//update end of buffer and number of available bytes in the buffer
			buffer_ptr->end = 2;
			buffer_ptr->space_left -= 4;
		}
		else {
			//insert values into buffer	
			buffer_ptr->buffer[buffer_ptr->end] = insert & 0x000000FF;
			buffer_ptr->buffer[0] = insert >> 8 & 0x000000FF;
			buffer_ptr->buffer[1] = insert >> 16 & 0x000000FF;
			buffer_ptr->buffer[2] = insert >> 24 & 0x000000FF;


			//update end of buffer and number of available bytes in the buffer
			buffer_ptr->end = 3;
			buffer_ptr->space_left -= 4;
		}
		return true;
	}
	else {
		//not enough space in buffer; operation failed
		return false;
	}

}

bool fifo_buffer_get_uint32(fifo_buffer_ptr buffer_ptr, unsigned int* value) {

	if (buffer_ptr->space_left < BUFFER_SIZE - 3) { //ensure there is a uint16 in the buffer to return
		
		//different cases to make the array circular
		if (buffer_ptr->beginning < BUFFER_SIZE - 4) {
			
			*value = (unsigned int)buffer_ptr->buffer[buffer_ptr->beginning] & 0x000000FF; //mask is needed as casting to bigger 
																						   //type results signed extension
			*value += (unsigned int)(buffer_ptr->buffer[buffer_ptr->beginning + 1] & 0x000000FF) << 8;
			*value += (unsigned int)(buffer_ptr->buffer[buffer_ptr->beginning + 2] & 0x000000FF) << 16;
			*value += (unsigned int)(buffer_ptr->buffer[buffer_ptr->beginning + 3] & 0x000000FF) << 24;

			//adjust begginning index and the amount of open space in the buffer
			buffer_ptr->beginning += 4;
			buffer_ptr->space_left += 4;
		}
		else if (buffer_ptr->end == BUFFER_SIZE - 4) {
			*value = (unsigned int)buffer_ptr->buffer[buffer_ptr->beginning] & 0x000000FF;
			*value += (unsigned int)(buffer_ptr->buffer[buffer_ptr->beginning + 1] & 0x000000FF) << 8;
			*value += (unsigned int)(buffer_ptr->buffer[buffer_ptr->beginning + 2] & 0x000000FF) << 16;
			*value += (unsigned int)(buffer_ptr->buffer[buffer_ptr->beginning + 3] & 0x000000FF) << 24;

			buffer_ptr->beginning = 0;
			buffer_ptr->space_left += 4;
		}
		else if (buffer_ptr->end == BUFFER_SIZE - 3) {
			*value = (unsigned int)buffer_ptr->buffer[buffer_ptr->beginning] & 0x000000FF;
			*value += (unsigned int)(buffer_ptr->buffer[buffer_ptr->beginning + 1] & 0x000000FF) << 8;
			*value += (unsigned int)(buffer_ptr->buffer[buffer_ptr->beginning + 2] & 0x000000FF) << 16;
			*value += (unsigned int)(buffer_ptr->buffer[0] & 0x000000FF) << 24;

			buffer_ptr->beginning = 1;
			buffer_ptr->space_left += 4;
		}
		else if (buffer_ptr->end == BUFFER_SIZE - 2) {
			*value = (unsigned int)buffer_ptr->buffer[buffer_ptr->beginning] & 0x000000FF;
			*value += (unsigned int)(buffer_ptr->buffer[buffer_ptr->beginning + 1] & 0x000000FF) << 8;
			*value += (unsigned int)(buffer_ptr->buffer[0] & 0x000000FF) << 16;
			*value += (unsigned int)(buffer_ptr->buffer[1] & 0x000000FF) << 24;

			buffer_ptr->beginning = 2;
			buffer_ptr->space_left += 4;
		}
		else {
			*value = (unsigned int)buffer_ptr->buffer[buffer_ptr->beginning] & 0x000000FF;
			*value += (unsigned int)(buffer_ptr->buffer[0] & 0x000000FF) << 8;
			*value += (unsigned int)(buffer_ptr->buffer[1] & 0x000000FF) << 16;
			*value += (unsigned int)(buffer_ptr->buffer[2] & 0x000000FF) << 24;

			buffer_ptr->beginning = 3;
			buffer_ptr->space_left += 4;
		}
		return true;
	}
	else return false; //no uint32 in buffer; operation failed

}