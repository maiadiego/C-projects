#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "MaxHeap.h"

#define MAX 10

typedef struct item{
    int chave;
    void *obj;
}Item;

struct maxheap{
    Item vet[MAX];
    int total_elementos;
};

Maxheap CriaHeap(){
    int i;
    Maxheap m = (Maxheap)malloc(sizeof(struct maxheap));
    m->total_elementos = 0;

    for(i = 0; i < MAX; i++){
        m->vet[i].obj = NULL;
        m->vet[i].chave = -1;
    }
    return m;
}

Maxheap LiberaHeap(Maxheap m){
    int i;
    for(i = 0; i < m->total_elementos; i++)
        free(m->vet[i].obj);
    free(m);
    return NULL;
}

int Cheio(Maxheap m){
    if(m->total_elementos == MAX)
        return 1;
    return 0;
}

int Vazio(Maxheap m){
    if(m->total_elementos == 0)
        return 1;
    return 0;
}

int indice_pai(int x, int total_elementos){

    int indice;
    indice = (int)floor((x-1)/2);

    if(x <= 0 || x >= total_elementos)
        return -1;
    else
        return indice;
}

void ajustar_subindo(Maxheap m, int pos, int total_elementos, size_t sizeObj){
    int pai;
    Item aux;
    aux.obj = (void*)malloc(sizeObj);

    if(pos != -1){
        pai = indice_pai(pos, total_elementos);
        if(pai != -1){
            if(m->vet[pos].chave > m->vet[pai].chave){
                aux.chave = m->vet[pos].chave;
                memcpy(aux.obj, m->vet[pos].obj, sizeObj);

                m->vet[pos].chave = m->vet[pai].chave;
                memcpy(m->vet[pos].obj, m->vet[pai].obj, sizeObj);

                m->vet[pai].chave = aux.chave;
                memcpy(m->vet[pai].obj, aux.obj, sizeObj);

                ajustar_subindo(m, pai, total_elementos, sizeObj);
                free(aux.obj);
            }
        }
    }

}

int Insere(Maxheap m, int chave, void *objeto, size_t sizeObj){
    if(Cheio(m)){
        printf("O Heap esta cheio!\n");
        return 0;

    }else{
        m->vet[m->total_elementos].chave = chave;
        m->vet[m->total_elementos].obj = (void*)malloc(sizeObj);
        memcpy(m->vet[m->total_elementos].obj, objeto, sizeObj);

        m->total_elementos+=1;

        ajustar_subindo(m, m->total_elementos-1, m->total_elementos, sizeObj);
        return 1;
    }
}

int indice_filho_esq(int x, int total_elementos){
    int indice;

    indice = (2 * x) + 1;
    if(x >= total_elementos || indice >= total_elementos)
        return -1;
    else
        return indice;
}

int indice_filho_dir(int x, int total_elementos){
    int indice;

    indice = (2 * x) + 2;
    if(x >= total_elementos || indice >= total_elementos)
        return -1;
    else
        return indice;
}

void ajustar_descendo(Maxheap m, int pos, int total_elementos, size_t sizeObj){
    Item aux1;
    aux1.obj = (void*)malloc(sizeObj);

    int esq = indice_filho_esq(pos, total_elementos);

    if(pos != -1 && esq != -1){

        int dir  = indice_filho_dir(pos,total_elementos);
        int indice_maior_filho = esq;

        if(dir!= -1 && m->vet[dir].chave > m->vet[indice_maior_filho].chave){

            indice_maior_filho = dir;

        }
        if(m->vet[indice_maior_filho].chave > m->vet[pos].chave){

            aux1.chave = m->vet[pos].chave;
            memcpy(aux1.obj, m->vet[pos].obj, sizeObj);

            m->vet[pos].chave = m->vet[indice_maior_filho].chave;
            memcpy(m->vet[pos].obj, m->vet[indice_maior_filho].obj, sizeObj);

            m->vet[indice_maior_filho].chave = aux1.chave;
            memcpy(m->vet[indice_maior_filho].obj, aux1.obj, sizeObj);

            free(aux1.obj);

            ajustar_descendo(m, indice_maior_filho, total_elementos, sizeObj);
        }
    }
}

int Remove(Maxheap m, void *objeto, size_t sizeObj){
    if(Vazio(m)){
        printf("Maxheap vazio!\n");
        return 0;
    }else{
        m->total_elementos -= 1;
        memcpy(objeto, m->vet[0].obj, sizeObj);

        m->vet[0].chave = m->vet[m->total_elementos].chave;
        memcpy(m->vet[0].obj, m->vet[m->total_elementos].obj, sizeObj);

        m->vet[m->total_elementos].chave = -1;
        free(m->vet[m->total_elementos].obj);

        ajustar_descendo(m, 0 ,m->total_elementos, sizeObj);

        return 1;
    }
}

void Imprime(Maxheap m){
    int i;
    if(Vazio(m))
        printf("O heap esta vazio!\n");
    else{
        for(i = 0; i < m->total_elementos; i++){
            printf("%d ", m->vet[i].chave);
        }
        printf("\n");
    }
}

