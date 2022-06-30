// A C++ program for Prim's Minimum
// Spanning Tree (MST) algorithm. The program is
// for adjacency matrix representation of the adjMatrix
#include <stdio.h>
#include <stdlib.h>
#include <math.h>  
#include <iostream>
using namespace std;
 
#define INT_MAX 2147483647

// Number of vertices in the adjMatrix
#define V 5
 
// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(int key[], bool mstSet[], int nLines)
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < nLines; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
 
    return min_index;
}
 
// A utility function to print the
// constructed MST stored in parent[]
void printMST(int parent[], float *adjMatrix, int nLines)
{
    cout<<"Edge \t  Weight\n";
    for (int i = 1; i < nLines; i++)
        printf("%d - %d    %.2f\n", parent[i], i, adjMatrix[i*nLines + parent[i]]);
}
 
// Function to construct and print MST for
// a adjMatrix represented using adjacency
// matrix representation
void primMST(float *adjMatrix, int nLines)
{
    // Array to store constructed MST
    int parent[nLines];
     
    // Key values used to pick minimum weight edge in cut
    int key[nLines];
     
    // To represent set of vertices included in MST
    bool mstSet[nLines];
 
    // Initialize all keys as INFINITE
    for (int i = 0; i < nLines; i++)
        key[i] = INT_MAX, mstSet[i] = false;
 
    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex.
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST
 
    // The MST will have nLines vertices
    for (int count = 0; count < nLines - 1; count++)
    {
        // Pick the minimum key vertex from the
        // set of vertices not yet included in MST
        int u = minKey(key, mstSet, nLines);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
 
        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST
        for (int v = 0; v < nLines; v++)
 
            // adjMatrix[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if adjMatrix[u][v] is smaller than key[v]
            if (adjMatrix[u*nLines+v] && mstSet[v] == false && adjMatrix[u*nLines+v] < key[v])
                parent[v] = u, key[v] = adjMatrix[u*nLines+v];
    }
 
    // print the constructed MST
    printMST(parent, adjMatrix, nLines);
}
 
// Code for adjacency matrix
// count the number of lines in the file called filename   
int countLines(char *filename, int *valuesX, int *valuesY){    
    FILE *fp = fopen(filename,"r");
    int nLines=1, x, y;
    char c;

    if (fp == NULL){
        return 0;
    }
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n')
            nLines++;
    // Close the file
    fclose(fp);
    return nLines;
}

void storeValues(char *filename, int *valuesX, int *valuesY){
    int x, y, lines;
    FILE *fp = fopen(filename,"r");
    if (fp == NULL){
        printf("Error: NULL file\n");
    }

    while(!feof(fp)) {
        fscanf(fp, "%d %d %d", &lines, &x, &y);
        valuesX[lines-1] = x;
        valuesY[lines-1] = y;
    }
    fclose(fp);
}

float euclidianDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2)
                + pow(y2 - y1, 2) * 1.0);
}

void addEdge(float *arr, int i, int j, int nLines, int *valuesX, int *valuesY) {
    arr[i*nLines + j] = euclidianDistance(valuesX[i], valuesY[j], valuesX[j], valuesY[i]);
}

// Print the matrix
void printAdjMatrix(float *arr, int nLines) {
    int i, j;

    FILE * arq = fopen("provisorio.txt","w");
    for (i = 0; i < nLines; i++) {
        fprintf(arq,"%d: ", i);
        for (j = 0; j < nLines; j++) {
            fprintf(arq,"%.2f    ", arr[i*nLines + j]);
        }
        fprintf(arq,"\n");
    }
}

int *ivec_alloc(int n){
    int *tmp = (int*) malloc(n * sizeof(int));
    return tmp;
}

// Driver code
int main(int argc, char *argv[]) {
    int nLines;
    int *valuesX, *valuesY;
    float *adjMatrix;

    // Counting how many vertices
    nLines = countLines(argv[1], valuesX, valuesY);

    //Memory allocation
    valuesX = ivec_alloc(nLines);
    valuesY = ivec_alloc(nLines);
    adjMatrix = (float *)malloc(nLines * nLines * sizeof(float)); 

    storeValues(argv[1], valuesX, valuesY);
    for(int i = 0; i < nLines; i++){
        for(int j = 0; j < nLines; j++){
            addEdge(adjMatrix, i, j, nLines, valuesX, valuesY);
        }
    }
    free(valuesX);
    free(valuesY);
 
    // Print the solution
    primMST(adjMatrix, nLines);
    printAdjMatrix(adjMatrix, nLines);

    return 0;
}
 
