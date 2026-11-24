//
// Created by 32827 on 2023/11/15.
//
#include "yzf_gpio.h"


YZF_RESULT yzf_gpio_open_clock(YZF_GPIO_POINTER gpio){
    switch ((uint32_t)gpio) {
        case (uint32_t)GPIOA:
            RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;
            return YZF_OK;
        case (uint32_t)GPIOB:
            RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;
            return YZF_OK;
        case (uint32_t)GPIOC:
            RCC->AHB4ENR |= RCC_AHB4ENR_GPIOCEN;
            return YZF_OK;
        case (uint32_t)GPIOD:
            RCC->AHB4ENR |= RCC_AHB4ENR_GPIODEN;
            return YZF_OK;
        case (uint32_t)GPIOE:
            RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN;
            return YZF_OK;
        case (uint32_t)GPIOF:
            RCC->AHB4ENR |= RCC_AHB4ENR_GPIOFEN;
            return YZF_OK;
        case (uint32_t)GPIOG:
            RCC->AHB4ENR |= RCC_AHB4ENR_GPIOGEN;
        default:
            return YZF_NOT_FOUND;
    }
}
YZF_RESULT yzf_gpio_close_clock(YZF_GPIO_POINTER gpio){
    switch ((uint32_t)gpio) {
        case (uint32_t)GPIOA:
            RCC->AHB4ENR &= ~RCC_AHB4ENR_GPIOAEN;
            return YZF_OK;
        case (uint32_t)GPIOB:
            RCC->AHB4ENR &= ~RCC_AHB4ENR_GPIOBEN;
            return YZF_OK;
        case (uint32_t)GPIOC:
            RCC->AHB4ENR &= ~RCC_AHB4ENR_GPIOCEN;
            return YZF_OK;
        case (uint32_t)GPIOD:
            RCC->AHB4ENR &= ~RCC_AHB4ENR_GPIODEN;
            return YZF_OK;
        case (uint32_t)GPIOE:
            RCC->AHB4ENR &= ~RCC_AHB4ENR_GPIOEEN;
            return YZF_OK;
        case (uint32_t)GPIOF:
            RCC->AHB4ENR &= ~RCC_AHB4ENR_GPIOFEN;
            return YZF_OK;
        case (uint32_t)GPIOG:
            RCC->AHB4ENR &= ~RCC_AHB4ENR_GPIOGEN;
            return YZF_OK;
        default:
            return YZF_NOT_FOUND;
    }
}

YZF_RESULT yzf_gpio_set_PP(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin){
    gpio->MODER  &= ~(0b11UL << (pin*2));
    gpio->MODER  |=  (0b01UL << (pin*2));
    gpio->OTYPER &=  ~(1<<pin);
    return YZF_OK;
}
YZF_RESULT yzf_gpio_set_OD(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin){
    gpio->MODER &= ~(0b11UL << (pin*2));
    gpio->MODER  |=  (0b01UL << (pin*2));
    gpio->OTYPER |= (1<<pin);
    return YZF_OK;
}
YZF_RESULT yzf_gpio_set_AFPP(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin){
    gpio->MODER &= ~(0b11UL << (pin*2));
    gpio->MODER  |=  (0b10UL << (pin*2));
    gpio->PUPDR &= ~(0b01UL << (pin*2));
    gpio->OTYPER &=  ~(1<<pin);
    return YZF_OK;
}
YZF_RESULT yzf_gpio_set_AFOD(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin){
    gpio->MODER &= ~(0b11UL << (pin*2));
    gpio->MODER  |=  (0b10UL << (pin*2));
    gpio->OTYPER |=  (1<<pin);
    return YZF_OK;
}
YZF_RESULT yzf_gpio_set_IN_FLOAT(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin){
    gpio->MODER &= ~(0b11UL << (pin*2));
    gpio->PUPDR &= ~(0b11UL << (pin*2));
    return YZF_OK;
}
YZF_RESULT yzf_gpio_set_IN_PULL_UP(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin){
    gpio->MODER &= ~(0b11UL << (pin*2));
    YZF_MODIFY_REG(gpio->PUPDR,0b11<<pin*2,GPIO_PULLUP,pin*2);
    return YZF_OK;
}
YZF_RESULT yzf_gpio_set_IN_PULL_DOWN(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin){
    gpio->MODER &= ~(0b11UL << (pin*2));
    YZF_MODIFY_REG(gpio->PUPDR,0b11<<pin*2,GPIO_PULLDOWN,pin*2);
    return YZF_OK;
}
YZF_RESULT yzf_gpio_set_IN_ANALOG(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin){
    gpio->MODER |= (0b11UL << (pin*2));
    gpio->PUPDR &= ~(0b11UL << (pin*2));
    return YZF_OK;
}
YZF_RESULT yzf_gpio_set_LOW(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin){
    gpio->OSPEEDR &= ~(0b11UL << (pin*2));
    gpio->OSPEEDR |=  (0b00UL << (pin*2));
    return YZF_OK;
}
YZF_RESULT yzf_gpio_set_MIDDLE(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin) {
    gpio->OSPEEDR &= ~(0b11UL << (pin*2));
    gpio->OSPEEDR |=  (0b01UL << (pin*2));
    return YZF_OK;
}
YZF_RESULT yzf_gpio_set_HIGH(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin){
    gpio->OSPEEDR &= ~(0b11UL << (pin*2));
    gpio->OSPEEDR |=  (0b11UL << (pin*2));
    return YZF_OK;
}
YZF_RESULT yzf_gpio_set_0(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin){
    gpio->BSRR = 0b1UL<<(pin+16);
    return YZF_OK;
}
YZF_RESULT yzf_gpio_set_1(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin){
    gpio->BSRR = 0b1UL<<pin;
    return YZF_OK;
}
YZF_RESULT yzf_gpio_lock(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin){
    gpio->LCKR |= 0b1UL<<pin;
    return YZF_OK;
}
YZF_RESULT yzf_gpio_unlock(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin){
    gpio->LCKR &= ~(0b1UL<<pin);
    return YZF_OK;
}
YZF_RESULT yzf_gpio_set_Pull_Up(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin){
    YZF_MODIFY_REG(gpio->PUPDR,0b11<<pin*2,GPIO_PULLUP,pin*2);
    return YZF_OK;
}
YZF_RESULT yzf_gpio_set_Pull_Down(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin){
    YZF_MODIFY_REG(gpio->PUPDR,0b11<<pin*2,GPIO_PULLDOWN,pin*2);
    return YZF_OK;
}
YZF_RESULT yzf_gpio_set_af(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin,uint8_t af){
    if(pin>=YZF_PIN_8){
        gpio->AFR[1] &= ~(0b1111<<((pin-YZF_PIN_8)*4));
        gpio->AFR[1] |= af<<((pin-YZF_PIN_8)*4);
    }else{
        gpio->AFR[0] &= ~(0b1111<<(pin*4));
        gpio->AFR[0] |= af<<(pin*4);
    }
    return YZF_OK;
}
YZF_BOOL yzf_gpio_get(YZF_GPIO_POINTER gpio,YZF_GPIO_PIN pin){
    return (gpio->IDR & (0b1UL<<pin))?YZF_TRUE:YZF_FALSE;
}

