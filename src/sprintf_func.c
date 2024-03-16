#include "s21_string.h"

void WideCharacter(wchar_t *pwcs, char *line) { wcstombs(line, pwcs, SIZE); }

void WideSymbol(wchar_t wc, int *n) {
  char s[SIZE] = {'\0'};
  wctomb(s, wc);
  *n = s[0];
}

void IntToChar(long int n, char *line) {
  int i = 0;
  long int buff = n;
  if (n < 0) buff = -buff;
  line[i] = buff % 10 + '0';
  i++;
  while ((buff = buff / 10) > 0) {
    line[i] = buff % 10 + '0';
    i++;
  }
  line[i] = '\0';
  ReverseChar(line);
}

void UnsignedIntToChar(unsigned long int n, char *line) {
  int i = 0;
  unsigned long int buff = n;
  line[i] = buff % 10 + '0';
  i++;
  while ((buff = buff / 10) > 0) {
    line[i] = buff % 10 + '0';
    i++;
  }
  line[i] = '\0';
  ReverseChar(line);
}

void ReverseChar(char *line) {
  int i, j;
  char c;
  for (i = 0, j = s21_strlen(line) - 1; i < j; i++, j--) {
    c = line[i];
    line[i] = line[j];
    line[j] = c;
  }
}

void flag_c(int ArgvC, ParserString *parser) {
  int i = 0;
  if (parser->minNum > 0 && parser->minus == 0 && parser->zero == 0) {
    for (int j = 1; j < parser->minNum; j++) {
      parser->mass[i] = ' ';
      i++;
    }
  }
  if (parser->zero == 1 && parser->minus == 0) {
    for (int j = 1; j < parser->minNum; j++) {
      parser->mass[i] = '0';
      i++;
    }
  }
  parser->mass[i] = ArgvC;
  i++;
  if (parser->minNum > 0 && parser->minus == 1) {
    for (int j = 1; j < parser->minNum; j++) {
      parser->mass[i] = ' ';
      i++;
    }
  }
}

void flag_s(char *line, ParserString *parser) {
  int dlina = 0;
  int end = 0;
  if (parser->fractionalMinNum < (int)s21_strlen(line) &&
      parser->fractionalMinNum > 0) {
    dlina = parser->fractionalMinNum;
  } else if (parser->fractionalMinNum < 0 || parser->fractionalZero == 1) {
    dlina = 0;
  } else {
    dlina = s21_strlen(line);
  }
  if (parser->minNum < dlina && parser->minNum > 0) {
    end = 0;
  } else {
    end = parser->minNum - dlina;
  }
  int i = 0;
  if (parser->minNum > 0 && parser->minus == 0 && parser->zero == 0) {
    for (int j = 0; j < end; j++) {
      parser->mass[i] = ' ';
      i++;
    }
  }
  if (parser->zero == 1 && parser->minus == 0) {
    for (int j = 0; j < end; j++) {
      parser->mass[i] = '0';
      i++;
    }
  }
  for (int count = 0; count < dlina; count++) {
    parser->mass[i] = line[count];
    i++;
  }
  if (parser->minNum > 0 && parser->minus == 1) {
    for (int j = 0; j < end; j++) {
      parser->mass[i] = ' ';
      i++;
    }
  }
}

