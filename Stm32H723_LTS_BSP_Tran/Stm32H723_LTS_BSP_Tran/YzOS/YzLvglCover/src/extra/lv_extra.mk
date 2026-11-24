#CSRCS += $(shell cmd /c "dir /b /s $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/*.c")
#
#


YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/layouts/flex/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/layouts/grid/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/themes/default/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/win/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/tileview/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/tabview/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/spinner/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/spinbox/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/span/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/msgbox/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/meter/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/menu/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/list/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/led/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/keyboard/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/imgbtn/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/colorwheel/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/chart/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/calendar/*.c)
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/animimg/*.c)

YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/layouts/flex
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/layouts/grid
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/themes/default
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/win
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/tileview
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/tabview
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/spinner
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/spinbox
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/span
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/msgbox
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/meter
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/menu
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/list
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/led
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/keyboard
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/imgbtn
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/colorwheel
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/chart
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/calendar
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets/animimg


#CSRCS += $(shell find -L $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra -name \*.c)
