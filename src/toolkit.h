#ifndef TOOLKIT_H
#define TOOLKIT_H

#include <stddef.h>

int toolkit_choose(const char *title, const char * const options[], int count);
void toolkit_message(const char *title, const char *message);
int toolkit_input_numbers(const char *title, const char * const labels[],
                          double values[], size_t count);
void math_tools_menu(void);
void cs_tools_menu(void);
void formula_library(void);
void exam_practice(void);
void settings_menu(void);
void clear_practice_score(void);

#endif