void flag_d(long int a, ParserString *parser) {
  char buff[4096] = {0};
  int i = 0;
  if (parser->specifier != 'u') {
    if (parser->length == 'l') {
      a = (long int)a;
    } else if (parser->length == 'h') {
      a = (short int)a;
    } else if (parser->length == 0) {
      a = (int)a;
    }
    IntToChar(a, buff);
  }
  if (parser->specifier == 'u') {
    if (parser->length == 'l') {
      a = (unsigned long int)a;
    } else if (parser->length == 'h') {
      a = (unsigned short int)a;
    } else if (parser->length == 0) {
      a = (unsigned int)a;
    }
    UnsignedIntToChar(a, buff);
  }
  if (parser->fractionalZero == 1 && parser->minNum > 0 && a == 0) {
    parser->mass[i] = ' ';
    i++;
  }
  int znak = 0;
  if (parser->specifier != 'u') {
    if ((a > 0 && parser->plus == 1) || a < 0 || (a > 0 && parser->space == 1))
      znak = 1;
  }
  int dlina = 0;
  int end = 0;
  if (parser->fractionalMinNum > 0 || parser->fractionalZero == 1) {
    if (parser->fractionalMinNum > (int)s21_strlen(buff) &&
        parser->fractionalMinNum > 0) {  // ширина самого числа
      dlina = parser->fractionalMinNum - s21_strlen(buff);
    } else if (parser->fractionalMinNum == 0 && parser->zero == 1 &&
               parser->minus == 0 && parser->minNum > 0 &&
               parser->fractionalZero != 1) {
      dlina = parser->minNum - s21_strlen(buff);
    }

    if (parser->minNum > 0 &&
        parser->fractionalMinNum < (int)s21_strlen(buff)) {  // кол-во пробелов
      end = parser->minNum - s21_strlen(buff) - znak;
    } else if (parser->fractionalMinNum > 0 &&
               parser->fractionalMinNum > (int)s21_strlen(buff)) {
      end = parser->minNum - parser->fractionalMinNum - znak;
    }

  } else {
    if (parser->zero == 1 && parser->minus == 0) {
      dlina = parser->minNum - s21_strlen(buff) - znak;
    }
    if ((parser->minNum > 0 && parser->zero == 0) ||
        (parser->minus == 1 && parser->minNum > 0)) {
      end = parser->minNum - s21_strlen(buff) - znak;
    }
  }
  if (parser->minNum > 0 && parser->minus == 0) {
    for (int j = 0; j < end; j++) {
      parser->mass[i] = ' ';
      i++;
    }
  }
  if (a >= 0 && parser->plus == 1 && parser->specifier != 'u') {
    parser->mass[i] = '+';
    i++;
  } else if (a >= 0 && parser->space == 1 && parser->specifier != 'u') {
    parser->mass[i] = ' ';
    i++;
  }
  if (a < 0 && parser->specifier != 'u') {
    parser->mass[i] = '-';
    i++;
  }
  if (dlina > 0) {
    for (int j = 0; j < dlina; j++) {
      parser->mass[i] = '0';
      i++;
    }
  }
  int lenght = 0;
  if (parser->fractionalZero == 1 && a == 0) {
    lenght = 0;
  } else {
    lenght = s21_strlen(buff);
  }
  for (int count = 0; count < lenght; count++) {
    parser->mass[i] = buff[count];
    i++;
  }
  if (parser->minNum > 0 && parser->minus == 1) {
    for (int j = 0; j < end; j++) {
      parser->mass[i] = ' ';
      i++;
    }
  }
}

void flag_f(long double adress, ParserString *parser) {
  int znak = 0;
  char massT[SIZE] = {'\0'};
  if (adress != fabsl(adress)) {
    znak++;
    adress = fabsl(adress);
  }
  flag_f_converter(adress, parser);
  s21_strcpy(massT, parser->mass);
  post_converter(znak, parser, massT);
}

void flag_xX(long int a, ParserString *parser) {
  parser->space = 0;
  if (a == 0) {
    parser->plus = 0;
    flag_d(a, parser);
  } else {
    unsigned long number = a;
    char massT[SIZE] = {'\0'};
    int i = 0, j = 0, start = 0, zeroPoint = 0;
    while (1) {
      int ostatok = 0;
      ostatok = number % 16;
      if (parser->specifier == 'X')
        if (ostatok > 9) ostatok += 55;
      if (parser->specifier == 'x')
        if (ostatok > 9) ostatok += 87;
      if (ostatok <= 9) ostatok += 48;
      massT[i] = (char)ostatok;
      if (number < 16) break;
      number = number / 16;
      i++;
    }
    if (parser->length == 'l') i = 15;
    if (parser->length == 'h') i = 3;
    if (parser->length == 0) i = 7;
    for (; i >= 0; i--, j++) {
      if (massT[i] == '0' && start == 0 && parser->mass[0] == '\0') {
        i--;
        start++;
      }
      if (massT[i] == '\0') {
        j--;
        continue;
      }
      parser->mass[j] = massT[i];
    }
    if (parser->fractionalMinNum > (int)s21_strlen(parser->mass))
      for (; parser->fractionalMinNum > (int)s21_strlen(parser->mass); j++) {
        for (int r = j; r >= 0; r--) parser->mass[r + 1] = parser->mass[r];
        parser->mass[0] = '0';
      }
    if (parser->grill > 0) {
      for (int r = j; r >= 0; r--) parser->mass[r + 2] = parser->mass[r];
      parser->mass[1] = parser->specifier;
      parser->mass[0] = '0';
      j += 2;
    }
    if (parser->minNum > j) {
      int h = parser->minNum - j;
      for (; h > 0; h--, j++) {
        if (parser->minus == 0) {
          for (int r = j; r >= 0; r--) parser->mass[r + 1] = parser->mass[r];
          if ((parser->zero > 0 &&
               parser->minNum <= parser->fractionalMinNum) ||
              (parser->zero > 0 && parser->fractionalMinNum == 0 &&
               parser->fractionalZero == 0)) {
            parser->mass[0] = '0';
            zeroPoint = 1;
          }
          if (parser->zero == 0 ||
              (parser->zero > 0 && parser->minNum > parser->fractionalMinNum &&
               !(parser->zero > 0 && parser->fractionalMinNum == 0 &&
                 parser->fractionalZero == 0)))
            parser->mass[0] = ' ';
        } else {
          parser->mass[j] = ' ';
        }
      }
    }
    if (zeroPoint == 1 && parser->grill > 0) {
      for (int r = 0; r < j; r++)
        if (parser->mass[r] == parser->specifier) parser->mass[r] = '0';
      parser->mass[1] = parser->specifier;
    }
  }
}

