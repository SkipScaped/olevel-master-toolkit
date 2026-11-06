#include "toolkit.h"

#include <math.h>
#include <stdio.h>

static void denary_to_binary(void)
{
    static const char * const labels[] = {"Denary integer (0-65535)"};
    double input[1];
    unsigned int value;
    char bits[17];
    char output[160];
    int position = 16;

    if (!toolkit_input_numbers("Denary to binary", labels, input, 1))
        return;
    if (input[0] < 0.0 || input[0] > 65535.0 || input[0] != trunc(input[0])) {
        toolkit_message("Invalid input", "Enter a whole number from 0 to 65535.");
        return;
    }
    value = (unsigned int)input[0];
    bits[position] = '\0';
    do {
        bits[--position] = (char)('0' + (value & 1U));
        value >>= 1;
    } while (value != 0U);
    snprintf(output, sizeof(output), "Repeated division by 2 gives\nDenary = %.0f\nBinary = %s",
             input[0], bits + position);
    toolkit_message("Base conversion", output);
}

static void evaluate_logic(void)
{
    static const char * const options[] = {"AND", "OR", "XOR", "NAND", "NOR", "NOT", "Back"};
    static const char * const unary_label[] = {"Input A (0 or 1)"};
    static const char * const binary_labels[] = {"Input A (0 or 1)", "Input B (0 or 1)"};
    int selected = toolkit_choose("Logic gate", options, 7);
    double values[2];
    int result;
    char output[120];

    if (selected < 0 || selected == 6)
        return;
    if (!toolkit_input_numbers("Gate inputs", selected == 5 ? unary_label : binary_labels,
                               values, selected == 5 ? 1U : 2U))
        return;
    if ((values[0] != 0.0 && values[0] != 1.0) ||
        (selected != 5 && values[1] != 0.0 && values[1] != 1.0)) {
        toolkit_message("Invalid input", "Logic inputs must be 0 or 1.");
        return;
    }
    switch (selected) {
    case 0: result = values[0] == 1.0 && values[1] == 1.0; break;
    case 1: result = values[0] == 1.0 || values[1] == 1.0; break;
    case 2: result = (values[0] == 1.0) != (values[1] == 1.0); break;
    case 3: result = !(values[0] == 1.0 && values[1] == 1.0); break;
    case 4: result = !(values[0] == 1.0 || values[1] == 1.0); break;
    default: result = values[0] == 0.0; break;
    }
    snprintf(output, sizeof(output), "%s gate\nOutput = %d", options[selected], result);
    toolkit_message("Logic result", output);
}

void cs_tools_menu(void)
{
    static const char * const options[] = {"Denary to binary", "Logic gates", "Back"};

    for (;;) {
        switch (toolkit_choose("Computer Science", options, 3)) {
        case 0: denary_to_binary(); break;
        case 1: evaluate_logic(); break;
        default: return;
        }
    }
}

void formula_library(void)
{
    static const char * const options[] = {
        "Quadratic formula", "Pythagoras", "Circle area", "Speed",
        "Mean", "Binary place values", "Back"
    };
    static const char * const formulas[] = {
        "Quadratic formula\nx = (-b +/- sqrt(b^2-4ac))/(2a)\nUse for ax^2+bx+c=0.",
        "Pythagoras\na^2+b^2=c^2\nUse in a right-angled triangle.",
        "Circle area\nA = pi*r^2\nr is the radius.",
        "Speed\nspeed = distance/time\nUse consistent units.",
        "Arithmetic mean\nmean = sum of values / count\nFor an ungrouped data set.",
        "Binary place values\n... 16, 8, 4, 2, 1\nAdd the place values with a 1."
    };

    for (;;) {
        int selected = toolkit_choose("Formula library", options, 7);
        if (selected < 0 || selected == 6)
            return;
        toolkit_message("Formula reference", formulas[selected]);
    }
}

static unsigned int practice_score;

void clear_practice_score(void)
{
    practice_score = 0;
}

void exam_practice(void)
{
    static const char * const labels[] = {"Your answer"};
    double answer[1];
    char output[150];

    if (!toolkit_input_numbers("Easy: quadratic roots", labels, answer, 1))
        return;
    if (answer[0] == 2.0 || answer[0] == 3.0) {
        ++practice_score;
        snprintf(output, sizeof(output), "Correct. x^2-5x+6=(x-2)(x-3).\nSession score: %u",
                 practice_score);
    } else {
        snprintf(output, sizeof(output), "Not quite. (x-2)(x-3)=0, so x=2 or x=3.\nSession score: %u",
                 practice_score);
    }
    toolkit_message("Practice: x^2 - 5x + 6 = 0", output);
}

void settings_menu(void)
{
    static const char * const options[] = {"Angle units (degrees)", "Clear practice score", "Back"};
    int selected = toolkit_choose("Settings", options, 3);

    if (selected == 0) {
        toolkit_message("Angle units", "Default mode: degrees. Radian selection is not included in this release.");
    } else if (selected == 1) {
        clear_practice_score();
        toolkit_message("Session statistics", "Practice score cleared.");
    }
}