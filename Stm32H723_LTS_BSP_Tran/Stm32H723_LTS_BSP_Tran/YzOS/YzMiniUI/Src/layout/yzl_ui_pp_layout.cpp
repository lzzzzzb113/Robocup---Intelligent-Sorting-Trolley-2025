//
// Created by 32827 on 2024/2/11.
//
#include "layout/yzl_ui_pp_layout.hpp"

LayoutBase::LayoutBase(ViewBase *view) {
    this->view = view;
}

LayoutBase::~LayoutBase() = default;

UI_Rect *LayoutBase::nextRect() {
    return &uiRect;
}

UI_Rect *LayoutBase::nextRect(uint16_t width, uint16_t height) {
    return &uiRect;
}

void LayoutBase::delRect(UI_Rect *rect) {

}

void LayoutBase::delRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {

}

uint16_t LayoutBase::getIndex(UI_Rect *rect) {
    return 0;
}
