#include "s21_smartcalc.h"

double calc_string(char *calc_string, int *status_string) {
  stack_n *head_n = NULL;
  stack_o *head_o = NULL;
  double current_n = 0.0;
  char current_o = '\0', previous_o = '\0';
  int position_in_string = 0, flag = 0;
  int length_string = strlen(calc_string);
  while (position_in_string < length_string && flag != 2) {
    flag = 0;
    if (get_n(calc_string, &position_in_string, &current_n) && flag == 0) {
      push_n(&head_n, current_n);
      if (*status_string == 4 &&
          priority_next_operation(calc_string, position_in_string) &&
          flag == 0) {
        flag = 1;
      } else if (*status_string == 4 &&
                 !priority_next_operation(calc_string, position_in_string) &&
                 flag == 0) {
        flag = 2;
      }
      if (*status_string == 8 &&
          priority_next_operation(calc_string, position_in_string) &&
          flag == 0) {
        flag = 1;
      } else if (*status_string == 8 &&
                 !priority_next_operation(calc_string, position_in_string) &&
                 flag == 0) {
        flag = 2;
      }
      if (*status_string == 2 && priority_calculation(current_o) && flag == 0) {
        calculation_current_operation(&head_n, &head_o);
        flag = 2;
      }
    } else if (get_o(calc_string, &position_in_string, &current_o) &&
               flag == 0) {
      previous_o = peek_o(head_o);
      push_o(&head_o, current_o);
      if (current_o == '(' && flag == 0) {
        current_n =
            operation_with_left_bracket(calc_string, &position_in_string);
        pop_o(&head_o);
        current_o = peek_o(head_o);
        push_n(&head_n, current_n);
        if (*status_string == 8 &&
            priority_next_operation(calc_string, position_in_string) &&
            flag == 0) {
          flag = 1;
        } else if (*status_string == 8 &&
                   !priority_next_operation(calc_string, position_in_string) &&
                   flag == 0) {
          flag = 2;
        }
        if (*status_string == 4 &&
            priority_next_operation(calc_string, position_in_string) &&
            flag == 0) {
          flag = 1;
        } else if (*status_string == 4 &&
                   !priority_next_operation(calc_string, position_in_string) &&
                   flag == 0) {
          flag = 2;
        }
      }
      if (current_o == '^' && flag == 0) {
        current_n = operation_with_power(calc_string, &position_in_string,
                                         peek_n(head_n));
        if (*status_string == 8 || *status_string == 4) {
          pop_n(&head_n);
          pop_o(&head_o);
          push_n(&head_n, current_n);
          flag = 2;
        } else {
          pop_n(&head_n);
          pop_o(&head_o);
          push_n(&head_n, current_n);
        }
      }
      if (position_in_string != 1 && flag == 0) {
        if (check_lower_priority(previous_o, current_o,
                                 &calc_string[position_in_string - 1])) {
          current_o = pop_o(&head_o);
          calculation_current_operation(&head_n, &head_o);
          push_o(&head_o, current_o);
        }
      }
      if (peek_o(head_o) == '-' && flag == 0) {
        current_n =
            result_op_minus(calc_string, &position_in_string, &head_n, &head_o);
      }
      if (peek_o(head_o) == '/' && flag == 0) {
        current_n =
            result_op_div(calc_string, &position_in_string, &head_n, &head_o);
      }
    }
    if (((int)strlen(calc_string) == position_in_string || current_o == ')') &&
        flag == 0) {
      calculation_current_operation(&head_n, &head_o);
      if ((current_o == ')') && (*status_string != 0)) {
        flag = 2;
      }
    }
  }
  if (peek_o(head_o) != '\0' && *status_string == 0) {
    calculation_current_operation(&head_n, &head_o);
  }
  if (*status_string != 0) {
    *status_string = position_in_string;
  }
  if (*calc_string != '\0') {
    current_n = pop_n(&head_n);
  }
  return current_n;
}

int get_n(char *part_s, int *position_in_string, double *value) {
  int status_get = 0;
  char string_number[12] = "0123456789.";
  *value = atof(&part_s[*position_in_string]);
  while (strchr_n(string_number, part_s[*position_in_string]) != '\0') {
    *position_in_string += 1;
    status_get = 1;
  }
  return status_get;
}

