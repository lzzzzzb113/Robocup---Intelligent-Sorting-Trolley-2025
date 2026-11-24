/**
 * @file lv_templ.h
 *
 */

/**
 * TODO Remove these instructions
 * Search and replace: cn_label-> object short name with lower case(e.g. btn, label etc)
 *                    CN_LABAL -> object short name with upper case (e.g. BTN, LABEL etc.)
 *
 */

#ifndef LV_CN_LABEL_H
#define LV_CN_LABEL_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../src/lv_conf_internal.h"

#define LV_USE_CN_LABAL 0
#if LV_USE_CN_LABAL != 0

#include "../core/lv_obj.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of template*/
typedef struct {
    lv_ANCESTOR_t ancestor; /*The ancestor widget, e.g. lv_slider_t slider*/
    /*New data for this type*/
} lv_cn_label_t;

extern const lv_obj_class_t lv_cn_label_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a cn_label object
 * @param parent    pointer to an object, it will be the parent of the new cn_label
 * @return          pointer to the created bar
 */
lv_obj_t * lv_cn_label_create(lv_obj_t * parent);

/*======================
 * Add/remove functions
 *=====================*/

/*=====================
 * Setter functions
 *====================*/

/*=====================
 * Getter functions
 *====================*/

/*=====================
 * Other functions
 *====================*/

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_CN_LABAL*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_CN_LABEL_H*/
