#ifndef LIBCL_H_INCLUDED
#define LIBCL_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

struct object{
	void* value;
	int cont;
};

struct object *malloc2(int);
void atrib(void*, struct object *);
void statusdeclaracao(struct object *, FILE *);
void status(struct object *, FILE *);
void atrib2(struct object **, struct object **, FILE *);


#endif // LIBCL_H_INCLUDED
