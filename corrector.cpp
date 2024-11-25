#include "corrector.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define PALABRAS 50000

int es_caracter_valido(char c);
int es_caracter_valido(char c) {
    char alfabeto[] = "abcdefghijklmnopqrstuvwxyzñáéíóú";
    c = tolower(c);
    for (size_t i = 0; i < strlen(alfabeto); i++) {
        if (c == alfabeto[i]) {
            return 1;
        }
    }
    return 0;
}

void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
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
            while (buffer[i] != '\0' && es_caracter_valido(buffer[i])) {
                palabra[j++] = tolower(buffer[i++]);
            }
            if (j > 0) {
                palabra[j] = '\0';
                int encontrada = -1;
                for (int k = 0; k < iNumElementos; k++) {
                    if (strcmp(szPalabras[k], palabra) == 0 && encontrada != k) {
                        encontrada = k;
                    }
                }

                if (encontrada != -1) {
                    iEstadisticas[encontrada]++;
                }
                else {

                    if (iNumElementos < PALABRAS) {
                        strcpy_s(szPalabras[iNumElementos], palabra);
                        iEstadisticas[iNumElementos] = 1;
                        iNumElementos++;
                    }
                    else {
                        fclose(fp);
                        return;
                    }
                }
            }
            while (buffer[i] != '\0' && !es_caracter_valido(buffer[i])) {
                i++;
            }
        }
    }

    fclose(fp);
}

void ClonaPalabras(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int& iNumSugeridas) {

}
void ListaCandidatas(char szPalabrasSugeridas[][TAMTOKEN], int iNumSugeridas, char szPalabras[][TAMTOKEN], int iEstadisticas[], int iNumElementos, char szListaFinal[][TAMTOKEN], int iPeso[], int iNumLista) {

}