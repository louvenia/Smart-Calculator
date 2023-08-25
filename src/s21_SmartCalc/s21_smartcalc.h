#ifndef SRC_SOURCE_CALC_H_
#define SRC_SOURCE_CALC_H_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY -102

typedef struct Stack_1 {
  double number;
  struct Stack_1 *next;
} stack_n;

typedef struct Stack_2 {
  char operation;
  struct Stack_2 *next;
} stack_o;

typedef struct operations {
  char *left_bracket;
  char *right_bracket;
  char *addition;
  char *subtraction;
  char *multiplication;
  char *division;
  char *power;
  char *modulus;
  char *unary_plus;
  char *unary_minus;
  char *cosine;
  char *sine;
  char *tangent;
  char *arccosine;
  char *arcsine;
  char *arctangent;
  char *square_root;
  char *natural_logarithm;
  char *decimal_logarithm;
} math;

double calculation(char *input_string, char *string_with_x);
void add_x(char *calc_string, double add_x_string);

double calc_string(char *calc_string, int *status_string);
void calculation_current_operation(stack_n **head_n, stack_o **head_o);

double calculation_value_s(double value_s, stack_o **head_o);
int priority_calculation(char operation);
int check_math_o(char symbol);
void push_o(stack_o **head, char current_o);
void push_n(stack_n **head, double number);

char pop_o(stack_o **head);
double pop_n(stack_n **head);

double peek_n(const stack_n *head);
char peek_o(const stack_o *head);

int get_n(char *part_s, int *position_in_string, double *value);
int get_o(char *part_s, int *position_in_string, char *operation);

char strchr_n(char *string_p, char operation);
int strchr_o(char current_o, char *operation);

double operation_with_minus(char *curent_string, int *position_in_string);
double operation_with_div(char *curent_string, int *position_in_string);

int check_unary_minus(char *curent_string, int position_in_string);

int priority_next_operation(char *part_s, int position_in_string);
double operation_with_power(char *curent_string, int *position_in_string,
                            double current_n);
double result_op_minus(char *calc_string, int *position_in_string,
                       stack_n **head_n, stack_o **head_o);
double result_op_div(char *calc_string, int *position_in_string,
                     stack_n **head_n, stack_o **head_o);
double operation_with_left_bracket(char *curent_string,
                                   int *position_in_string);
int check_lower_priority(char previous_o, char current_o, char *calc_string);

int number_after_op(char *symbol);

// _______________________________________________________________________________

int check_wrong_string(char *input_string, char *input_x_string);
int checking(char *string, int *status_wrong);
int check_brackets(char *string);
int check_empty_brackets(char *string);
int two_operators(char *string);
int check_around(char *math);
int check_binary(char string);
int check_open_o(char string);
int false_binary(char *string);
int three_operators(char *string);
int binary_after_op(char *string);
int check_dot(char *string);
int check_n(char symbol);
int count_arg(char *string);
void change_string(char *input_string);
int input_x_string(char *string);
int fun_expression(char symbol);
int conversion_string(char *string);
int check_n_o(char symbol);

// _______________________________________________________________________________

void annu_credit_calc(double *result, double credit, double interest_rate,
                      double period);
void diff_credit_calc(double *result, double credit, double interest_rate,
                      double period);

// _______________________________________________________________________________

void depozit_calc(double *result, double *depozit, int period,
                  double interest_rate, double tax, double replenishment,
                  double withdrawal, double *count_replenishment,
                  double *count_withdrawal, double *minimum_balance,
                  int type_period, int type_dep_calc);
void calculation_depozit(int period_type, double *interest_charges,
                         double *tax_amount, double *depozit,
                         double interest_rate, double tax, double replenishment,
                         double withdrawal, double *count_replenishment,
                         double *count_withdrawal, double *minimum_balance,
                         int type_dep_calc, double upper_value,
                         double lower_value, int tax_period);
void calc_tax_amount(double *interest_charges, double tax, double *tax_amount,
                     int tax_period, int *status_tax);
void replenishment_op(double *depozit, double replenishment,
                      double *count_replenishment, int int_period);
void withdrawal_op(double *depozit, double withdrawal, double *count_withdrawal,
                   int int_period, double *minimum_balance);

#endif // SRC_SOURCE_CALC_H_