int get_o(char *part_s, int *position_in_string, char *operation) {
  int status_get = 0;
  const char string_operations[60] = "(|)|+|-|*|/|^|%|U|u|c|s|t|C|S|T|q|l|L";
  *operation = *strchr(string_operations, part_s[*position_in_string]);
  if (operation != NULL) {
    status_get = 1;
    *position_in_string += 1;
  }
  return status_get;
}

char strchr_n(char *string_p, char operation) {
  int i = 0;
  for (; i < 11; i++) {
    if (string_p[i] == operation) {
      return string_p[i];
    }
  }
  return '\0';
}

int strchr_o(char current_o, char *operation) {
  int status = 0;
  if (current_o == operation[0])
    status = 1;
  return status;
}

double operation_with_power(char *current_string, int *position_in_string,
                            double current_n) {
  double result = 0.0;
  int flag_position = 8;
  result = calc_string(&current_string[*position_in_string], &flag_position);
  result = pow(current_n, result);
  *position_in_string += flag_position;
  return result;
}

double operation_with_left_bracket(char *current_string,
                                   int *position_in_string) {
  double result_bracket = 0.0;
  int flag_position = 9;
  result_bracket =
      calc_string(&current_string[*position_in_string], &flag_position);
  *position_in_string += flag_position;
  return result_bracket;
}

double result_op_div(char *calc_string, int *position_in_string,
                     stack_n **head_n, stack_o **head_o) {
  double current_n = 0.0;
  current_n = operation_with_div(calc_string, position_in_string);
  push_n(head_n, current_n);
  pop_o(head_o);
  char current_o = '*';
  push_o(head_o, current_o);
  return current_n;
}

double operation_with_div(char *current_string, int *position_in_string) {
  double result = 0.0;
  int flag_position = 4;
  result = calc_string(&current_string[*position_in_string], &flag_position);
  result = 1.0 / result;
  *position_in_string += flag_position;
  return result;
}

double result_op_minus(char *calc_string, int *position_in_string,
                       stack_n **head_n, stack_o **head_o) {
  double current_n = 0.0;
  if (check_unary_minus(calc_string - 1, *position_in_string)) {
    current_n = operation_with_minus(calc_string, position_in_string);
    push_n(head_n, current_n);
    pop_o(head_o);
  } else {
    current_n = operation_with_minus(calc_string, position_in_string);
    pop_o(head_o);
    push_n(head_n, current_n);
    char current_o = '+';
    push_o(head_o, current_o);
  }
  return current_n;
}

int check_unary_minus(char *current_string, int position_in_string) {
  int status_unary = 0;
  if (position_in_string == 1) {
    status_unary = 1;
  } else if (current_string[position_in_string - 1] == 'c' ||
             current_string[position_in_string - 1] == 'C' ||
             current_string[position_in_string - 1] == 's' ||
             current_string[position_in_string - 1] == 'S' ||
             current_string[position_in_string - 1] == 't' ||
             current_string[position_in_string - 1] == 'T' ||
             current_string[position_in_string - 1] == 'q' ||
             current_string[position_in_string - 1] == 'l' ||
             current_string[position_in_string - 1] == 'L' ||
             current_string[position_in_string - 1] == '*' ||
             current_string[position_in_string - 1] == '/' ||
             current_string[position_in_string - 1] == '+' ||
             current_string[position_in_string - 1] == '-' ||
             current_string[position_in_string - 1] == '^' ||
             current_string[position_in_string - 1] == '%' ||
             current_string[position_in_string - 1] == '(') {
    status_unary = 1;
  }
  return status_unary;
}

double operation_with_minus(char *current_string, int *position_in_string) {
  double result = 0.0;
  int flag_position = 2;
  while (current_string[*position_in_string] == ' ') {
    *position_in_string += 1;
  }
  if (get_n(current_string, position_in_string, &result)) {
    result *= -1;
  } else {
    result = calc_string(&current_string[*position_in_string], &flag_position);
    result *= -1;
    *position_in_string += flag_position;
  }
  return result;
}

