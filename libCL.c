#include "libCL.h"

struct object *malloc2(int tamanho){  // aloca a struct
	struct object *aux = (struct object *) malloc(tamanho);
	aux->cont = 1;
	return aux;
}

void atrib(void* x, struct object *p){  // coloca o valor na area de endereco passada
    p->value = x;
}

void statusdeclaracao(struct object *aux, FILE *fp){

    fprintf(fp, "Foi declarado o ponteiro no endereco %d\n\n", aux);

}

void status(struct object *aux, FILE *fp){  // mostra o estado da memória

        fprintf(fp, "O ponteiro agora aponta para o endereco %d do heap\n", aux);
        fprintf(fp, "O ponteiro tem valor %d\n", aux->value);
        fprintf(fp, "O endereco %d agora tem %d apontamento(s)\n\n", aux, aux->cont);

}

void atrib2(struct object **p, struct object **q, FILE *fp){   // realiza a atribuicao de ponteiros
	struct object *temp;  //variavel temporaria para armazenar o endereco que mudou seu apontamento
	if(q != NULL){
        temp = (*p);
        (*p) = (*q);
        (*q)->cont++;
        temp->cont--;

        if (temp->cont==0){
            fprintf(fp, "A area %d agora tem 0 apontamentos e foi liberada\n", temp);
            free(temp);
        }
	}else{
       temp = (*p);
       (*p) = NULL;
       temp->cont--;
       if (temp->cont==0){
            fprintf(fp, "A area %d agora tem 0 apontamentos e foi liberada\n", temp);
            free(temp);
        }
	  }
}

