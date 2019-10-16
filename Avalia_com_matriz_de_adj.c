#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Grafo *grafo;

struct Grafo{
    int tamanho;
    int *adjMatrix;
};

int edge(int i, int j, grafo g){
    return g->adjMatrix[getIndex(i, j, g->tamanho)];
}

void setEdge(int valor, int i, int j, grafo g){
    g->adjMatrix[getIndex(i, j, g->tamanho)] = valor; 
}

int getIndex(int i, int j, int n){
        if(i<j)
            return (2*n-i-1)*i/2+(j-1)-1;
        else
            return (2*n-j-1)*j/2+(i-1)-1;
}

void mostraGrafo(grafo g){
    printf("\n");
    for( int i = 0; i < g->tamanho ; i++){
        for(int  j = 0; j < g->tamanho ; j++){
            if(i != j)printf("%d ",edge(i,j,g));
            else printf("0 ");
        }
        printf("\n");
    }
    printf("\n");
}

grafo criaGrafo(int n,int p){
    grafo g = malloc(sizeof(grafo));
    g->tamanho = n;
    g->adjMatrix =  malloc((g->tamanho*(g->tamanho-1)/2)*sizeof(grafo));

    for(int i = 0; i < (g->tamanho*(g->tamanho-1)/2) ; i++){
        int prob = rand()%100;
        if(prob>p) g->adjMatrix[i] = 1;
        else g->adjMatrix[i] = 0;
    }
    printf("\n");
    return g;
}

int Verifica_num_vertices(grafo g1, grafo g2){
    printf("%d||%d",g1->tamanho,g2->tamanho);
    if(g1->tamanho == g2->tamanho)
        return 1;
    return 0;
}

int Verifica_num_arestas(grafo g1, grafo g2){
    int a=0;
    int b=0;
    for(int i = 0; i < g1->tamanho ; i++){
        for(int j = i+1; j < g1->tamanho; j++){
            if(edge(i,j,g1)==1){
                a++;            }
        }
    }
    for( int i = 0; i < g2->tamanho ; i++){
        for(int  j = i+1; j < g2->tamanho ; j++){
            if(edge(i,j,g2)==1){
                b++;
            }
        }
    }
    printf("%d||%d",a,b);
    if(a == b)
        return 1;
    return 0;

}

void qtdVerticeMesmoGrau(grafo g1, grafo g2){
 int *a1, *a2, i, j,aux;
 a1 = (int*)malloc(g1->tamanho*sizeof(int));
 a2 = (int*)malloc(g2->tamanho*sizeof(int)); 
 
 for(i=0;i<g1->tamanho;i++){
  a1[i]=0;
 }
 for(i=0;i<g2->tamanho;i++){
  a2[i]=0;
 }
 
 for(i = 0; i< g1->tamanho;i++){
  aux = 0;
        for(j = 0; j< g1->tamanho;j++){
         if(i!=j)
    aux+=edge(i,j,g1);
     }
     a1[aux]+=1;
    }
 
 for(i = 0; i< g2->tamanho;i++){
  aux = 0;
        for(j = 0; j< g2->tamanho;j++){
         if(i!=j)
    aux+=edge(i,j,g2);
     }
     a2[aux]++;
    }
 for(i=0;i<g2->tamanho;i++){
  printf("%d    %d\n",a1[i],a2[i]);
 }
}


////////////////////////////////////////////////////////////////////////

int BP_visit(grafo g, int i){ 
   for(i = 0; i < g->tamanho; i++){
       for(int j = i+1; j < g->tamanho; j++){
           if(edge(i,j,g) == 0)
                BP_visit(g,i);
           return 1;
       }
   }
}

int Busca_em_profundidade(grafo g){ 
   int a = 0;
   int pre[(g->tamanho*(g->tamanho-1)/2)];
    for(int i = 0; i < (g->tamanho*(g->tamanho-1)/2); i++) 
        pre[i] = -1;
    //for(int i = 0; i < (g->tamanho*(g->tamanho-1)/2); i++) {
    //if(pre[i] == -1)
    a = BP_visit(g,0); // começa nova etapa
    //}
    return a;
}

////////////////////////////////////////////////////////////////////////


int main(){
    srand(time(NULL));

    struct Grafo *g1,*g2;
    g1 = criaGrafo(5,50);
    g2 = criaGrafo(5,50);
    
    printf("\nGrafo 1 ->\t");
    mostraGrafo(g1);
    printf("\nGrafo 2 ->\t");
    mostraGrafo(g2);
    printf("\n");

    printf("Testes>>>\n");
    printf("Num de vertices->");
    Verifica_num_vertices(g1,g2);
    printf("\nNum de arestas->");
    Verifica_num_arestas(g1,g2);
    printf("\nQtd->\n");
    qtdVerticeMesmoGrau(g1,g2);

    printf("\n\n");
    //printf("%d\n",Busca_em_profundidade(g1));

    printf("\n\n");
    
}