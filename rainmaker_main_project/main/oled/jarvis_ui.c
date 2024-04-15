#include "jarvis_ui.h"

void jarvis_ui(lv_disp_t *disp)
{
    // Set rotation to 180 degrees
    lv_disp_set_rotation(disp, LV_DISP_ROT_180);

    lv_obj_t *scr = lv_disp_get_scr_act(disp);

    // Create the first label (Primary level)
    lv_obj_t *label1 = lv_label_create(scr);
    lv_label_set_long_mode(label1, LV_LABEL_LONG_CLIP); // Circular scroll
    lv_label_set_text(label1, "JARVIS:"); // Static text
    lv_obj_set_width(label1, disp->driver->hor_res);
    lv_obj_align(label1, LV_ALIGN_TOP_MID, 0, 0);

    // Create the first label (Primary level)
    lv_obj_t *label2 = lv_label_create(scr);
    lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR); // Circular scroll
    lv_label_set_text(label2, "Good morning. It's 7 A.M. The weather in Malibu is 23 degrees with scattered clouds. The surf conditions are fair with waist to shoulder highlines, high tide will be at 10:52 a.m."); // Static text
    lv_obj_set_width(label2, disp->driver->hor_res);
    lv_obj_align(label2, LV_ALIGN_TOP_MID, 0, 15);

    // Create the second label (Secondary level)
    lv_obj_t *label3 = lv_label_create(scr);
    lv_label_set_long_mode(label3, LV_LABEL_LONG_CLIP); // Circular scroll
    lv_label_set_text(label3, "Status: \nAll systems go"); // Additional static text
    lv_obj_set_width(label3, disp->driver->hor_res);
    lv_obj_align(label3, LV_ALIGN_TOP_MID, 0, 30); // Position it below the first label

    // Set a smaller font for the second label
    lv_obj_set_style_text_font(label1, &lv_font_montserrat_12, LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label2, &lv_font_montserrat_12, LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label3, &lv_font_montserrat_12, LV_STATE_DEFAULT);
}