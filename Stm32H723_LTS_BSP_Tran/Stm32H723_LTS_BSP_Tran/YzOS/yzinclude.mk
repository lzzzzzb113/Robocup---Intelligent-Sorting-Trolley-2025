
# YZOS Config
YZ_CONFIG_BASE_DIR = YzOS/YzConfig
YZ_CONFIG_SOURCES = $(wildcard $(YZ_CONFIG_BASE_DIR)/Src/*.c)
YZ_CONFIG_INCLUDES = -I$(YZ_CONFIG_BASE_DIR)/Inc

# YZOS BASE
YZ_BASE_BASE_DIR = YzOS/YzBase
YZ_BASE_SOURCES = $(wildcard $(YZ_BASE_BASE_DIR)/Src/*.c)
YZ_BASE_INCLUDES = -I$(YZ_BASE_BASE_DIR)/Inc

# YZOS MATH
YZ_MATH_BASE_DIR = YzOS/YzMath
YZ_MATH_SOURCES = $(wildcard $(YZ_MATH_BASE_DIR)/Src/*.c)
YZ_MATH_INCLUDES = -I$(YZ_MATH_BASE_DIR)/Inc

# YZOS SoftPort
YZ_SOFTPORT_BASE_DIR = YzOS/YzSoftPort
YZ_SOFTPORT_SOURCES = $(wildcard $(YZ_SOFTPORT_BASE_DIR)/Src/*.c)
YZ_SOFTPORT_INCLUDES = -I$(YZ_SOFTPORT_BASE_DIR)/Inc

# YZOS MemManager
YZ_MEMMANAGER_BASE_DIR = YzOS/YzMemManager
YZ_MEMMANAGER_SOURCES = $(wildcard $(YZ_MEMMANAGER_BASE_DIR)/Src/*.c)
YZ_MEMMANAGER_INCLUDES = -I$(YZ_MEMMANAGER_BASE_DIR)/Inc

#YZOS Peripheral
YZ_PERIPHERAL_BASE_DIR = YzOS/YzPeripheral
YZ_PERIPHERAL_SOURCES = $(wildcard $(YZ_PERIPHERAL_BASE_DIR)/Src/*.c)
YZ_PERIPHERAL_INCLUDES = -I$(YZ_PERIPHERAL_BASE_DIR)/Inc

# YZOS FatFsCover
### Move Need Change For SD Card Read/Write
### See Src/yzl_ff_release.c
YZ_FATFSCOVER_BASE_DIR = YzOS/YzFatFsCover
YZ_FATFSCOVER_SOURCES = $(wildcard $(YZ_FATFSCOVER_BASE_DIR)/Src/*.c)
YZ_FATFSCOVER_INCLUDES = -I$(YZ_FATFSCOVER_BASE_DIR)/Inc

# YZOS Font
YZ_FONT_BASE_DIR = YzOS/YzFont
YZ_FONT_SOURCES = $(wildcard $(YZ_FONT_BASE_DIR)/Src/*.c)
YZ_FONT_INCLUDES = -I$(YZ_FONT_BASE_DIR)/Inc

# YZOS YzDriver
YZ_DRIVER_BASE_DIR = YzOS/YzDriver
YZ_DRIVER_SOURCES = $(wildcard $(YZ_DRIVER_BASE_DIR)/Src/*.c)
YZ_DRIVER_INCLUDES = -I$(YZ_DRIVER_BASE_DIR)/Inc

# YZOS LvglCover
# OBJECTS += $(patsubst %.c, $(BUILD_DIR)/%.o, $(CSRCS))
LVGL_DIR = YzOS
LVGL_DIR_NAME = YzLvglCover
include YzOS/YzLvglCover/lvgl.mk
YZ_LVGL_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/*.c)
YZ_LVGL_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)

# YZOS Lvgl Object Extra
YZ_LVGL_MULT_OBJ_SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/multiOBj/Src/*.c)
YZ_LVGL_MULT_OBJ_INCLUDES += -I$(LVGL_DIR)/$(LVGL_DIR_NAME)/multiOBj/Inc

# YZOS Mini UI
YZ_MINIUI_BASE_DIR = YzOS/YzMiniUI
include YzOS/YzMiniUI/yzminiui.mk

# YZOS Appliction
YZ_APP_BASE_DIR = YzOS/YzApplication
YZ_APP_SOURCES = $(wildcard $(YZ_APP_BASE_DIR)/Src/*.c)
YZ_APP_INCLUDES = -I$(YZ_APP_BASE_DIR)/Inc
YZ_APP_CXX_SOURCES = $(wildcard $(YZ_APP_BASE_DIR)/Src/*.cpp)

#YZOS C With Class Support
YZ_CWithClassSupport_BASE_DIR = YzOS/YzCWithClassSupport
YZ_CWithClassSupport_CXX_SOURCES = $(wildcard $(YZ_CWithClassSupport_BASE_DIR)/Src/*.cpp)
YZ_CWithClassSupport_INCLUDES = -I$(YZ_CWithClassSupport_BASE_DIR)/Inc

#YZOS Space Sensor
YZ_SPACE_SENSOR_BASE_DIR = YzOS/YzSpaceSensor
YZ_SPACE_SENSOR_SOURCES = $(wildcard $(YZ_SPACE_SENSOR_BASE_DIR)/Src/*.c)
YZ_SPACE_SENSOR_CXX_SOURCES = $(wildcard $(YZ_SPACE_SENSOR_BASE_DIR)/Src/*.cpp)
YZ_SPACE_SENSOR_INCLUDES = -I$(YZ_SPACE_SENSOR_BASE_DIR)/Inc

MJSON_BASE_DIR = YzOS/extLib/mjson
MJSON_SOURCES = $(wildcard $(MJSON_BASE_DIR)/src/*.c)
MJSON_INCLUDES = -I$(MJSON_BASE_DIR)/include

# ALL
YZ_ALL_SOURCES += $(YZ_MATH_SOURCES) \
				$(YZ_CONFIG_SOURCES) \
				$(YZ_BASE_SOURCES) \
                $(YZ_APP_SOURCES) \
                $(YZ_SOFTPORT_SOURCES) \
                $(YZ_MEMMANAGER_SOURCES) \
                $(YZ_FATFSCOVER_SOURCES) \
                $(YZ_FONT_SOURCES) \
                $(YZ_DRIVER_SOURCES) \
                $(YZ_PERIPHERAL_SOURCES) \
                $(YZ_MINIUI_SOURCES) \
                $(MJSON_SOURCES) \
                $(YZ_SPACE_SENSOR_SOURCES) \
#启用lvgl需 开启Makefile的编译选项 system_int文件中的tick中断
#			 	$(YZ_LVGL_SOURCES) \
#				$(YZ_LVGL_MULT_OBJ_SOURCES) \

YZ_ALL_INCLUDES +=  $(YZ_MATH_INCLUDES)  \
					$(YZ_CONFIG_INCLUDES) \
					$(YZ_BASE_INCLUDES) \
                    $(YZ_APP_INCLUDES) \
                    $(YZ_SOFTPORT_INCLUDES) \
                    $(YZ_MEMMANAGER_INCLUDES) \
                    $(YZ_FATFSCOVER_INCLUDES) \
                    $(YZ_FONT_INCLUDES) \
                    $(YZ_LVGL_INCLUDES) \
                    $(YZ_LVGL_MULT_OBJ_INCLUDES) \
                    $(YZ_DRIVER_INCLUDES) \
                    $(YZ_PERIPHERAL_INCLUDES) \
                    $(YZ_MINIUI_INCLUDES) \
                    $(YZ_CWithClassSupport_INCLUDES) \
                    $(MJSON_INCLUDES) \
                    $(YZ_SPACE_SENSOR_INCLUDES) \

YZ_CXX_SOURCES += 	$(YZ_CWithClassSupport_CXX_SOURCES) \
					$(YZ_MINIUI_CXX_SOURCES) \
					$(YZ_APP_CXX_SOURCES) \
					$(YZ_SPACE_SENSOR_CXX_SOURCES) \
