#include "smart_shaver.h"

static lv_obj_t * create_window(lv_obj_t *parent, const char *title, lv_color_t bg_color);

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
  create_window(pager, "Window 1", lv_color_hex(0xFFFFFF));
  create_window(pager, "Window 2", lv_color_hex(0x0066FF));
  create_window(pager, "Window 3", lv_color_hex(0xFFCC00));
  create_window(pager, "Window 4", lv_color_hex(0xFF3333));
}

static lv_obj_t * create_window(lv_obj_t *parent, const char *title, lv_color_t bg_color)
{
  lv_obj_t *win = lv_obj_create(parent);
  lv_obj_remove_style_all(win);
  lv_obj_set_size(win, SMART_SHAVER_SCREEN_WIDTH, SMART_SHAVER_SCREEN_HEIGHT);
  lv_obj_set_style_bg_color(win, bg_color, 0);
  lv_obj_set_style_bg_opa(win, LV_OPA_100, 0);

  /* Simple title to differentiate the empty windows */
  lv_obj_t *label = lv_label_create(win);
  lv_label_set_text(label, title);
  lv_obj_center(label);

  return win;
}


