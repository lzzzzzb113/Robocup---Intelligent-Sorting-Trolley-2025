CSRCS += lv_port_disp.c
CSRCS += lv_port_fs.c
CSRCS += lv_port_indev.c

DEPPATH += --dep-path $(LVGL_DIR)/$(LVGL_DIR_NAME)/porting
VPATH += :$(LVGL_DIR)/$(LVGL_DIR_NAME)/porting

CFLAGS += "-I$(LVGL_DIR)/$(LVGL_DIR_NAME)/porting"