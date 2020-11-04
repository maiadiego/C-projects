#ifndef LIBCL_H_INCLUDED
#define LIBCL_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

struct object{
	int value;
	int cont;
};

struct object *malloc2();
void atrib(int, struct object *);
void statusdeclaracao(struct object *, FILE *);
void status(struct object *, FILE *);
struct object *atrib2(struct object **, struct object **, FILE *);


#endif // LIBCL_H_INCLUDED