YZF_GPIO_POINTER  mGpio= (YZF_GPIO_POINTER) YZF_NULL;
YZF_GPIO_PIN  mPin=YZF_NULL;
YZF_RESULT yzf_gpio(YZF_GPIO_POINTER gpio){
    mGpio=gpio;
    return YZF_OK;
}
YZF_RESULT yzf_gpio_pin(YZF_GPIO_PIN pin){
    mPin=pin;
    return YZF_OK;
}
YZF_RESULT yzf_gpio_open_clock_(){
    YZF_CHECK_PARAM(mGpio)
    return yzf_gpio_open_clock(mGpio);
}
YZF_RESULT yzf_gpio_close_clock_(){
    YZF_CHECK_PARAM(mGpio)
    return yzf_gpio_close_clock(mGpio);
}
YZF_RESULT yzf_gpio_set_PP_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_set_PP(mGpio,mPin);
}
YZF_RESULT yzf_gpio_set_Pull_Up_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_set_Pull_Up(mGpio,mPin);
}
YZF_RESULT yzf_gpio_set_Pull_Down_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_set_Pull_Down(mGpio,mPin);
}
YZF_RESULT yzf_gpio_set_OD_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_set_OD(mGpio,mPin);
}
YZF_RESULT yzf_gpio_set_AFPP_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_set_AFPP(mGpio,mPin);
}
YZF_RESULT yzf_gpio_set_AFOD_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_set_AFOD(mGpio,mPin);
}
YZF_RESULT yzf_gpio_set_IN_FLOAT_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_set_IN_FLOAT(mGpio,mPin);
}
YZF_RESULT yzf_gpio_set_IN_PULL_UP_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_set_IN_PULL_UP(mGpio,mPin);
}
YZF_RESULT yzf_gpio_set_IN_PULL_DOWN_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_set_IN_PULL_DOWN(mGpio,mPin);
}
YZF_RESULT yzf_gpio_set_IN_ANALOG_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_set_IN_ANALOG(mGpio,mPin);
}
YZF_RESULT yzf_gpio_set_MIDDLE_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_set_MIDDLE(mGpio,mPin);
}
YZF_RESULT yzf_gpio_set_LOW_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_set_LOW(mGpio,mPin);
}
YZF_RESULT yzf_gpio_set_HIGH_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_set_HIGH(mGpio,mPin);
}
YZF_RESULT yzf_gpio_set_0_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_set_0(mGpio,mPin);
}
YZF_RESULT yzf_gpio_set_1_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_set_1(mGpio,mPin);
}
YZF_RESULT yzf_gpio_lock_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_lock(mGpio,mPin);
}
YZF_RESULT yzf_gpio_unlock_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_unlock(mGpio,mPin);
}
YZF_RESULT yzf_gpio_set_af_(uint8_t type){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_set_af(mGpio,mPin,type);
}
YZF_BOOL yzf_gpio_get_(){
    YZF_CHECK_PARAM(mGpio)
    YZF_CHECK_PARAM(mPin)
    return yzf_gpio_get(mGpio,mPin);
}