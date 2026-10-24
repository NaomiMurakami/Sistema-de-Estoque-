#ifndef UTIL_H
#define UTIL_H

/* Validacoes genericas (nao dependem da lista de produtos).
   Todas retornam 1 se o valor e valido e 0 caso contrario. */

int validarInteiroPositivo(int valor);        /* valor > 0  */
int validarInteiroNaoNegativo(int valor);     /* valor >= 0 */
int validarFloatPositivo(float valor);        /* valor > 0  */
int validarTextoPreenchido(const char texto[]);
int validarCaractereEm(char c, const char permitidos[]);

#endif
