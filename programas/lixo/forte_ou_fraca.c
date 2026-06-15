#include <stdio.h> 
#include <string.h>
#include <ctype.h>
int VerificaSenhaForte(char senha[]) {

  int i;

  int maiuscula = 0;
  int minuscula = 0;
  int numero = 0;
  int simbolo = 0;

  if(strlen(senha) < 8) {
    return 0;
  }

  for(i = 0; senha[i] != '\0'; i++) {

    if(isupper(senha[i])) {
      maiuscula = 1;
    }

    else if(islower(senha[i])) {
      minuscula = 1;
    }

    else if(isdigit(senha[i])) {
      numero = 1;
    }

    else {
      simbolo = 1;
    }
  }

  if(maiuscula && minuscula && numero && simbolo) {
    return 1;
  }

  return 0;
}