void flag_o(long int a, ParserString *parser) {
  parser->space = 0;
  if (a == 0) {
    parser->plus = 0;
    flag_d(a, parser);
  } else {
    unsigned long number = a;
    if (parser->length == 'h') number = (unsigned short int)number;
    if (parser->length == 'l') number = (unsigned long int)number;
    if (parser->length == 0) number = (unsigned int)number;
    char massT[SIZE] = {'\0'};
    int i = 0, j = 0;
    while (1) {
      int ostatok = 0;
      ostatok = number % 8;
      ostatok += 48;
      massT[i] = (char)ostatok;
      if (number < 8) break;
      number = number / 8;
      i++;
    }
    for (; i >= 0; i--, j++) {
      if (massT[i] == '\0') {
        j--;
        continue;
      }
      parser->mass[j] = massT[i];
    }
    if (parser->fractionalMinNum > (int)s21_strlen(parser->mass))
      for (; parser->fractionalMinNum > (int)s21_strlen(parser->mass); j++) {
        for (int r = j; r >= 0; r--) parser->mass[r + 1] = parser->mass[r];
        parser->mass[0] = '0';
      }
    if (parser->grill > 0 && parser->mass[0] != '0') {
      for (int r = j; r >= 0; r--) parser->mass[r + 1] = parser->mass[r];
      parser->mass[0] = '0';
      j++;
    }
    if (parser->minNum > j) {
      int h = parser->minNum - j;
      for (; h > 0; h--, j++) {
        if (parser->minus == 0) {
          for (int r = j; r >= 0; r--) parser->mass[r + 1] = parser->mass[r];
          if (parser->zero > 0) parser->mass[0] = '0';
          if (parser->zero == 0) parser->mass[0] = ' ';
        } else {
          parser->mass[j] = ' ';
        }
      }
    }
  }
}

void flag_p(void *adress, ParserString *parser) {
  unsigned long int convertAdress = (unsigned long int)adress;
  if (convertAdress == 0) {
    parser->fractionalMinNum = 0;
    parser->fractionalZero = 0;
    char *mass = {"(nil)"};
    flag_s(mass, parser);
    return;
  }
  int copyPlus = parser->plus;
  if (copyPlus != 0) parser->minNum -= 1;
  parser->grill = 1;
  parser->zero = 0;
  parser->specifier = 'x';
  parser->length = 'l';
  flag_xX(convertAdress, parser);
}

void flag_eE(long double adress, ParserString *parser) {
  int znak = 0;
  char massT[SIZE] = {'\0'};
  if (adress != fabsl(adress)) {
    znak++;
    adress = fabsl(adress);
  }
  flag_e_converter(adress, parser);
  s21_strcpy(massT, parser->mass);
  post_converter(znak, parser, massT);
}

