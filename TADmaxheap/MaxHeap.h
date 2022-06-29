#ifndef MAXHEAP_H_INCLUDED
#define MAXHEAP_H_INCLUDED

typedef struct maxheap *Maxheap;
Maxheap CriaHeap();
Maxheap LiberaHeap(Maxheap m);
int Insere(Maxheap m, int chave, void *objeto, size_t sizeObj);
int Remove(Maxheap m, void *objeto, size_t sizeObj);
void Imprime(Maxheap m);

#endif // MAXHEAP_H_INCLUDED
