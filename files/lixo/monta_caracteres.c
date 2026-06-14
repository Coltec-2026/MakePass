#include <string.h>

void MontaCaracteres(char caracteres[], int mai, int min, int num, int simb) {

  strcpy(caracteres, "");

  if(mai == 1) {
    strcat(caracteres, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  }

  if(min == 1) {
    strcat(caracteres, "abcdefghijklmnopqrstuvwxyz");
  }

  if(num == 1) {
    strcat(caracteres, "0123456789");
  }

  if(simb == 1) {
    strcat(caracteres, "!@#$%&*?");
  }
} 
