#include <string.h>
#include "util.h"

int validarInteiroPositivo(int valor) {
  return valor > 0;
}

int validarInteiroNaoNegativo(int valor) {
  return valor >= 0;
}

int validarFloatPositivo(float valor) {
  return valor > 0;
}

int validarTextoPreenchido(const char texto[]) {
  return strlen(texto) > 0;
}

int validarCaractereEm(char c, const char permitidos[]) {
  return strchr(permitidos, c) != NULL && c != '\0';
}
