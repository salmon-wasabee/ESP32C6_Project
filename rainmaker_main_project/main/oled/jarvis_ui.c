#include "jarvis_ui.h"
#include "../mic_test/mic_test.h"

extern double db;
extern char db_str[20];
char temp[50];
char temp1[50];

lv_obj_t *label3;
lv_obj_t *label4;

void update_label_task(void *pvParameter)
{
    while (1) {
        sprintf(temp, "Sound: %s dBs", db_str);
        lv_label_set_text(label3, temp);
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }
}

void update_label_task1(void *pvParameter)
{
    while (1) {
        double db_value = atof(db_str); // Convert db_str to a double
        if (db_value < 30)
            sprintf(temp1, "Quiet");
        else if (db_value >= 30 && db_value < 40)
            sprintf(temp1, "Whisper");
        else if (db_value >= 40 && db_value < 50)
            sprintf(temp1, "Library");
        else if (db_value >= 50 && db_value < 60)
            sprintf(temp1, "Moderate Rainfall");
        else if (db_value >= 60 && db_value < 70)
            sprintf(temp1, "Conversation");
        else if (db_value >= 70 && db_value < 80)
            sprintf(temp1, "Vacuum Cleaner,127 hrs");
        else if (db_value >= 80 && db_value < 90)
            sprintf(temp1, "Restaurant,40 hrs");
        else if (db_value >= 90 && db_value < 100)
            sprintf(temp1, "Motorcycle, 4 hrs");
        else if (db_value >= 100 && db_value < 110)
            sprintf(temp1, "Ambulance, 24 mins");
        else if (db_value >= 110 && db_value < 120)
            sprintf(temp1, "Concert, 4 mins");
        else if (db_value >= 120 && db_value <= 130)
            sprintf(temp1, "Thunder, 1 min");
        else
            sprintf(temp1, "-");

        lv_label_set_text(label4, temp1);
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }
}


void jarvis_ui(lv_disp_t *disp)
{
    // // Set rotation to 180 degrees
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
    label3 = lv_label_create(scr);
    lv_label_set_long_mode(label3, LV_LABEL_LONG_CLIP); // Circular scroll
    lv_label_set_text(label3, temp); // Additional static text
    lv_obj_set_width(label3, disp->driver->hor_res);
    lv_obj_align(label3, LV_ALIGN_TOP_MID, 0, 30); // Position it below the first label

        // Create the second label (Secondary level)
    label4  = lv_label_create(scr);
    lv_label_set_long_mode(label4, LV_LABEL_LONG_CLIP); // Circular scroll
    lv_label_set_text(label4, "------"); // Additional static text
    lv_obj_set_width(label4, disp->driver->hor_res);
    lv_obj_align(label4, LV_ALIGN_TOP_MID, 0, 45); // Position it below the first label

    

    // Set a smaller font for the second label
    lv_obj_set_style_text_font(label1, &lv_font_montserrat_12, LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label2, &lv_font_montserrat_12, LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label3, &lv_font_montserrat_12, LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label4, &lv_font_montserrat_12, LV_STATE_DEFAULT);

    xTaskCreate(update_label_task, "Update Label Task", 4096, NULL, 5, NULL);
    xTaskCreate(update_label_task1, "Update Label Task 1", 4096, NULL, 5, NULL);
}

