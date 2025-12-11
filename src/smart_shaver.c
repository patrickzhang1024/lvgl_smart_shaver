#include <stdbool.h>
#include "smart_shaver.h"

static lv_obj_t * create_window(lv_obj_t *parent, const char *title, lv_color_t bg_color, bool add_label);
static void setup_first_window(lv_obj_t *win);

void smart_shaver_ui_init(void)
{
  /* Root screen */
  lv_obj_t *screen = lv_scr_act();

  /* Horizontal pager holding the windows */
  lv_obj_t *pager = lv_obj_create(screen);
  lv_obj_remove_style_all(pager);
  lv_obj_set_size(pager, LV_PCT(100), LV_PCT(100));
  lv_obj_set_flex_flow(pager, LV_FLEX_FLOW_ROW);
  lv_obj_set_scrollbar_mode(pager, LV_SCROLLBAR_MODE_OFF);
  lv_obj_set_scroll_dir(pager, LV_DIR_HOR);
  lv_obj_set_scroll_snap_x(pager, LV_SCROLL_SNAP_CENTER);
  lv_obj_clear_flag(pager, LV_OBJ_FLAG_SCROLL_ELASTIC);
  lv_obj_add_flag(pager, LV_OBJ_FLAG_SCROLL_ONE);
  lv_obj_set_style_pad_all(pager, 0, 0);

  /* Create four blank windows */
  lv_obj_t *win1 = create_window(pager, "Window 1", lv_color_hex(0xFFFFFF), false);
  setup_first_window(win1);

  create_window(pager, "Window 2", lv_color_hex(0x0066FF), true);
  create_window(pager, "Window 3", lv_color_hex(0xFFCC00), true);
  create_window(pager, "Window 4", lv_color_hex(0xFF3333), true);
}

static lv_obj_t * create_window(lv_obj_t *parent, const char *title, lv_color_t bg_color, bool add_label)
{
  lv_obj_t *win = lv_obj_create(parent);
  lv_obj_remove_style_all(win);
  lv_obj_set_size(win, SMART_SHAVER_SCREEN_WIDTH, SMART_SHAVER_SCREEN_HEIGHT);
  lv_obj_set_style_bg_color(win, bg_color, 0);
  lv_obj_set_style_bg_opa(win, LV_OPA_100, 0);

  if(add_label) {
    /* Simple title to differentiate the empty windows */
    lv_obj_t *label = lv_label_create(win);
    lv_label_set_text(label, title);
    lv_obj_center(label);
  }

  return win;
}

static void setup_first_window(lv_obj_t *win)
{
  /* Vertical layout: animation area on top, control buttons row at bottom */
  lv_obj_set_flex_flow(win, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(win, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
  lv_obj_set_style_pad_all(win, 0, 0);
  lv_obj_set_style_pad_row(win, 0, 0);

  /* Animation area placeholder */
  lv_obj_t *anim_area = lv_obj_create(win);
  lv_obj_remove_style_all(anim_area);
  lv_obj_set_size(anim_area, SMART_SHAVER_SCREEN_WIDTH, 560);
  lv_obj_set_style_bg_color(anim_area, lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_style_bg_opa(anim_area, LV_OPA_20, 0);
  lv_obj_set_style_border_width(anim_area, 0, 0);
  lv_obj_clear_flag(anim_area, LV_OBJ_FLAG_SCROLLABLE);

  /* Button row */
  lv_obj_t *btn_row = lv_obj_create(win);
  lv_obj_remove_style_all(btn_row);
  lv_obj_set_size(btn_row, LV_PCT(100), 80);
  lv_obj_set_flex_flow(btn_row, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(btn_row, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_pad_all(btn_row, 0, 0);
  lv_obj_set_style_pad_column(btn_row, 10, 0);

  const char *labels[3] = {"clean", "replace", "ready"};
  for(uint8_t i = 0; i < 3; i++) {
    lv_obj_t *btn = lv_btn_create(btn_row);
    lv_obj_set_size(btn, 100, 80);
    lv_obj_t *lbl = lv_label_create(btn);
    lv_label_set_text(lbl, labels[i]);
    lv_obj_center(lbl);
  }
}


