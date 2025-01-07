#include <stdio.h>
#include <malloc.h>
#define ERRO -1
#define true 1
#define false 0
typedef int bool;
typedef int TIPOCHAVE;

typedef struct {
  TIPOCHAVE chave;
  // outros campos...
} REGISTRO;

typedef struct aux {
  REGISTRO reg;
  struct aux* prox;
} ELEMENTO, *PONT;

typedef struct {
  PONT cabeca;
  PONT inicio;
  PONT fim;
} FILA;

/* Inicialização da fila ligada (a fila jah esta criada e eh apontada pelo endereco em f) */
void inicializarFila(FILA* f){
  f->cabeca = (PONT) malloc(sizeof(ELEMENTO));
  f->cabeca->prox = f->cabeca;
  f->inicio = f->cabeca;
  f->fim = f->cabeca;
} 

void testando(FILA* f){

  if(f->inicio->prox == f->cabeca) printf("Foda-se");

} 

int tamanho(FILA* f) {
  PONT end = f->cabeca->prox;
  int tam = 0;
  while (end != f->cabeca){
    tam++;
    end = end->prox;
  }
  return tam;
} /* tamanho */

int tamanhoEmBytes(FILA* f) {
  return (tamanho(f)*sizeof(ELEMENTO)) + sizeof(FILA);
} /* tamanhoEmBytes */

void destruirFila(FILA* f) {
  PONT end = f->inicio;
  while (end != f->cabeca){
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  free(f->cabeca);
} 

PONT retornarPrimeiro(FILA* f, TIPOCHAVE *ch){
  if (f->inicio != f->cabeca) *ch = f->inicio->reg.chave;
  return f->inicio;
}

PONT retornarUltimo(FILA* f, TIPOCHAVE* ch){
  if (f->inicio == f->cabeca) return NULL;
  *ch = f->fim->reg.chave;
  return f->fim;
}

bool inserirNaFila(FILA* f,REGISTRO reg) {
  PONT novo = (PONT) malloc(sizeof(ELEMENTO));

  novo->reg = reg;
  novo->prox = f->cabeca;

  if(f->inicio == f->cabeca){
    f->cabeca->prox = novo;
    f->inicio = novo;
  }else{
    f->fim->prox = novo;
  }
  f->fim = novo;

  return true;
}

bool excluirDaFila(FILA* f, REGISTRO* reg) {

  if (f->inicio==f->cabeca){
    return false;                     
  }

  *reg = f->inicio->reg;

  PONT apagar = f->inicio;
  f->inicio = f->inicio->prox;
  free(apagar);

  if (f->inicio == f->cabeca){
    f->fim = f->cabeca;
  }else{
    f->cabeca->prox = f->inicio;
  }

  return true;
} 

void exibirFila(FILA* f){
  PONT end = f->inicio;
  printf("Fila: \" ");
  while (end != f->cabeca){
    printf("%d ", end->reg.chave);
    end = end->prox;
  }
  printf("\"\n");
} 
