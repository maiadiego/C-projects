#include "libCL.h"

int main(){

    FILE *fp = fopen("log.txt", "w");

    if(fp == NULL)
        printf("Erro na criacao do log\n");
    else{
        fprintf(fp, "------Ponteiro v------\n");
        struct object *v;
        statusdeclaracao(v, fp);
        fprintf(fp, "------Ponteiro w------\n");
        struct object *w;
        statusdeclaracao(w, fp);
        fprintf(fp, "------Ponteiro c------\n");
        struct object *c;
        statusdeclaracao(c, fp);

        fprintf(fp, "------Ponteiro v------\n");
        v = malloc2(sizeof(int));
        atrib(10, v);
        if(v == NULL)
            fprintf(fp, "O ponteiro agora e nulo\n\n");
        else
            status(v, fp);

        fprintf(fp, "------Ponteiro w------\n");
        w = malloc2(sizeof(int));
        atrib(20, w);
        if(w == NULL)
            fprintf(fp, "O ponteiro agora e nulo\n\n");
        else
            status(w, fp);

		fprintf(fp, "------Ponteiro v------\n");
        atrib2(&v, &w, fp); // v apontará para o mesmo lugar que w
        if(v == NULL)
            fprintf(fp, "O ponteiro agora e nulo\n\n");
        else
            status(v, fp);

        fprintf(fp, "------Ponteiro w------\n");
        if(w == NULL)
            fprintf(fp, "O ponteiro agora e nulo\n\n");
        else
            status(w, fp);

		fprintf(fp, "------Ponteiro c------\n");
        c = malloc2(sizeof(char));
        atrib('Z', c);
        if(c == NULL)
            fprintf(fp, "O ponteiro agora e nulo\n\n");
        else
            status(c, fp);


        fprintf(fp, "------Ponteiro v------\n");
        atrib2(&v, NULL, fp);
        if(v == NULL)
            fprintf(fp, "O ponteiro agora e nulo\n\n");
        else
            status(v, fp);

        fprintf(fp, "------Ponteiro w------\n");
        if(w == NULL)
            fprintf(fp, "O ponteiro agora e nulo\n\n");
        else
            status(w, fp);
    }

	return 0;

}

