#include "toolkit.h"

#include <ndialog.h>
#include <math.h>
#include <stdlib.h>

int toolkit_choose(const char *title, const char * const options[], int count)
{
    const char *terminated_options[16];
    ndialog_t *dialog;
    int selected = 0;
    int index;
    ndialog_result_t result;

    if (count < 1 || count >= 16)
        return -1;
    for (index = 0; index < count; ++index)
        terminated_options[index] = options[index];
    terminated_options[count] = NULL;

    dialog = ndlg_create(title);
    if (dialog == NULL)
        return -1;

    ndlg_add_combobox(dialog, "Select", terminated_options, &selected);
    ndlg_set_button_bar(dialog, NDLG_BTN_OK_CANCEL);
    result = ndlg_show(dialog);
    ndlg_destroy(dialog);

    if (result != NDLG_RESULT_OK || selected < 0 || selected >= count)
        return -1;
    return selected;
}

void toolkit_message(const char *title, const char *message)
{
    ndialog_t *dialog = ndlg_create(title);

    if (dialog == NULL)
        return;
    ndlg_add_label(dialog, message);
    ndlg_set_button_bar(dialog, NDLG_BTN_OK);
    ndlg_show(dialog);
    ndlg_destroy(dialog);
}

int toolkit_input_numbers(const char *title, const char * const labels[],
                          double values[], size_t count)
{
    char fields[4][32] = {{0}};
    char *end;
    ndialog_t *dialog;
    ndialog_result_t result;
    size_t index;

    if (count == 0 || count > 4)
        return 0;

    dialog = ndlg_create(title);
    if (dialog == NULL)
        return 0;

    for (index = 0; index < count; ++index)
        ndlg_add_text_entry(dialog, labels[index], fields[index], (int)sizeof(fields[index]));
    ndlg_set_button_bar(dialog, NDLG_BTN_OK_CANCEL);
    result = ndlg_show(dialog);
    ndlg_destroy(dialog);
    if (result != NDLG_RESULT_OK)
        return 0;

    for (index = 0; index < count; ++index) {
        values[index] = strtod(fields[index], &end);
        if (end == fields[index] || *end != '\0' || !isfinite(values[index])) {
            toolkit_message("Invalid input", "Enter a valid finite number in every field.");
            return 0;
        }
    }
    return 1;
}