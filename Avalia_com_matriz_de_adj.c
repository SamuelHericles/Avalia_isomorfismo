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
            return ((2*n-i-1)*i/2+(j-1)-1)-(n-2);
        else
            return ((2*n-j-1)*j/2+(i-1)-1)-(n-2);
}

void mostraGrafo(grafo g){
    for(int i = 0; i< g->tamanho*(g->tamanho-1)/2 ;i++){
        printf("%d \t",g->adjMatrix[i]);
    }
    printf("\n");
}

grafo criaGrafo(int n,int p){
    grafo g = malloc(sizeof*g);
    g->tamanho = n;
    g->adjMatrix =  malloc(g->tamanho*(g->tamanho-1)/2*sizeof(grafo));

    for(int i = 0; i < g->tamanho*(g->tamanho-1)/2 ; i++){
        int prob = rand()%100;
        //printf("%d \t",prob);
        if(prob>p) g->adjMatrix[i] = 1;
        else g->adjMatrix[i] = 0;
    }
    printf("\n");
    return g;
}

int Verifica_num_vertices(grafo g1, grafo g2){
    printf("%d||%d\n",g1->tamanho,g2->tamanho);
    if(g1->tamanho == g2->tamanho)
        return 1;
    return 0;
}

int Verifica_num_arestas(grafo g1, grafo g2){
    int a=0;
    int b=0;
    for(int i = 0; i < g1->tamanho*(g1->tamanho-1)/2 ; i++)
        if(g1->adjMatrix[i] == 1) a+=1;
        
    for(int j = 0; j < g2->tamanho*(g2->tamanho-1)/2 ; j++)
        if(g2->adjMatrix[j] == 1) b+=1;
    
    printf("%d||%d\n",a,b);
    if(a == b)
        return 1;
    return 0;

}

int Verifica_circuitos(grafo g1, grafo g2){
    int a=0;
    int b=0;
    for(int i = 0; i < (g1->tamanho*(g1->tamanho-1)/2) ; i++)
        if(g1->adjMatrix[i] == 1) a+=1;
        
    for(int j = 0; j < (g2->tamanho*(g2->tamanho-1)/2) ; j++)
        if(g2->adjMatrix[j] == 1) b+=1;
    
    printf("->%d||%d\n",g1->tamanho,a);
    printf("->%d||%d\n",g2->tamanho,b);
    if(( a >= g1->tamanho-1)&&( b >= g2->tamanho-1)){
        printf("Ambos os Grafos possuem circuitos\n");
        return 1;
    } else {
        printf("Nao eh certeza afirmar que ambos os grafos possuem circuitos\n");
        return 0;
    }
}


void Verifica_desconexo(grafo g1, grafo g2){
    int c = 0;
    
    for(int i = 0; i < (g1->tamanho*(g1->tamanho-1)/2) ; i++){
            c += g1->adjMatrix[i];
            printf("%d\n",c);
    }
    printf("%d\n",c);
}
int Verifica_comp_desconexas(grafo g1, grafo g2);
int forca_bruta(grafo g1, grafo g2);


int main(){
    srand(time(NULL));

    struct Grafo *g1,*g2;
    g1 = criaGrafo(5,60);
    g2 = criaGrafo(5,30);
    
    printf("\n");
    mostraGrafo(g1);
    printf("\n");
    mostraGrafo(g2);
    printf("\n");

    Verifica_num_vertices(g1,g2);
    Verifica_num_arestas(g1,g2);
    Verifica_circuitos(g1,g2);
    Verifica_desconexo(g1,g2);


    printf("\n");
    
}