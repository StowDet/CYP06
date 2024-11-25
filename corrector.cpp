#include "corrector.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define PALABRAS 50000
#define ABECEDARIO "abcdefghijklmnopqrstuvwxyzáéíóú"

int es_palabra_repetida(const char* palabra, char szPalabrasSugeridas[][TAMTOKEN], int iNumSugeridas) {
    for (int i = 0; i < iNumSugeridas; i++) {
        if (strcmp(szPalabrasSugeridas[i], palabra) == 0) {
            return 1; // La palabra ya existe
        }
    }
    return 0;
}

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
    iNumSugeridas = 0;
    int len = strlen(szPalabraLeida);



    // Operaciones: Eliminación, Transposición, Sustitución, Inserción
    for (int i = 0; i < len; i++) {
        // Eliminación
        char copia[TAMTOKEN] = { 0 };
        strncpy_s(copia, TAMTOKEN, szPalabraLeida, i);
        strcpy_s(&copia[i], TAMTOKEN - i, &szPalabraLeida[i + 1]);
        if (!es_palabra_repetida(copia, szPalabrasSugeridas, iNumSugeridas)) {
            strcpy_s(szPalabrasSugeridas[iNumSugeridas++], TAMTOKEN, copia);
        }

        // Sustitución
        for (int j = 0; ABECEDARIO[j] != '\0'; j++) {
            strcpy_s(copia, TAMTOKEN, szPalabraLeida);
            copia[i] = ABECEDARIO[j];
            if (!es_palabra_repetida(copia, szPalabrasSugeridas, iNumSugeridas)) {
                strcpy_s(szPalabrasSugeridas[iNumSugeridas++], TAMTOKEN, copia);
            }
        }

        // Transposición
        if (i < len - 1) {
            strcpy_s(copia, TAMTOKEN, szPalabraLeida);
            char temp = copia[i];
            copia[i] = copia[i + 1];
            copia[i + 1] = temp;
            if (!es_palabra_repetida(copia, szPalabrasSugeridas, iNumSugeridas)) {
                strcpy_s(szPalabrasSugeridas[iNumSugeridas++], TAMTOKEN, copia);
            }
        }
    }

    // Inserción
    for (int i = 0; i <= len; i++) {
        for (int j = 0; ABECEDARIO[j] != '\0'; j++) {
            char copia[TAMTOKEN] = { 0 };
            strncpy_s(copia, TAMTOKEN, szPalabraLeida, i);
            copia[i] = ABECEDARIO[j];
            strcpy_s(&copia[i + 1], TAMTOKEN - i - 1, &szPalabraLeida[i]);
            if (!es_palabra_repetida(copia, szPalabrasSugeridas, iNumSugeridas)) {
                strcpy_s(szPalabrasSugeridas[iNumSugeridas++], TAMTOKEN, copia);
            }
        }
    }
}
void ListaCandidatas(char szPalabrasSugeridas[][TAMTOKEN], int iNumSugeridas, char szPalabras[][TAMTOKEN],
    int iEstadisticas[], int iNumElementos, char szListaFinal[][TAMTOKEN],
    int iPeso[], int* iNumLista) {
    *iNumLista = 0;

    for (int i = 0; i < iNumSugeridas; i++) {
        for (int j = 0; j < iNumElementos; j++) {
            if (strcmp(szPalabrasSugeridas[i], szPalabras[j]) == 0) {
                strcpy_s(szListaFinal[*iNumLista], TAMTOKEN, szPalabras[j]);
                iPeso[*iNumLista] = iEstadisticas[j];
                (*iNumLista)++;
            }
        }
    }
}