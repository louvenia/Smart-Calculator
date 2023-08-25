#include "s21_smartcalc.h"

double calculation(char *input_string, char *string_with_x) {
  char buf[256] = {'\0'};
  strncpy(buf, input_string, 256);
  int status_calculation = 0;
  double result = 0.0, x_result = 0.0;
  x_result = calc_string(string_with_x, &status_calculation);
  add_x(input_string, x_result);
  result = calc_string(input_string, &status_calculation);
  char the_end = '\0';
  memset(input_string, the_end, 256);
  strncpy(input_string, buf, 256);
  return result;
}

int check_wrong_string(char *input_string, char *input_string_with_x) {
  int status_wrong = 0;
  checking(input_string, &status_wrong);
  checking(input_string_with_x, &status_wrong);
  if (status_wrong == 0) {
    status_wrong = input_x_string(input_string_with_x);
  }
  return !status_wrong;
}

int checking(char *string, int *status_wrong) {
  if (*status_wrong == 0) {
    *status_wrong = conversion_string(string);
  }
  if (*status_wrong == 0) {
    change_string(string);
    *status_wrong = check_brackets(string);
  }
  if (*status_wrong == 0) {
    *status_wrong = two_operators(string);
  }
  if (*status_wrong == 0) {
    *status_wrong = check_dot(string);
  }
  if (*status_wrong == 0) {
    *status_wrong = count_arg(string);
  }
  return *status_wrong;
}

int conversion_string(char *string) {
  int conversion_status = 0, flag = 0;
  char new_string[256] = {'\0'};
  size_t length_string = strlen(string);
  for (size_t i = 0, j = 0; i < length_string && flag != 2; i++, j++) {
    flag = 0;
    if (check_n_o(string[i]) && flag != 1) {
      new_string[j] = string[i];
    } else if (string[i] == 'l' && string[i + 1] == 'n' && flag != 1) {
      new_string[j] = 'l';
      i += 1;
    } else if (string[i] == 'l' && string[i + 1] == 'g' && flag != 1) {
      new_string[j] = 'L';
      i += 1;
    } else if (string[i] == 'c' && string[i + 1] == 'o' &&
               string[i + 2] == 's' && flag != 1) {
      new_string[j] = 'c';
      i += 2;
    } else if (string[i] == 's' && string[i + 1] == 'i' &&
               string[i + 2] == 'n' && flag != 1) {
      new_string[j] = 's';
      i += 2;
    } else if (string[i] == 't' && string[i + 1] == 'a' &&
               string[i + 2] == 'n' && flag != 1) {
      new_string[j] = 't';
      i += 2;
    } else if (string[i] == 'm' && string[i + 1] == 'o' &&
               string[i + 2] == 'd' && flag != 1) {
      new_string[j] = '%';
      i += 2;
    } else if (string[i] == 'a' && string[i + 1] == 'c' &&
               string[i + 2] == 'o' && string[i + 3] == 's' && flag != 1) {
      new_string[j] = 'C';
      i += 3;
    } else if (string[i] == 'a' && string[i + 1] == 's' &&
               string[i + 2] == 'i' && string[i + 3] == 'n' && flag != 1) {
      new_string[j] = 'S';
      i += 3;
    } else if (string[i] == 'a' && string[i + 1] == 't' &&
               string[i + 2] == 'a' && string[i + 3] == 'n' && flag != 1) {
      new_string[j] = 'T';
      i += 3;
    } else if (string[i] == 's' && string[i + 1] == 'q' &&
               string[i + 2] == 'r' && string[i + 3] == 't' && flag != 1) {
      new_string[j] = 'q';
      i += 3;
    } else if (string[i] == ' ' && flag != 1) {
      j--;
      flag = 1;
    } else if (flag != 1) {
      conversion_status = 1;
      flag = 2;
    }
  }
  char the_end = '\0';
  memset(string, the_end, length_string);
  strcpy(string, new_string);
  return conversion_status;
}

