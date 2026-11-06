#include "toolkit.h"

int main(void)
{
    static const char * const options[] = {
        "Mathematics tools",
        "Computer Science",
        "Formula library",
        "Exam practice",
        "Settings",
        "About",
        "Exit"
    };

    for (;;) {
        int selected = toolkit_choose("O-LEVEL MASTER TOOLKIT", options, 7);
        switch (selected) {
        case 0:
            math_tools_menu();
            break;
        case 1:
            cs_tools_menu();
            break;
        case 2:
            formula_library();
            break;
        case 3:
            exam_practice();
            break;
        case 4:
            settings_menu();
            break;
        case 5:
            toolkit_message("About",
                "O-LEVEL MASTER TOOLKIT\n"
                "Ndless edition 1.0\n"
                "Maths and Computer Science\n"
                "Answers are numerical approximations where stated.");
            break;
        default:
            return 0;
        }
    }
}