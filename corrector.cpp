#include "corrector.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
void Diccionario(char* szNombre) {
    FILE* fp = fopen(szNombre, "r"); 
    if (fp == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer); 
    }

    fclose(fp);
}
void ClonaPalabras(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int& iNumSugeridas) {

}
void ListaCandidatas(char szPalabrasSugeridas[][TAMTOKEN], int iNumSugeridas, char szPalabras[][TAMTOKEN], int iEstadisticas[], int iNumElementos, char szListaFinal[][TAMTOKEN], int iPeso[], int iNumLista) {

}