#include "corrector.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define PALABRAS 50000

void Diccionario(char* szNombre) {
    FILE* fp;
    fopen_s(&fp, szNombre, "r");
    if (fp == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    char szPalabras[PALABRAS][TAMTOKEN] = { {0} };
    int iEstadisticas[PALABRAS] = { 0 };
    int iNumElementos = 0;

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        int i = 0;
        while (buffer[i] != '\0') {
            char palabra[TAMTOKEN] = { 0 };
            int j = 0;

            while (buffer[i] != '\0' && buffer[i] != ' ' && buffer[i] != '\n') {
                palabra[j++] = tolower(buffer[i++]);
            }

            if (j > 0) {
                palabra[j] = '\0';
                int encontrada = -1;

                for (int k = 0; k < iNumElementos; k++) {
                    if (strcmp(szPalabras[k], palabra) == 0) {
                        encontrada = k;
                        break;
                    }
                }

                if (encontrada != -1) {
                    iEstadisticas[encontrada]++;
                }
                else if (iNumElementos < PALABRAS) {
                    strcpy(szPalabras[iNumElementos], palabra); 
                    iEstadisticas[iNumElementos] = 1;
                    iNumElementos++;
                }
            }
            i++;
        }
    }

    fclose(fp);
    printf("Diccionario procesado\n");
}
void ClonaPalabras(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int& iNumSugeridas) {

}
void ListaCandidatas(char szPalabrasSugeridas[][TAMTOKEN], int iNumSugeridas, char szPalabras[][TAMTOKEN], int iEstadisticas[], int iNumElementos, char szListaFinal[][TAMTOKEN], int iPeso[], int iNumLista) {

}