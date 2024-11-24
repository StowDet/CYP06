#include "corrector.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define PALABRAS 50000

void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos) {
    FILE* fp;
    fopen_s(&fp, szNombre, "r");
    if (fp == NULL) {
        printf("No se pudo abrir el archivo: %s\n", szNombre);
        return;
    }
 char buffer[1024];
    iNumElementos = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        int i = 0;
        while (buffer[i] != '\0') {
            char palabra[TAMTOKEN] = { 0 };
            int j = 0;

            
            while (buffer[i] != '\0' && !strchr(" \t,;().\r\n", buffer[i])) {
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
                    
                    strcpy_s(szPalabras[iNumElementos], palabra);
                    iEstadisticas[iNumElementos] = 1;
                    iNumElementos++;
                }
            }

            
            while (buffer[i] != '\0' && strchr(" \t,;().\r\n", buffer[i])) {
                i++;
            }
        }
    }

    fclose(fp);

    
    for (int i = 0; i < iNumElementos - 1; i++) {
        for (int j = i + 1; j < iNumElementos; j++) {
            if (strcmp(szPalabras[i], szPalabras[j]) > 0) {
                char tempPalabra[TAMTOKEN];
                strcpy_s(tempPalabra, TAMTOKEN, szPalabras[i]);
                strcpy_s(szPalabras[i], TAMTOKEN, szPalabras[j]);
                strcpy_s(szPalabras[j], TAMTOKEN, tempPalabra);

                int tempEstadistica = iEstadisticas[i];
                iEstadisticas[i] = iEstadisticas[j];
                iEstadisticas[j] = tempEstadistica;
            }
        }
    }
}

void ClonaPalabras(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int& iNumSugeridas) {

}
void ListaCandidatas(char szPalabrasSugeridas[][TAMTOKEN], int iNumSugeridas, char szPalabras[][TAMTOKEN], int iEstadisticas[], int iNumElementos, char szListaFinal[][TAMTOKEN], int iPeso[], int iNumLista) {

}