void flag_gG(double adress, ParserString *parser) {
  if (adress == INFINITY || adress == -INFINITY || adress != adress) {
    if (adress == INFINITY) {
      char infMass[] = {"inf"};
      flag_s(infMass, parser);
    }
    if (adress != adress) {
      char infMass[] = {"nan"};
      flag_s(infMass, parser);
    }
    return;
  }
  int znak = 0;
  char copyMass[SIZE] = "\0";
  parser->specifier = parser->specifier - 2;
  if (adress != fabs(adress)) {
    znak++;
    adress = fabs(adress);
  }
  long double number = adress;
  if (parser->fractionalMinNum == 0 && parser->fractionalZero == 0)
    parser->fractionalMinNum = 6;
  if (parser->fractionalMinNum == 1) parser->fractionalMinNum = 0;
  if (adress < 1) {
    int countMantiss = ((int)(fabsl(log10(number))) + 1);
    if ((countMantiss <= 4 && parser->fractionalMinNum != 6 &&
         parser->fractionalZero != 1) ||
        adress == 0) {
      if (adress == 0) parser->fractionalMinNum -= 1;
      if (parser->fractionalMinNum < countMantiss)
        parser->fractionalMinNum = countMantiss;
      flag_f_converter(adress, parser);
      s21_strcpy(copyMass, parser->mass);
      int pointTrue = -1;
      for (int i = 0; copyMass[i] != '\0'; i++)
        if (copyMass[i] == '.') pointTrue = 1;
      if (parser->grill == 0 && pointTrue == 1)
        for (int i = s21_strlen(copyMass) - 1; i > 0; i--) {
          if (copyMass[i] == '.') {
            copyMass[i] = '\0';
            break;
          }
          if (copyMass[i] == '0' || copyMass[i] == '\0') {
            copyMass[i] = '\0';
          } else {
            break;
          }
        }
    } else {
      if (parser->fractionalMinNum >= 2) parser->fractionalMinNum -= 1;
      flag_e_converter(adress, parser);
      round_e(parser);
      s21_strcpy(copyMass, parser->mass);
    }
  } else {
    int countMantiss = 0;
    countMantiss = (int)log10(floorl(number)) + 1;
    if (countMantiss <= parser->fractionalMinNum) {
      parser->fractionalMinNum = parser->fractionalMinNum - countMantiss;
      if (parser->fractionalMinNum == 0) parser->fractionalZero = 1;
      flag_f_converter(adress, parser);
      s21_strcpy(copyMass, parser->mass);
      int pointTrue = -1;
      for (int i = 0; copyMass[i] != '\0'; i++)
        if (copyMass[i] == '.') pointTrue = 1;
      if (parser->grill == 0 && pointTrue == 1)
        for (int i = s21_strlen(copyMass) - 1; i > 0; i--) {
          if (copyMass[i] == '.') {
            copyMass[i] = '\0';
            break;
          }
          if (copyMass[i] == '0' || copyMass[i] == '\0') {
            copyMass[i] = '\0';
          } else {
            break;
          }
        }
    } else {
      parser->fractionalMinNum = parser->fractionalMinNum - 1;
      if (znak > 0) adress *= -1;
      flag_e_converter(adress, parser);
      round_e(parser);
      s21_strcpy(copyMass, parser->mass);
    }
  }
  post_converter(znak, parser, copyMass);
}

void flag_f_converter(long double adress, ParserString *parser) {
  if (adress != fabsl(adress)) adress = fabsl(adress);
  int countMassT = 0, countMantiss = 0;
  if (parser->fractionalMinNum == 0 && parser->fractionalZero == 0)
    parser->fractionalMinNum = 6;
  long double number = adress;
  if (parser->fractionalMinNum == 0) number = roundl(number);
  char massMantiss[SIZE] = {'\0'}, massT[SIZE] = {'\0'};
  if (log10(number) > 0 || adress == 1) {
    for (int r = (int)log10(number) + 1, i = 0; i < r; countMassT++, i++) {
      massT[countMassT] = (fmodl(number, 10)) + 48;
      number /= 10;
    }
  } else {
    massT[countMassT] = '0';
    countMassT++;
  }
  ReverseChar(massT);
  if (parser->fractionalMinNum == 0) {
    if (parser->grill) {
      massT[countMassT] = '.';
      countMassT++;
    }
    for (int i = 0; massT[i] != '\0'; i++) parser->mass[i] = massT[i];
  } else {
    massT[countMassT] = '.';
    countMassT++;
    number = adress;
    number = fmodl(number, 1);
    for (int i = 0; i < parser->fractionalMinNum + 1; i++, countMantiss++) {
      massMantiss[countMantiss] = (floorl(number = number * 10)) + 48;
      number = fmodl(number, 1);
    }
    int znakUp = 0;
    if (adress != 0 && massMantiss[parser->fractionalMinNum] >= '5') {
      znakUp = 1;
      for (int i = parser->fractionalMinNum - 1; i >= 0; i--) {
        if (znakUp > 0) {
          if (massMantiss[i] + 1 == 58) {
            massMantiss[i] = '0';
          } else {
            massMantiss[i] = massMantiss[i] + 1;
            znakUp = 0;
          }
        }
      }
    }
    if (parser->specifier != 'f' && parser->grill == 0 && adress != 0) {
      int t = countMantiss;
      for (int i = countMantiss - 1; massMantiss[i] == '0'; i--) {
        countMantiss--;
        massMantiss[i] = '\0';
        if (i == 0) break;
      }
      if (t != countMantiss) countMantiss++;
    }
    if (znakUp != 0) {
      for (int i = countMassT - 2; i >= 0; i--) {
        if (znakUp > 0) {
          if (massT[i] + 1 == 58) {
            massT[i] = '0';
          } else {
            massT[i] = massT[i] + 1;
            znakUp = 0;
          }
        }
      }
    }
    if (znakUp != 0) {
      for (int i = countMassT - 1; i > 0; i--) massT[i + 1] = massT[i];
      massT[0] = '1';
      countMassT++;
    }
  }
  for (int i = 0; i < countMantiss - 1; i++, countMassT++)
    massT[countMassT] = massMantiss[i];
  s21_strcpy(parser->mass, massT);
}

