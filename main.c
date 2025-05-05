#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafi.h"
#include "code.h"
#define MAX 100


int main()
{
   /*


     graph *G = nuovoGrafo(4);


    aggiungiArco(G, 0, 1, 10);
    aggiungiArco(G, 0, 3, 20);
    aggiungiArco(G, 0, 2, 30);
    aggiungiArco(G, 1, 0, 30);
    aggiungiArco(G, 1, 3, 13);
    aggiungiArco(G, 2, 1, 90);
    aggiungiArco(G, 2, 3, 30);
    aggiungiArco(G, 3, 1, 20);
    aggiungiArco(G, 3, 0, 20);

    stampa_grafo(G);


     int nodo = 0;
    printf("\nGrado entrante del nodo %d: %d\n", nodo, gradoEntrante(G, nodo));
    printf("Grado uscente del nodo %d: %d\n", nodo, gradoUscente(G, nodo));

    rimuoviArco(G, 1, 3);
    modifica_peso_arco(G, 0,1,15);
    printf("\nil grafo dopo aver modificato il peso di un arco e':\n ");
    stampa_grafo(G);

    printf("\nil grafo trasposto e': \n");
    graph *G2 = NULL;
    G2 = creaTrasposto(G);
    stampa_grafo(G2);

    printf("\n");

    edge *arcoMaggiore = trovaArcoPesoMaggiore(G);
    printf("L'arco con il peso maggiore ha peso %d e chiave %d.\n", arcoMaggiore->peso, arcoMaggiore->key);
    edge *arcoMinore = trovaArcoPesoMinore(G);
    printf("L'arco con il peso minore ha peso %d e chiave %d.\n", arcoMinore->peso, arcoMinore->key);

    int distanza[4]; //array che memorizza le distanze più brevi dalla sorgente a tutti gli altri nodi nel grafo
    int prev[4]; //array che memorizza i predecessori lungo i percorsi minimi dalla sorgente a tutti gli altri nodi nel grafo

    dijkstra(G,0,distanza,prev);

    printf("\nRisultato dijkstra: \n");

    for(int i=0; i<4; i++)
    {
        printf("Distanza da 0 a %d: %d\n", i, distanza[i]);
    }

    printf("\n");
    printf("RISULTATO DFS: ");
    dfs(G);

    printf("\n");

    printf("RISULTATO BFS: ");
    bfs(G);

    int **adjMatrix = graphToAdjMatrix(G);
    printf("\n");
    printf("\nstampo la matrice di adiacenza: (stampando direttamente i pesi)\n");
    // Stampa la matrice di adiacenza
    for (int i = 0; i < G->nv; i++)
    {
        for (int j = 0; j < G->nv; j++)
        {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("stampo il grafo ottenuto dalla matrice:\n");
    graph *G3 = adjMatrixToGraph(adjMatrix, 4);
    stampa_grafo(G3);

    eliminaGrafo(G3);

    */

    int nArchi1,i1;
    int u1, v1, peso1;

    printf("quanti archi vuoi inserire?\n ");
    scanf("%d",&nArchi1);
    graph *G1 = nuovoGrafo(nArchi1);

    for(i1=0;i1<nArchi1;i1++){
        printf("inserisci il nodo da cui parte l'arco %d°: ",i1+1);
        scanf("%d",&u1);
        printf("inserisci il nodo che riceve l'arco %d°: ",i1+1);
        scanf("%d",&v1);
        printf("inserisci il peso dell'arco %d°: ",i1+1);
        scanf("%d",&peso1);
        aggiungiArco(G1,u1,v1,peso1);
    }

    printf("\n");
    printf("stampa del primo grafo: \n");
    stampa_grafo(G1);
    printf("\n");

    int nArchi2,i2;
    int u2, v2, peso2;

    printf("quanti archi vuoi inserire?\n ");
    scanf("%d",&nArchi2);
    graph *G2 = nuovoGrafo(nArchi2);

    for(i2=0;i2<nArchi2;i2++){
        printf("inserisci il nodo da cui parte l'arco %d°: ",i2+1);
        scanf("%d",&u2);
        printf("inserisci il nodo che riceve l'arco %d°: ",i2+1);
        scanf("%d",&v2);
        printf("inserisci il peso dell'arco %d°: ",i2+1);
        scanf("%d",&peso2);
        aggiungiArco(G2,u2,v2,peso2);
    }
    printf("\n");
    printf("stampa del secondo grafo: \n");
    stampa_grafo(G2);
    printf("\n");

        graph* sum = sommaGrafi(G1, G2);
    if (sum != NULL) {
        printf("Grafo somma dei due grafi:\n");
        stampa_grafo(sum);
    }

    return 0;
}
