#include "s21_smartcalc.h"

void push_n(stack_n **head, double number) {
  stack_n *tmp = (stack_n *)malloc(sizeof(stack_n));
  if (tmp == NULL) {
    exit(STACK_OVERFLOW);
  }
  tmp->next = *head;
  tmp->number = number;
  *head = tmp;
}

void push_o(stack_o **head, char current_o) {
  stack_o *tmp = (stack_o *)malloc(sizeof(stack_o));
  if (tmp == NULL) {
    exit(STACK_OVERFLOW);
  }
  tmp->next = *head;
  tmp->operation = current_o;
  *head = tmp;
}

double pop_n(stack_n **head) {
  stack_n *tmp;
  double value = 0.0;
  if (*head == NULL) {
    exit(STACK_UNDERFLOW);
  }
  tmp = *head;
  *head = (*head)->next;
  value = tmp->number;
  free(tmp);
  return value;
}

char pop_o(stack_o **head) {
  stack_o *tmp;
  char value = '\0';
  if (*head == NULL) {
    return value;
  }
  tmp = *head;
  *head = (*head)->next;
  value = tmp->operation;
  free(tmp);
  return value;
}

char peek_o(const stack_o *head) {
  if (head == NULL) {
    return '\0';
  }
  return head->operation;
}

double peek_n(const stack_n *head) {
  if (head == NULL) {
    exit(STACK_UNDERFLOW);
  }
  return head->number;
}