void flag_e_converter(long double adress, ParserString *parser) {
  if (adress != fabsl(adress)) adress = fabsl(adress);
  int countMassT = 0, countMantiss = 0;
  long double number = adress;
  char massMantiss[SIZE] = {'\0'}, massT[SIZE] = {'\0'};
  if (log10(number) > 0) {
    for (int r = (int)log10(number) + 1, i = 0; i < r; countMassT++, i++) {
      massT[countMassT] = (fmodl(number, 10)) + 48;
      number /= 10;
    }
  } else {
    massT[countMassT] = '0';
    countMassT++;
  }
  ReverseChar(massT);
  massT[countMassT] = '.';
  int point = countMassT, pointMinus = 0, pointPlus = 0;
  countMassT++;
  number = adress;
  number = fmodl(number, 1);
  if (parser->fractionalMinNum == 0 && parser->fractionalZero == 0)
    parser->fractionalMinNum = 6;
  if (point != 1) {
    for (int i = point; i > 1; i--, countMantiss++) {
      char bykva = massT[i - 1];
      massT[i - 1] = '.';
      massT[i] = '\0';
      countMassT--;
      pointPlus++;
      for (int j = countMantiss; j > 0; j--) {
        massMantiss[j] = massMantiss[j - 1];
      }
      massMantiss[0] = bykva;
    }
  }
  int minCopy = -1, foundNumber = 0;
  if (parser->fractionalMinNum > -1) minCopy = parser->fractionalMinNum;
  for (; countMantiss < minCopy + 2; countMantiss++) {
    if (adress == 0 && countMantiss > parser->fractionalMinNum) break;
    number = number * 10;
    massMantiss[countMantiss] = (floorl(number)) + 48;
    if (massT[0] == '0' && massMantiss[countMantiss] == '0' &&
        foundNumber == 0) {
      minCopy++;
      pointMinus++;
    } else {
      foundNumber = 1;
    }
    number = fmodl(number, 1);
  }
  if (point == 1 && massT[0] == '0') {
    pointPlus--;
    massT[0] = massMantiss[pointMinus];
    for (int i = 0; i < countMantiss - pointMinus; i++)
      massMantiss[i] = massMantiss[i + pointMinus + 1];
  }
  if (parser->fractionalMinNum < 0) parser->fractionalMinNum = 0;
  if (parser->fractionalMinNum == 0 && massMantiss[0] >= '5')
    massT[0] = massT[0] + 1;
  int znakUp = 0;
  if (massMantiss[parser->fractionalMinNum] >= '5') {
    znakUp = 1;
    for (int i = parser->fractionalMinNum - 1; i >= 0; i--) {
      if (znakUp > 0) {
        if (massMantiss[i] + 1 == 58 && i == 0) massT[0]++;
        if (massMantiss[i] + 1 == 58) {
          massMantiss[i] = '0';
        } else {
          massMantiss[i] = massMantiss[i] + 1;
          znakUp = 0;
        }
      }
    }
  }
  if (massT[0] == '9' + 1) {
    massT[0] = '1';
    pointPlus++;
  }
  massMantiss[parser->fractionalMinNum] = parser->specifier;
  countMantiss = parser->fractionalMinNum + 2;
  if (pointMinus >= 0 && pointPlus <= 0) {
    massMantiss[parser->fractionalMinNum + 1] = '-';
    pointMinus++;
    if (pointMinus < 10) {
      massMantiss[countMantiss] = '0';
      massMantiss[countMantiss + 1] = pointMinus + 48;
      countMantiss += 2;
    } else {
      char massExp[SIZE] = {'\0'};
      int count = 0;
      for (int i = pointMinus; 1; i = (i - i % 10) / 10, count++) {
        if (i == 0) break;
        massExp[count] = i % 10 + 48;
      }
      for (; count > 0; count--, countMantiss++)
        massMantiss[countMantiss] = massExp[count - 1];
    }
  } else {
    if (massT[0] == '9' + 1) {
      massT[0] = '1';
      pointPlus++;
    }
    massMantiss[parser->fractionalMinNum + 1] = '+';
    if (pointPlus < 10) {
      massMantiss[countMantiss] = '0';
      massMantiss[countMantiss + 1] = pointPlus + 48;
      countMantiss += 2;
    } else {
      char massExp[SIZE] = {'\0'};
      int count = 0;
      for (int i = pointPlus; 1; i = (i - i % 10) / 10, count++) {
        if (i == 0) break;
        massExp[count] = i % 10 + 48;
      }
      for (; count > 0; count--, countMantiss++)
        massMantiss[countMantiss] = massExp[count - 1];
    }
  }
  massMantiss[countMantiss] = '\0';
  if (parser->fractionalMinNum == 0 && parser->grill == 0) {
    massT[countMassT] = '\0';
    countMassT--;
  }
  for (int i = 0; massMantiss[i] != '\0'; i++, countMassT++)
    massT[countMassT] = massMantiss[i];
  if (adress == 0) {
    massT[0] = '0';
    massT[countMassT - 1] = '0';
    massT[countMassT - 2] = '0';
    massT[countMassT - 3] = '+';
  }
  s21_strcpy(parser->mass, massT);
}

