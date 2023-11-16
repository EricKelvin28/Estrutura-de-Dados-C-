#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int chave;
    struct no *filho_esq;
    struct no *filho_dir;
}TNo;

TNo *criarNo(int chave){
    TNo *novo = malloc(sizeof(TNo));
    novo->chave = chave;
    novo->filho_esq = NULL;
    novo->filho_dir = NULL;
    return novo;
}

TNo *inserir(TNo *raiz,int chave){
    if(raiz == NULL){
        return criarNo(chave);
        
    }else if(chave < raiz->chave){
        raiz->filho_esq =  inserir(raiz->filho_esq,chave);
    }else if(chave > raiz->chave){
        raiz->filho_dir = inserir(raiz->filho_dir,chave);
    }
    return raiz;
}

TNo *busca(TNo *raiz, int chave){
    if(raiz->chave == chave || raiz == NULL){
        return raiz;
    }
    if(chave < raiz->chave){
        return busca(raiz->filho_esq,chave);
    }else{
        return busca(raiz->filho_dir,chave);
    }
}

void imprimir_arvore(TNo *raiz){
    if(raiz != NULL){
        imprimir_arvore(raiz->filho_esq);
        printf("%d ",raiz->chave);
        imprimir_arvore(raiz->filho_dir);
    }
}

void exibirFolhaNaOrdem(TNo *raiz){
    if(raiz != NULL){
        exibirFolhaNaOrdem(raiz->filho_esq);
        if(raiz->filho_dir == NULL && raiz->filho_esq == NULL){
            printf("%d ",raiz->chave);
        }
        exibirFolhaNaOrdem(raiz->filho_dir);
    }
}

//int altura(){

//}
TNo *valormin(TNo *raiz){
    TNo *atual = raiz;
    while (atual != NULL && atual->filho_esq != NULL)
    {
        atual = atual->filho_esq;
    }
    return atual;
}

TNo *mdM(TNo *raiz){
    return valormin(raiz->filho_dir);
}

TNo *remover(TNo *raiz, int chave){
    if (raiz == NULL)
    {
        return raiz;
    }
    else if (chave < raiz->chave)
    {
        raiz->filho_esq = remover(raiz->filho_esq, chave);
    }
    else if (chave > raiz->chave)
    {
        raiz->filho_dir = remover(raiz->filho_dir, chave);
    }
    else{
        if (raiz->filho_esq ==  NULL)
        {
            TNo *aux = raiz->filho_dir;
            free(raiz);
            return aux;
        }
        else if (raiz->filho_dir ==  NULL)
        {
            TNo *aux = raiz->filho_esq;
            free(raiz);
            return aux;
        }
        TNo* aux = mdM(raiz);
        raiz->chave = aux->chave;
        raiz->filho_dir = remover(raiz->filho_dir,aux->chave);
    }
    return raiz;
}

int main(){
    TNo *arv = NULL;
    arv = inserir(arv,10);
    arv = inserir(arv,145);
    arv = inserir(arv,100);
    arv = inserir(arv,4);
    arv = inserir(arv,1);
    imprimir_arvore(arv);
    arv = remover(arv,100);
    imprimir_arvore(arv);
   // exibirFolhaNaOrdem(arv);
    return 0;
}
