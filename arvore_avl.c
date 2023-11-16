#include <stdio.h>

typedef struct no{
    int chave;
    struct no *filho_esq;
    struct no *filho_dir;
    int altura;
}TNo;

TNo *criarNo(int chave){
    TNo *novo = malloc(sizeof(TNo));
    novo->chave = chave;
    novo->filho_esq = NULL;
    novo->filho_dir = NULL;
    novo->altura = 1;
    return novo;
}

int maior(int a, int b){
	if (a>b)
	{
		return a;
	}else{
		return b;
	}
}
int altura (TNo *raiz){
	if (raiz== NULL)
	{
		return 0;
	}
	return raiz->altura;
}

int fatorBalanceamento(TNo *raiz){
	if(raiz == NULL){
		return 0;
	}
	int fb;
	fb = altura(raiz->filho_esq) - altura(raiz->filho_dir);
	return fb;
}

TNo *rotacaoSimplesEsq(TNo *raiz){
	TNo *x,y;
	x = raiz->dir;
	y = x->filho_esq;
	raiz->filho_dir = y;
	x->filho_esq = raiz;

	raiz->altura = maior(altura(raiz->filho_dir),altura(raiz->filho_esq))+1;
	y->altura = maior(altura(y->filho_dir),altura(y->filho_esq))+1;

	return x;
}
TNo *rotacaoSimplesDir(TNo *raiz){
	TNo *x,y;
	x = raiz->esq;
	y = x->filho_dir;
	raiz->filho_esq = y;
	x->filho_dir = raiz;

	raiz->altura = maior(altura(raiz->filho_dir),altura(raiz->filho_esq))+1;
	y->altura = maior(altura(y->filho_dir),altura(y->filho_esq))+1;

	return x;
}
TNo *rotacaoDuplaEsq(TNo *raiz){
	raiz->filho_dir = rotacaoSimplesDir(raiz->filho_dir);
	return rotacaoSimplesEsq(raiz);
}
TNo *rotacaoDuplaDir(TNo *raiz){
	raiz->filho_esq = rotacaoSimplesDir(raiz->filho_esq);
	return rotacaoSimplesEsq(raiz);
}

TNo *balancear(TNo *raiz){
	int fb = fatorBalanceamento(raiz);
	if (fb < -1 && fatorBalanceamento(raiz->filho_esq <= 0))
	{
		return rotacaoSimplesEsq(raiz);
	}else if (fb > 1 && fatorBalanceamento(raiz->filho_esq >= 0))
	{
		return rotacaoSimplesDir(raiz);
	}else if (fb < -1 && fatorBalanceamento(raiz->filho_esq > 0))
	{
		return rotacaoDuplaEsq(raiz);
	}else if (fb > 1 && fatorBalanceamento(raiz->filho_esq < 0))
	{
		return rotacaoDuplaDir(raiz); 
	}
	return raiz;
}

TNo *inserir(TNo *raiz,int chave){
    if(raiz == NULL){
        return criarNo(chave);
        
    }else if(chave < raiz->chave){
        raiz->filho_esq =  inserir(raiz->filho_esq,chave);
    }else if(chave > raiz->chave){
        raiz->filho_dir = inserir(raiz->filho_dir,chave);
    }else{
    	return raiz;
    }
    raiz->altura = maior(altura(raiz->filho_esq),altura(raiz->filho_dir))+1;

    TNo *raiz = balancear(raiz);

    return raiz;
}