void round_e(ParserString *parser) {
  int startPoint = 0;
  char copyMass[SIZE] = {'\0'};
  s21_strcpy(copyMass, parser->mass);
  for (; copyMass[startPoint] != parser->specifier; startPoint++)
    ;
  if (parser->grill == 0) {
    int cutMass = startPoint - 1;
    for (; cutMass > 0; cutMass--) {
      if (copyMass[cutMass] == '0') {
        copyMass[cutMass] = '\0';
      } else {
        if (copyMass[cutMass] != '.') break;
      }
      if (copyMass[cutMass] == '.') {
        copyMass[cutMass] = '\0';
        cutMass--;
        break;
      }
    }
    if (cutMass + 1 != startPoint) {
      for (; copyMass[startPoint] != '\0'; startPoint++, cutMass++)
        copyMass[cutMass + 1] = copyMass[startPoint];
      copyMass[cutMass + 1] = '\0';
    }
    s21_strcpy(parser->mass, copyMass);
  }
}

void post_converter(int znak, ParserString *parser, char *copyMass) {
  int end = 0;
  int i = 0;
  if (znak != 0 || parser->plus == 1) {
    end = s21_strlen(copyMass) + 1;
  } else {
    end = s21_strlen(copyMass);
  }
  if (parser->minNum > 0 && parser->minus == 0 && parser->zero == 0) {
    for (int j = 0; j < (parser->minNum - end); j++) {
      parser->mass[i] = ' ';
      i++;
    }
  }
  if (parser->plus == 1 && znak == 0) {
    parser->mass[i] = '+';
    i++;
  }
  if (znak != 0) {
    parser->mass[i] = '-';
    i++;
  }
  if (parser->mass[0] != ' ' && parser->plus == 0 && znak == 0 &&
      parser->space > 0) {
    parser->mass[i] = ' ';
    i++;
    end++;
  }
  if (parser->zero == 1 && parser->minus == 0) {
    for (int j = 0; j < (parser->minNum - end); j++) {
      parser->mass[i] = '0';
      i++;
    }
  }
  for (size_t count = 0; count < s21_strlen(copyMass); count++) {
    parser->mass[i] = copyMass[count];
    i++;
  }
  if (parser->minNum > 0 && parser->minus == 1) {
    for (int j = 0; j < (parser->minNum - end); j++) {
      parser->mass[i] = ' ';
      i++;
    }
  }
  parser->mass[i] = '\0';
}