int priority_next_operation(char *part_s, int position_in_string) {
  int status_priority = 0, skip_status = 0, flag = 0;
  for (; status_priority == 0 && &part_s[position_in_string] != NULL;
       position_in_string++) {
    if (part_s[position_in_string] == '^' && flag == 0) {
      status_priority = 1;
    } else if (check_n(part_s[position_in_string]) && flag == 0) {
      flag = 1;
    } else if (part_s[position_in_string] == '(' && flag == 0) {
      skip_status = 1;
    } else if (!check_n(part_s[position_in_string]) && skip_status == 1 &&
               part_s[position_in_string] != ')' && flag == 0) {
      flag = 1;
    } else if (part_s[position_in_string] == ')' && skip_status == 1 &&
               flag == 0) {
      skip_status = 0;
    } else if (part_s[position_in_string] == ')' && skip_status != 1 &&
               flag == 0) {
      status_priority = 3;
    } else {
      status_priority = 3;
    }
  }
  if (status_priority == 3)
    status_priority = 0;
  return status_priority;
}

int check_lower_priority(char previous_o, char current_o, char *calc_string) {
  int status_l_priority = 0;
  if (calc_string != NULL) {
    if (((previous_o == '*' || previous_o == '/' || previous_o == '^') &&
         (current_o == '-' || current_o == '+')) ||
        (check_math_o(previous_o) && current_o != '(' && current_o != '-' &&
         !check_math_o(current_o))) {
      status_l_priority = 1;
    }
    if ((calc_string - 1) != NULL && calc_string != NULL) {
      if (*calc_string == '-' &&
          (*(calc_string - 1) == '*' || *(calc_string - 1) == '/' ||
           *(calc_string - 1) == '%' || *(calc_string - 1) == '^'))
        status_l_priority = 0;
    }
    if ((!priority_calculation(current_o) &&
         priority_calculation(previous_o)) &&
        !priority_calculation(*(calc_string - 1))) {
      status_l_priority = 1;
    }
  }
  return status_l_priority;
}

void calculation_current_operation(stack_n **head_n, stack_o **head_o) {
  double value_f = 0.0, value_s = 0.0;
  int flag = 0;
  value_f = pop_n(head_n);
  char current_o = '\0';
  current_o = pop_o(head_o);
  math operation = {"(", ")", "+", "-", "*", "/", "^", "%", "U", "u",
                    "c", "s", "t", "C", "S", "T", "q", "l", "L"};

  while (current_o != '\0') {
    if (current_o == '(' || current_o == ')') {
      current_o = pop_o(head_o);
      if (current_o == '\0') {
        flag = 1;
      }
    }
    if (flag == 0) {
      if (strchr_o(current_o, operation.addition)) {
        value_s = pop_n(head_n);
        value_s = calculation_value_s(value_s, head_o);
        push_n(head_n, value_f + value_s);
      } else if (strchr_o(current_o, operation.multiplication)) {
        value_s = pop_n(head_n);
        value_s = calculation_value_s(value_s, head_o);
        push_n(head_n, value_f * value_s);
      } else if (strchr_o(current_o, operation.modulus)) {
        value_s = pop_n(head_n);
        value_s = calculation_value_s(value_s, head_o);
        push_n(head_n, fmod(value_s, value_f));
      } else if (strchr_o(current_o, operation.cosine)) {
        push_n(head_n, cos(value_f));
      } else if (strchr_o(current_o, operation.sine)) {
        push_n(head_n, sin(value_f));
      } else if (strchr_o(current_o, operation.tangent)) {
        push_n(head_n, tan(value_f));
      } else if (strchr_o(current_o, operation.arccosine)) {
        push_n(head_n, acos(value_f));
      } else if (strchr_o(current_o, operation.arcsine)) {
        push_n(head_n, asin(value_f));
      } else if (strchr_o(current_o, operation.arctangent)) {
        push_n(head_n, atan(value_f));
      } else if (strchr_o(current_o, operation.square_root)) {
        push_n(head_n, sqrt(value_f));
      } else if (strchr_o(current_o, operation.natural_logarithm)) {
        push_n(head_n, log(value_f));
      } else if (strchr_o(current_o, operation.decimal_logarithm)) {
        push_n(head_n, log10(value_f));
      }
      current_o = pop_o(head_o);
      value_f = pop_n(head_n);
    }
  }
  push_n(head_n, value_f);
}

double calculation_value_s(double value_s, stack_o **head_o) {
  char operation = '\0';
  if (priority_calculation(operation = peek_o(*head_o))) {
    stack_n *head_n = NULL;
    stack_o *head_o = NULL;
    push_o(&head_o, operation);
    push_n(&head_n, value_s);
    calculation_current_operation(&head_n, &head_o);
    value_s = pop_n(&head_n);
    pop_o(&head_o);
  }
  return value_s;
}
