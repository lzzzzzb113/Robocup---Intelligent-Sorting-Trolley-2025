//
// Created by 32827 on 2024/1/10.
//
#include "yzl_softport.h"
#if USE_SOFT_PORT

void yzl_softport_delayUS (__IO uint32_t ulCount)
{
    uint32_t i;
    for ( i = 0; i < ulCount; i ++ ) {
        volatile uint16_t uc = (YZ_CONF_CLOCK_FREQ)/(1000*8800);
        while ( uc -- );
    }
}
void yzl_softport_delayMS (__IO uint32_t ulCount){
    uint32_t i;
    for ( i = 0; i < ulCount; i ++ ) {
        yzl_softport_delayUS(1000);
    }
}

#endif