void change_string(char *input_string) {
  char new_string[256] = {'\0'};
  size_t length_string = strlen(input_string);
  for (size_t i = 0, j = 0; i < length_string; i++) {
    if (&input_string[i + 1] != NULL) {
      if ((check_n(input_string[i]) || input_string[i] == '.' ||
           input_string[i] == 'x') &&
          fun_expression(input_string[i + 1])) {
        new_string[j] = input_string[i];
        new_string[j + 1] = '*';
        new_string[j + 2] = input_string[i + 1];
        j += 2;
        i += 1;
      } else if (input_string[i] == '-' && input_string[i + 1] == '-') {
        new_string[j] = '+';
        i += 1;
      } else {
        new_string[j] = input_string[i];
      }
      j++;
    }
  }
  char the_end = '\0';
  memset(input_string, the_end, length_string);
  strcpy(input_string, new_string);
}

int check_n_o(char symbol) {
  int status = 0;
  if (check_n(symbol) || symbol == '.' || symbol == '+' || symbol == '-' ||
      symbol == '*' || symbol == '/' || symbol == '(' || symbol == ')' ||
      symbol == 'x' || symbol == '^') {
    status = 1;
  }
  return status;
}

int check_n(char symbol) {
  int status = 0;
  if (symbol == '0' || symbol == '1' || symbol == '2' || symbol == '3' ||
      symbol == '4' || symbol == '5' || symbol == '6' || symbol == '7' ||
      symbol == '8' || symbol == '9') {
    status = 1;
  }
  return status;
}

int fun_expression(char symbol) {
  int status = 0;
  if (priority_calculation(symbol) || symbol == '(' || symbol == 'x') {
    status = 1;
  }
  return status;
}

int priority_calculation(char operation) {
  int status = 0;
  if (operation == 'c' || operation == 'C' || operation == 's' ||
      operation == 'S' || operation == 't' || operation == 'T' ||
      operation == 'l' || operation == 'L' || operation == 'q') {
    status = 1;
  }
  return status;
}

int check_brackets(char *string) {
  int bracket_count = 0, flag = 0;
  size_t length_string = strlen(string), i = 0;
  while (length_string > i && flag == 0) {
    if (string[i] == '(') {
      bracket_count += 1;
      if (check_empty_brackets(&string[i + 1]) && flag == 0) {
        bracket_count = 10;
        flag = 1;
      }
    } else if (string[i] == ')') {
      bracket_count -= 1;
    }
    if (bracket_count < 0 && flag == 0) {
      flag = 1;
    }
    i++;
  }
  return !!bracket_count;
}

int check_empty_brackets(char *string) {
  int status = 0, number_status = 0, flag = 0;
  if (string == NULL) {
    status = 1;
  } else {
    int length_string = strlen(string);
    int i = 0;
    while (i < length_string && flag == 0) {
      if (&string[i] == NULL && flag == 0) {
        status = 1;
        flag = 1;
      }
      if (string[i] == ')' && number_status != 1 && flag == 0) {
        status = 1;
        flag = 1;
      }
      if (check_n(string[i]) || string[i] == 'x') {
        number_status = 1;
      }
      i++;
    }
  }
  return status;
}

int two_operators(char *string) {
  int status_binary = 0;
  size_t length_string = strlen(string);
  if (check_binary(*string) && *string != '-') {
    status_binary = 1;
  }
  if (length_string > 0) {
    if (check_binary(string[length_string - 1])) {
      status_binary = 1;
    }
  }
  if (three_operators(string)) {
    status_binary = 1;
  }
  for (size_t i = 0; length_string > i && status_binary != 1; i++) {
    if (&string[i + 1] != NULL) {
      if (check_open_o(string[i]) && check_binary(string[i + 1]) &&
          string[i + 1] != '-') {
        status_binary = 1;
      }
    }
    if (&string[i - 1] != NULL) {
      if (string[i] == ')' && check_binary(string[i - 1])) {
        status_binary = 1;
      }
    }
    if (i != length_string - 1) {
      if (false_binary(&string[i])) {
        status_binary = 1;
      }
      if (number_after_op(&string[i])) {
        status_binary = 1;
      }
      if (binary_after_op(&string[i])) {
        status_binary = 1;
      }
      if (i != 0) {
        if (check_around(&string[i]))
          status_binary = 1;
      }
    }
  }
  return !!status_binary;
}

int check_binary(char string) {
  int status_binary = 0;
  if (string == '+' || string == '-' || string == '*' || string == '/' ||
      string == '%' || string == '^') {
    status_binary = 1;
  }
  return status_binary;
}

