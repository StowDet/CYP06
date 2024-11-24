#include "corrector.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
void Diccionario(char* szNombre) {
    FILE* fp;
    fopen_s(&fp, szNombre, "r");
    if (fp == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        int i = 0;
        while (buffer[i] != '\0') {
            char palabra[50] = { 0 };
            int j = 0;

            
            while (buffer[i] != '\0' && buffer[i] != ' ' && buffer[i] != '\n') {
                palabra[j++] = buffer[i++];
            }

            if (j > 0) {
                palabra[j] = '\0';
                printf("Palabra encontrada: %s\n", palabra);
            }

            i++;
        }
    }

    fclose(fp);
}
void ClonaPalabras(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int& iNumSugeridas) {

}
void ListaCandidatas(char szPalabrasSugeridas[][TAMTOKEN], int iNumSugeridas, char szPalabras[][TAMTOKEN], int iEstadisticas[], int iNumElementos, char szListaFinal[][TAMTOKEN], int iPeso[], int iNumLista) {

}