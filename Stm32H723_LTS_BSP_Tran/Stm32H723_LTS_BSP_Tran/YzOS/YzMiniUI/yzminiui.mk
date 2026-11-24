
YZ_UIDriver_SOURCES = $(wildcard $(YZ_MINIUI_BASE_DIR)/Src/UIDriver/*.c)
YZ_UIDriver_INCLUDES = -I$(YZ_MINIUI_BASE_DIR)/Inc/UIDriver

YZ_layout_SOURCES = $(wildcard $(YZ_MINIUI_BASE_DIR)/Src/layout/*.c)
YZ_layout_INCLUDES = -I$(YZ_MINIUI_BASE_DIR)/Inc/layout
YZ_layout_CXX_SOURCES = $(wildcard $(YZ_MINIUI_BASE_DIR)/Src/layout/*.cpp)

YZ_widget_SOURCES = $(wildcard $(YZ_MINIUI_BASE_DIR)/Src/widget/*.c)
YZ_widget_INCLUDES = -I$(YZ_MINIUI_BASE_DIR)/Inc/widget
YZ_widget_CXX_SOURCES = $(wildcard $(YZ_MINIUI_BASE_DIR)/Src/widget/*.cpp)

YZ_view_SOURCES = $(wildcard $(YZ_MINIUI_BASE_DIR)/Src/view/*.c)
YZ_view_INCLUDES = -I$(YZ_MINIUI_BASE_DIR)/Inc/view
YZ_view_CXX_SOURCES = $(wildcard $(YZ_MINIUI_BASE_DIR)/Src/view/*.cpp)

YZ_utils_SOURCES = $(wildcard $(YZ_MINIUI_BASE_DIR)/Src/utils/*.c)
YZ_utils_INCLUDES = -I$(YZ_MINIUI_BASE_DIR)/Inc/utils
YZ_utils_CXX_SOURCES = $(wildcard $(YZ_MINIUI_BASE_DIR)/Src/utils/*.cpp)

YZ_MINIUI_SOURCES = $(wildcard $(YZ_MINIUI_BASE_DIR)/Src/*.c) \
					$(YZ_UIDriver_SOURCES) \
					$(YZ_widget_SOURCES) \
					$(YZ_utils_SOURCES) \
					$(YZ_view_SOURCES) \
					$(YZ_layout_SOURCES)

YZ_MINIUI_INCLUDES = -I$(YZ_MINIUI_BASE_DIR)/Inc \
					 $(YZ_UIDriver_INCLUDES) \
					 $(YZ_widget_INCLUDES) \
					 $(YZ_utils_INCLUDES) \
					 $(YZ_view_INCLUDES) \
					 $(YZ_layout_INCLUDES)

YZ_MINIUI_CXX_SOURCES =  $(wildcard $(YZ_MINIUI_BASE_DIR)/Src/*.cpp) \
						$(YZ_widget_CXX_SOURCES) \
						$(YZ_view_CXX_SOURCES) \
						$(YZ_utils_CXX_SOURCES) \
						$(YZ_layout_CXX_SOURCES)
