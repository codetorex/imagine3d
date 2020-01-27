// Resource Memory
#ifndef RESMEM_H
#define RESMEM_H


typedef struct 
{
	int length;
	int pos;
	void *data;
} MEMFILE;

unsigned int	memopen		(char *name,char *type);
void			memclose	(unsigned int handle);
int				memread		(void *buffer, int size, unsigned int handle);
void			memseek		(unsigned int handle, int pos, signed char mode);
int				memtell		(unsigned int handle);

#endif