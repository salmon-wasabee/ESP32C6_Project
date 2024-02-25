#include "lvgl.h"

/* Include your OLED display's header files here */
// #include "your_oled_display_driver.h"

/* Static functions declarations */
static void lv_obj_set_width_anim(void * obj, int32_t value);
static void lv_obj_set_height_anim(void * obj, int32_t value);
static void create_siri_waveform(lv_obj_t* parent);
void friday_ui(lv_disp_t *disp);

/* LVGL buffer and display driver setup */
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10]; /* A buffer for 10 lines */

/* Initialize your display here and create a function to flush the graphics from LVGL to your display */
// static void my_display_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);

void app_main() {
    /* Initialize LVGL */
    lv_init();

    /* Initialize your OLED display here */
    // oled_init();

    /* Set up the LVGL draw buffer */
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, LV_HOR_RES_MAX * 10);

    /* Set up the LVGL display driver */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = 128;
    disp_drv.ver_res = 64;
    disp_drv.flush_cb = my_display_flush; /* This should be your display flush function */
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /* Now you can call your UI setup function */
    lv_obj_t *scr = lv_disp_get_scr_act(NULL); /* Get the current screen */
    friday_ui(scr);
}

/* Your existing functions go here, including create_siri_waveform and friday_ui */
static void create_siri_waveform(lv_obj_t* parent) {
    lv_obj_t* arc;
    for (int i = 0; i < 3; i++) {
        arc = lv_arc_create(parent);
        lv_arc_set_start_angle(arc, 0);
        lv_arc_set_end_angle(arc, 360);
        lv_arc_set_rotation(arc, i * 45); // Rotate each arc for variation
        lv_obj_set_size(arc, 20 + i * 10, 20 + i * 10); // Increase size for each arc
        lv_obj_center(arc);

        // Animation for width
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, arc);
        lv_anim_set_exec_cb(&a, lv_obj_set_width_anim); // Use wrapper function
        lv_anim_set_values(&a, 20 + i * 10, 30 + i * 10);
        lv_anim_set_time(&a, 1000);
        lv_anim_set_playback_time(&a, 1000);
        lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
        lv_anim_start(&a);

        // Repeat the same for height using the height wrapper
        lv_anim_set_exec_cb(&a, lv_obj_set_height_anim); // Use wrapper function for height
        lv_anim_start(&a);
    }
}

void friday_ui(lv_disp_t *disp) {
    lv_disp_set_rotation(disp, LV_DISP_ROT_180);
    lv_obj_t *scr = lv_disp_get_scr_act(disp);

    lv_obj_t *label1 = lv_label_create(scr);
    lv_label_set_text(label1, "FRIDAY");
    lv_obj_align(label1, LV_ALIGN_TOP_MID, 0, 0);

    lv_obj_t *anim_container = lv_obj_create(scr);
    lv_obj_set_size(anim_container, 50, 50); // Increased size for visibility
    lv_obj_align(anim_container, LV_ALIGN_TOP_MID, 0, 10); // Center the container for visibility

    create_siri_waveform(anim_container);
}

/* Implement the my_display_flush function based on your OLED display's requirements */
static void my_display_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    /* Code to transfer the LVGL rendered graphics to your display */
    lv_disp_t * disp = (lv_disp_t *)user_ctx;
    lvgl_port_flush_ready(disp);
    return false;
    /* Don't forget to call lv_disp_flush_ready(disp_drv) at the end */
}
