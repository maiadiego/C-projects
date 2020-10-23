#include <stdio.h>
#include <stdlib.h>

struct object{
	int value;
	int cont;
};

struct object *malloc2();
void atrib(int, struct object *);
void statusdeclaracao(struct object *, FILE *);
void status(struct object *, FILE *);
struct object *atrib2(struct object **, struct object **);

int main(){

    FILE *fp = fopen("log.txt", "w");

    if(fp == NULL)
        printf("Erro na criacao do log\n");

    else{

        struct object *v;
        fprintf(fp, "------Ponteiro v------\n");
        statusdeclaracao(v, fp);
        struct object *w;
        fprintf(fp, "------Ponteiro w------\n");
        statusdeclaracao(w, fp);

        v = malloc2();
        atrib(10, v);
        fprintf(fp, "------Ponteiro v------\n");
        if(v == NULL)
            fprintf(fp, "O ponteiro agora e nulo\n\n");
        else{
            status(v, fp);
        }

        w = malloc2();
        atrib(20, w);
        fprintf(fp, "------Ponteiro w------\n");
        if(w == NULL)
            fprintf(fp, "O ponteiro agora e nulo\n\n");
        else{
            status(w, fp);
        }

        v = atrib2(&v, &w); // v apontará para o mesmo lugar que w
        fprintf(fp, "------Ponteiro v------\n");
        if(v == NULL)
            fprintf(fp, "O ponteiro agora e nulo\n\n");
        else{
            status(v, fp);
        }

        fprintf(fp, "------Ponteiro w------\n");
        if(w == NULL)
            fprintf(fp, "O ponteiro agora e nulo\n\n");
        else{
            status(w, fp);
        }

        v = atrib2(&v, NULL);
        fprintf(fp, "------Ponteiro v------\n");
        if(v == NULL)
            fprintf(fp, "O ponteiro agora e nulo\n\n");
        else{
            status(v, fp);
        }

        fprintf(fp, "------Ponteiro w------\n");
        if(w == NULL)
            fprintf(fp, "O ponteiro agora e nulo\n\n");
        else{
            status(w, fp);
        }

    }

	return 0;

}

