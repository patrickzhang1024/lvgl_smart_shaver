#include <stdbool.h>
#include "smart_shaver.h"

static lv_obj_t * create_window(lv_obj_t *parent, const char *title, lv_color_t bg_color, bool add_label);
static void setup_first_window(lv_obj_t *win);
static void setup_second_window(lv_obj_t *win);

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
  lv_obj_t *win1 = create_window(pager, "Window 1", lv_color_hex(0x000000), false);
  setup_first_window(win1);

  lv_obj_t *win2 = create_window(pager, "Window 2", lv_color_hex(0x000000), false);
  setup_second_window(win2);
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

static void setup_second_window(lv_obj_t *win)
{
  /* Full black background */
  lv_obj_set_style_bg_color(win, lv_color_hex(0x000000), 0);
  lv_obj_set_style_bg_opa(win, LV_OPA_100, 0);
  lv_obj_set_flex_flow(win, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(win, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
  lv_obj_set_style_pad_all(win, 16, 0);
  lv_obj_set_style_pad_row(win, 20, 0);

  /* Top status bar */
  lv_obj_t *status_bar = lv_obj_create(win);
  lv_obj_remove_style_all(status_bar);
  lv_obj_set_size(status_bar, LV_PCT(100), 32);
  lv_obj_set_flex_flow(status_bar, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(status_bar, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_bg_opa(status_bar, LV_OPA_TRANSP, 0);

  lv_obj_t *bt_label = lv_label_create(status_bar);
  lv_label_set_text(bt_label, LV_SYMBOL_BLUETOOTH);
  lv_obj_set_style_text_color(bt_label, lv_color_hex(0x4DA3FF), 0);
  lv_obj_set_style_text_font(bt_label, LV_FONT_DEFAULT, 0);

  lv_obj_t *battery_label = lv_label_create(status_bar);
  lv_label_set_text_fmt(battery_label, "%s 90%%", LV_SYMBOL_BATTERY_FULL);
  lv_obj_set_style_text_color(battery_label, lv_color_hex(0xFFFFFF), 0);

  /* Centered vertical buttons */
  lv_obj_t *btn_col = lv_obj_create(win);
  lv_obj_remove_style_all(btn_col);
  lv_obj_set_size(btn_col, LV_PCT(100), LV_SIZE_CONTENT);
  lv_obj_set_flex_flow(btn_col, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(btn_col, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_pad_row(btn_col, 14, 0);

  const char *labels[] = {"Mode", "Connect", "Auto clean", "Setting"};
  uint8_t label_count = sizeof(labels) / sizeof(labels[0]);
  for(uint8_t i = 0; i < label_count; i++) {
    lv_obj_t *btn = lv_btn_create(btn_col);
    lv_obj_set_size(btn, 160, 48);
    lv_obj_set_style_bg_color(btn, lv_color_hex(0x222222), 0);
    lv_obj_set_style_bg_opa(btn, LV_OPA_90, 0);
    lv_obj_set_style_radius(btn, 12, 0);
    lv_obj_set_style_outline_width(btn, 0, 0);

    lv_obj_t *lbl = lv_label_create(btn);
    lv_label_set_text(lbl, labels[i]);
    lv_obj_set_style_text_color(lbl, lv_color_hex(0xFFFFFF), 0);
    lv_obj_center(lbl);
  }
}


