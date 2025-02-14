//include header files 
#include <ch32v00x.h>
#include <debug.h>

// define decoder function  
void decoder_2to4(int g0, int g1, uint8_t *d0, uint8_t *d1, uint8_t *d2, uint8_t *d3) {
    *d0 = (g1 == 0) && (g0 == 0);
    *d1 = (g1 == 0) && (g0 == 1);
    *d2 = (g1 == 1) && (g0 == 0);
    *d3 = (g1 == 1) && (g0 == 1);
}

//pin configuration 
void GPIO_Config(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0}; //structure variable used for the GPIO configuration
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); // to Enable the clock for Port D

    // input pin definition  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5; // Defines which Pin to configure
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // Defines Output Type
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Defines speed
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // output pin definition  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Defines Output Type
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Defines speed
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

// main function  
int main(void) {
    uint8_t g0, g1, d0, d1, d2, d3 = 0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    GPIO_Config();

    while(1) {
        g0 = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4);
        g1 = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_5);

        decoder_2to4(g0, g1, &d0, &d1, &d2, &d3);

        if(d0 == 0) { GPIO_WriteBit(GPIOD, GPIO_Pin_0, RESET); }
        else { GPIO_WriteBit(GPIOD, GPIO_Pin_0, SET); }

        if(d1 == 0) { GPIO_WriteBit(GPIOD, GPIO_Pin_1, RESET); }
        else { GPIO_WriteBit(GPIOD, GPIO_Pin_1, SET); }

        if(d2 == 0) { GPIO_WriteBit(GPIOD, GPIO_Pin_2, RESET); }
        else { GPIO_WriteBit(GPIOD, GPIO_Pin_2, SET); }

        if(d3 == 0) { GPIO_WriteBit(GPIOD, GPIO_Pin_3, RESET); }
        else { GPIO_WriteBit(GPIOD, GPIO_Pin_3, SET); }
    }
}
