#include "toolkit.h"

#include <math.h>
#include <stdio.h>

static void solve_quadratic(void)
{
    static const char * const labels[] = {"a", "b", "c"};
    double values[3];
    double a, b, c, discriminant;
    char output[220];

    if (!toolkit_input_numbers("Quadratic equation", labels, values, 3))
        return;
    a = values[0];
    b = values[1];
    c = values[2];
    if (a == 0.0) {
        toolkit_message("Invalid equation", "The coefficient a must not be zero.");
        return;
    }
    discriminant = b * b - 4.0 * a * c;
    if (!isfinite(discriminant)) {
        toolkit_message("Input out of range", "The coefficients are too large to calculate safely.");
        return;
    }
    if (discriminant < 0.0) {
        snprintf(output, sizeof(output),
                 "D = b^2 - 4ac = %.8g\nD is negative: there are no real roots.",
                 discriminant);
    } else {
        double root1 = (-b + sqrt(discriminant)) / (2.0 * a);
        double root2 = (-b - sqrt(discriminant)) / (2.0 * a);
        snprintf(output, sizeof(output),
                 "ax^2 + bx + c = 0\nD = b^2 - 4ac = %.8g\n"
                 "x = (-b +/- sqrt(D))/(2a)\nRoots: %.8g, %.8g",
                 discriminant, root1, root2);
    }
    toolkit_message("Quadratic working", output);
}

static void solve_simultaneous(void)
{
    static const char * const coefficient_labels[] = {"a", "b", "c", "d"};
    static const char * const rhs_labels[] = {"e", "f"};
    double coefficients[4], rhs[2], determinant, x, y;
    char output[240];

    if (!toolkit_input_numbers("Coefficients: ax+by=e, cx+dy=f",
                               coefficient_labels, coefficients, 4) ||
        !toolkit_input_numbers("Right-hand sides", rhs_labels, rhs, 2))
        return;
    determinant = coefficients[0] * coefficients[3] - coefficients[1] * coefficients[2];
    if (determinant == 0.0) {
        toolkit_message("No unique solution", "The coefficient determinant is zero.");
        return;
    }
    if (!isfinite(determinant)) {
        toolkit_message("Input out of range", "The coefficients are too large to calculate safely.");
        return;
    }
    x = (rhs[0] * coefficients[3] - coefficients[1] * rhs[1]) / determinant;
    y = (coefficients[0] * rhs[1] - rhs[0] * coefficients[2]) / determinant;
    snprintf(output, sizeof(output),
             "Equations: ax+by=e, cx+dy=f\nD = ad-bc = %.8g\n"
             "x = (ed-bf)/D = %.8g\ny = (af-ec)/D = %.8g",
             determinant, x, y);
    toolkit_message("Simultaneous working", output);
}

static void calculate_percentage(void)
{
    static const char * const labels[] = {"Percentage", "Amount"};
    double values[2];
    char output[160];

    if (!toolkit_input_numbers("Percentage", labels, values, 2))
        return;
    snprintf(output, sizeof(output), "%.8g%% of %.8g\n= %.8g x %.8g / 100\n= %.8g",
             values[0], values[1], values[0], values[1], values[0] * values[1] / 100.0);
    toolkit_message("Percentage working", output);
}

static void calculate_hcf_lcm(void)
{
    static const char * const labels[] = {"Integer 1", "Integer 2"};
    double values[2];
    long long first, second, a, b;
    char output[180];

    if (!toolkit_input_numbers("HCF and LCM", labels, values, 2))
        return;
    if (fabs(values[0]) > 2147483647.0 || fabs(values[1]) > 2147483647.0 ||
        values[0] != trunc(values[0]) || values[1] != trunc(values[1])) {
        toolkit_message("Invalid input", "Use whole numbers between -2147483647 and 2147483647.");
        return;
    }
    first = (long long)values[0];
    second = (long long)values[1];
    a = first < 0 ? -first : first;
    b = second < 0 ? -second : second;
    {
        long long left = a, right = b;
        while (right != 0) {
            long long remainder = left % right;
            left = right;
            right = remainder;
        }
        if (a == 0 || b == 0) {
            snprintf(output, sizeof(output), "Euclidean algorithm gives HCF = %lld\nLCM = 0",
                     left);
        } else {
            snprintf(output, sizeof(output), "Euclidean algorithm gives HCF = %lld\nLCM = |ab|/HCF = %lld",
                     left, (a / left) * b);
        }
    }
    toolkit_message("HCF and LCM working", output);
}

static void calculate_pythagoras(void)
{
    static const char * const labels[] = {"Side 1", "Side 2"};
    double values[2];
    char output[160];

    if (!toolkit_input_numbers("Pythagoras", labels, values, 2))
        return;
    if (values[0] <= 0.0 || values[1] <= 0.0) {
        toolkit_message("Invalid input", "Side lengths must be positive.");
        return;
    }
    snprintf(output, sizeof(output), "c^2 = a^2 + b^2\nc = sqrt(%.8g^2 + %.8g^2)\nHypotenuse = %.8g",
             values[0], values[1], hypot(values[0], values[1]));
    toolkit_message("Pythagoras working", output);
}

static void solve_circle(void)
{
    static const char * const labels[] = {"Radius"};
    double value[1];
    char output[150];

    if (!toolkit_input_numbers("Circle", labels, value, 1))
        return;
    if (value[0] <= 0.0) {
        toolkit_message("Invalid radius", "Radius must be positive.");
        return;
    }
    snprintf(output, sizeof(output), "Circumference = 2*pi*r = %.8g\nArea = pi*r^2 = %.8g",
             2.0 * 3.14159265358979323846 * value[0],
             3.14159265358979323846 * value[0] * value[0]);
    toolkit_message("Circle results", output);
}

void math_tools_menu(void)
{
    static const char * const options[] = {
        "Quadratic equation", "Simultaneous equations", "Percentage",
        "HCF and LCM", "Pythagoras", "Circle calculations", "Back"
    };

    for (;;) {
        switch (toolkit_choose("Mathematics", options, 7)) {
        case 0: solve_quadratic(); break;
        case 1: solve_simultaneous(); break;
        case 2: calculate_percentage(); break;
        case 3: calculate_hcf_lcm(); break;
        case 4: calculate_pythagoras(); break;
        case 5: solve_circle(); break;
        default: return;
        }
    }
}