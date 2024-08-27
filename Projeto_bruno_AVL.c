#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH_NAME 30

typedef struct no {
        char nome [MAX_LENGTH_NAME];
        int quantidade_sinonimos;
        char** sinonimos;
        struct no *direita, *esquerda;
        int altura_arvore;
} Arvore_AVL;


Arvore_AVL* inicializar_arvore_AVL(Arvore_AVL *arvore_AVL, char nome[], int quantidade_sinonimos, char** sinonimos) {
      arvore_AVL = (Arvore_AVL*)malloc(sizeof(Arvore_AVL));
    if (arvore_AVL != NULL) {
        strcpy(arvore_AVL -> nome, nome);
        arvore_AVL -> direita = NULL;
        arvore_AVL -> esquerda = NULL;
        arvore_AVL -> altura_arvore = 1;
        arvore_AVL -> quantidade_sinonimos = quantidade_sinonimos;
        arvore_AVL -> sinonimos = malloc(quantidade_sinonimos * sizeof(char*));
        for (int i = 0; i < quantidade_sinonimos; i ++) {
          arvore_AVL -> sinonimos[i] = (strdup(sinonimos[i]));
        }
    }   return arvore_AVL;
}


int tamanho_arvore_esquerda (Arvore_AVL *arvore) { 
    if (!arvore) {
      return 0;
  }
      return 1 + tamanho_arvore_esquerda(arvore -> esquerda);
}


int tamanho_arvore_direita (Arvore_AVL *arvore) {
  if (!arvore) { 
        return 0;
  }
    return 1 + tamanho_arvore_direita(arvore -> direita);
}

int maior_subarvore (int a, int b){
    return (a >= b) ? a : b;
}

Arvore_AVL* inserir_arvore (Arvore_AVL* arvore, char nome[], int quantidade_sinonimo, char** sinonimos){
      if (arvore == NULL) {
          return inicializar_arvore_AVL(arvore, nome, quantidade_sinonimo, sinonimos);
      } 
      else {
        int comp = strcmp (arvore -> nome , nome);
        if (comp < 0) {
          arvore -> direita = inserir_arvore (arvore -> direita, nome, quantidade_sinonimo, sinonimos);
        } 
        else { 
          arvore -> esquerda = inserir_arvore (arvore -> esquerda, nome, quantidade_sinonimo, sinonimos);
      }
}     arvore -> altura_arvore = maior_subarvore(tamanho_arvore_esquerda(arvore -> esquerda), tamanho_arvore_direita(arvore -> direita)) + 1;
      return arvore;
}

Arvore_AVL* balancear_direita (Arvore_AVL* arvore) {
   Arvore_AVL *y, *x;

      y = arvore -> esquerda;
      x = y -> direita;
   
      y -> direita = arvore;
      x = arvore -> direita;

       arvore -> altura_arvore = maior_subarvore(tamanho_arvore_esquerda(arvore -> esquerda), tamanho_arvore_direita(arvore -> direita)) + 1;
       y -> altura_arvore = maior_subarvore(tamanho_arvore_esquerda(arvore -> esquerda), tamanho_arvore_direita(arvore -> direita)) + 1;
   
   return y;
}

Arvore_AVL* balancear_esquerda (Arvore_AVL* arvore) {
   Arvore_AVL *y, *x;

      y = arvore -> direita;
      x = y -> esquerda;
   
      y -> esquerda = arvore;
      x = arvore -> esquerda;

      arvore -> altura_arvore = maior_subarvore(tamanho_arvore_esquerda(arvore -> esquerda), tamanho_arvore_direita(arvore -> direita)) + 1;
      y -> altura_arvore = maior_subarvore(tamanho_arvore_esquerda(arvore -> esquerda), tamanho_arvore_direita(arvore -> direita)) + 1;

      return y;

}
   

Arvore_AVL* balacear_direita_esquerda(Arvore_AVL *arvore){

}


Arvore_AVL* balacear_esquerda_direita(Arvore_AVL *arvore){
  
}


Arvore_AVL* Busca_sinonimos (char* input_file, char* output_file, Arvore_AVL *arvore, char nome) {
  if (arvore == NULL) {
    return NULL;
  }
  
  FILE* input = fopen (input_file, "w");
  FILE* output = fopen (output_file, "w");
    
    int cmp = strcmp(arvore->nome, nome);
    fprintf (output, "[ " );
    if (cmp > 0) {
          fprintf (output, " %s -> ", arvore-> nome);
          return Busca_sinonimos(input, output, arvore -> esquerda, nome);
    }

    else {
      if (cmp < 0) { 
          fprintf(output, " %s -> ", arvore -> nome);
          return Busca_sinonimos(input, output, arvore -> direita, nome);
    }

    else if (cmp == 0) {
      fprintf(output, " %s ", arvore -> nome);
      fprintf(output, " ] \n");
      for (int i = 0; i < arvore -> quantidade_sinonimos; i ++) {
        fprintf(output, "%s, ", arvore -> sinonimos[i]);
      }
    }
  }
}

void File (char* input_file, char* output_file) {
    FILE* input = fopen ("entrada.txt", "r");
    FILE* output = fopen ("saida.txt", "w");

    int num_palavras;
    fscanf (input, "%d", &num_palavras);

  Arvore_AVL* arvore = NULL;
     char nome[MAX_LENGTH_NAME];
      int quantidade_sinonimos;
      char** sinonimos = malloc (quantidade_sinonimos *sizeof(char*));


    for (int i = 0; i < num_palavras; i++) {

      fscanf (input, "%s %d", nome, &quantidade_sinonimos);    

      for (int j = 0; j < quantidade_sinonimos; j++) {
        sinonimos[j] = malloc(MAX_LENGTH_NAME * sizeof(char));
        fscanf (input, " %s ", sinonimos[j]); 
      }       
        
       arvore = inserir_arvore(arvore, nome, quantidade_sinonimos, sinonimos);
    }

    int num_Consulta;
    fscanf(output, "%d", num_Consulta);

    for (int i = 0; i < num_Consulta; i++) {
      char consulta [MAX_LENGTH_NAME];
      fscanf(input, "%d", consulta);
       Busca_sinonimos(input, output, arvore , consulta);
    }

       
  
  fclose (input);
  fclose (output);
}



int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf ("Uso : %s <arquivo_entrada> <arquivo_saida \n", argv[0]);
  }

  File(argv[1],argv[2]);

  return 0;

}