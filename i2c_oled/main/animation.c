#include "lvgl.h"

static void lv_obj_set_width_anim(void * obj, int32_t value) {
    lv_obj_set_width(obj, value);
}

static void lv_obj_set_height_anim(void * obj, int32_t value) {
    lv_obj_set_height(obj, value);
}


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

void example_lvgl_siri_ui(lv_disp_t *disp) {
    lv_disp_set_rotation(disp, LV_DISP_ROT_180);
    lv_obj_t *scr = lv_disp_get_scr_act(disp);

    lv_obj_t *label1 = lv_label_create(scr);
    lv_label_set_text(label1, "F.R.I.D.A.Y ");
    lv_obj_align(label1, LV_ALIGN_TOP_MID, 0, 0);

    lv_obj_t *anim_container = lv_obj_create(scr);
    lv_obj_set_size(anim_container, 128, 64); // Increased size for visibility
    lv_obj_align(anim_container, LV_ALIGN_CENTER, 0, 0); // Center the container for visibility

    create_siri_waveform(anim_container);
}
