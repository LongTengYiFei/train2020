#pragma onece
#define DEFAULT_LENGTH 20
struct FIFO{
	int avail_bytes;
	int used_bytes;

	int head;
	int rear;
	int max_length;//wo shi zai xiang bu chu geng hao de ming cheng le.

	int (*in)(struct FIFO *self, void *src);
	int (*out)(struct FIFO *self, void *dest);
	int (*used)(struct FIFO *self);//count of btyes
	int (*avail)(struct FIFO *self);//count of bytes
	void (*init)(struct FIFO *self);

	void *data;
	int item_length;
	int (*set_item_length)(struct FIFO *self, int length);
};

void fifo_init(struct FIFO * self, int length);
int fifo_in(struct FIFO *self, void *src);
int fifo_out(struct FIFO *self, void *dest);
int fifo_used(struct FIFO *self);//count of btyes
int fifo_avail(struct FIFO *self);//count of bytes

int set_item_length(struct FIFO *self, int length);

