#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
    void *carga;
    struct elemento *proximo;
}TElemento;

typedef struct lista{
    TElemento *inicio;
    TElemento *final;
    int qntde;
}TLista;

TElemento *criarElemento(void *carga){
    TElemento *novo = malloc(sizeof(TElemento));
    novo->carga = carga;
    novo->proximo = NULL;
    return novo;
}

TLista *criarLista(){
    TLista *lse = malloc(sizeof(TLista));
    lse->inicio = NULL;
    lse->final = NULL;
    lse->qntde = 0;
    return lse;
}

void inserir_inicio(TLista *lse, void *carga_nova){
    TElemento *elem = criarElemento(carga_nova);
    if(lse->inicio == NULL){
        lse->inicio = elem;
        lse->final = elem;
    }
    else{
        elem->proximo = lse->inicio;
        lse->inicio = elem;
    }
    lse->qntde ++;
}

void inserir_final(TLista *lse,void *carga_nova){
    TElemento *elem = criarElemento(carga_nova);
    if(lse->inicio == NULL){
        lse->inicio = elem;
        lse->final = elem;
    }
    else{
        TElemento *ultimo = lse->final;
        ultimo->proximo = elem;
        lse->final = elem;
    }
    lse->qntde ++;
}

void remover_inicio (TLista *lse, TDestroy destroy){
    TElemento *primeiro = lse->inicio;
    if(lse->inicio != NULL){
        void *carga = primeiro->carga;
        if (lse->inicio == lse->final)
        {
            lse->inicio = NULL;
            lse->final = NULL;
        }
        else{
            lse->inicio = primeiro->proximo;
        }
        free(primeiro);
        destroy(carga);
        lse->qntde--;
    }
}

