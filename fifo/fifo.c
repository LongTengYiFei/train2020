#include"fifo.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
int fifo_in(struct FIFO *self, void *src){
	if(self->item_length == 0)
	{
		printf("please set the item length\n");
		assert(0);
	}
	if(self->avail_bytes < self->item_length)
		return 1;//fail	
	//memcpy
	if(self->max_length - self->rear >= self->item_length)
		memcpy(self->data + self->rear, src, self->item_length);
	else{//fen duan cun chu
		memcpy(self->data + self->rear, src, self->max_length - self->rear);
		memcpy(self->data, src + self->max_length - self->rear, self->item_length - (self->max_length - self->rear));
	}

	self->rear = (self->rear + self->item_length) % self->max_length;
	self->used_bytes += self->item_length;
	self->avail_bytes -= self->item_length;

	self->item_length = 0;
	return 0;//success
}

int fifo_out(struct FIFO *self, void *dest){
	if(self->item_length == 0)
	{
		printf("please set the item length\n");
		assert(0);
	}
	if(self->used_bytes <= 0){
		return 1;//fail	
	}
	//memcpy
	if(self->max_length - self->head >= self->item_length)
		memcpy(dest, self->data + self->head, self->item_length);
	else{
		memcpy(dest, self->data + self->head, self->max_length - self->head);	
		memcpy(dest + self->max_length - self->head, self->data, self->item_length - (self->max_length - self->head));	
	
	}
	self->head = (self->head + self->item_length) % self->max_length;
	self->used_bytes -= self->item_length;
	self->avail_bytes += self->item_length;

	self->item_length = 0;
	return 0;//success
}
 
int fifo_used(struct FIFO *self){
	return self->used_bytes;
}

int fifo_avail(struct FIFO *self){
	return self->avail_bytes;
}

int fifo_set_item_length(struct FIFO *self, int length){
	self->item_length = length;
	return length;
}

void fifo_init(struct FIFO * self, int length){
	self->data = (void *)malloc(length);	
	self->in = fifo_in;
	self->out = fifo_out;
	self->head = 0;
	self->rear = 0;
	self->used = fifo_used;
	self->avail = fifo_avail;
	self->avail_bytes = length;
	self->used_bytes = 0;
	self->max_length = length;
	self->item_length = 0;
	self->set_item_length = fifo_set_item_length;
}