int three_operators(char *string) {
  int status_triple = 0, operators_counter = 0;
  size_t length_string = strlen(string);
  for (size_t i = 0; length_string > i && status_triple != 1; i++) {
    if (check_binary(string[i])) {
      operators_counter += 1;
    } else {
      operators_counter = 0;
    }
    if (operators_counter == 3) {
      status_triple = 1;
    }
  }
  return status_triple;
}

int check_open_o(char string) {
  int status_open = 0;
  if (check_math_o(string) || string == '(') {
    status_open = 1;
  }
  return status_open;
}

int false_binary(char *string) {
  int status_in_binary = 0;
  if ((string + 1) != NULL) {
    if (*(string + 1) == '-') {
      status_in_binary = 0;
    } else if (check_binary(*string) && check_binary(*(string + 1))) {
      status_in_binary = 1;
    }
  }
  return status_in_binary;
}

int binary_after_op(char *string) {
  int status = 0;
  if ((string + 1) != NULL) {
    if (check_open_o(*string) && check_binary(*(string + 1)) &&
        *(string + 1) != '-')
      status = 1;
  }
  return status;
}

int number_after_op(char *symbol) {
  int status = 0;
  if (symbol + 1 != NULL) {
    if (check_math_o(*symbol) &&
        (!check_n(*(symbol + 1)) && *(symbol + 1) != '-' &&
         *(symbol + 1) != 'x' && *(symbol + 1) != '(' &&
         check_math_o(*(symbol + 1)) != 1))
      status = 1;
  }
  return status;
}

int check_around(char *math) {
  int status_neighbor = 0;
  char aft_symbol = '\0';
  if (check_open_o(*math) && *math != '^' && *math != '(') {
    if ((math - 1) != NULL) {
      aft_symbol = *(math - 1);
      status_neighbor = check_n(aft_symbol);
      if (aft_symbol == ')')
        status_neighbor = 1;
    }
  }
  return status_neighbor;
}

int check_dot(char *string) {
  int status = 0, flag_dot = 0, dot = 0;
  ;
  size_t length_string = strlen(string);
  for (size_t i = 0; i < length_string && status != 1; i++) {
    if (flag_dot == 1 && dot == 1 && string[i] == '.') {
      status = 1;
    }
    if (check_n(string[i])) {
      flag_dot = 1;
    }
    if (string[i] == '.' && flag_dot == 1) {
      dot += 1;
    }
    if (string[i] == '.' && flag_dot != 1) {
      status = 1;
    }
    if (dot > 1) {
      status = 1;
    }
    if (check_n(string[i]) != 1 && string[i] != '.') {
      flag_dot = 0;
      dot = 0;
    }
  }
  return status;
}

int count_arg(char *string) {
  int status = 0, flag = 0;
  int length_string = strlen(string);
  int find_number = 0, find_func = 0;
  for (int i = 0; i < length_string && flag == 0; i++) {
    if (string[i] == '^' && find_number == 0 && flag == 0) {
      status = 1;
      flag = 1;
    }
    if ((check_n(string[i]) || string[i] == 'x') && flag == 0) {
      find_number = 1;
      find_func = 0;
    }
    if (check_math_o(string[i]) && flag == 0) {
      find_func = 1;
    }
  }
  if (find_func == 1)
    status = 1;
  return status;
}

int check_math_o(char symbol) {
  int status = 0;
  if (priority_calculation(symbol) || symbol == '^') {
    status = 1;
  }
  return status;
}

int input_x_string(char *string) {
  int status = 0, flag = 0;
  size_t length_string = strlen(string);
  for (size_t i = 0; i < length_string && flag == 0; i++) {
    if (string[i] == 'x') {
      status = 1;
      flag = 1;
    }
  }
  return status;
}

void add_x(char *calc_string, double add_x_string) {
  char new_string[256] = {'\0'};
  char string_with_x[100] = {'\0'};
  size_t string_len = strlen(calc_string);
  snprintf(string_with_x, 100, "%F", add_x_string);
  size_t x_len = strlen(string_with_x);
  for (size_t i = 0, j = 0; i < string_len; i++, j++) {
    if (calc_string[i] != 'x') {
      new_string[j] = calc_string[i];
    } else {
      strcpy(&new_string[j], string_with_x);
      j += x_len - 1;
    }
  }
  char the_end = '\0';
  memset(calc_string, the_end, 256);
  strcpy(calc_string, new_string);
}
