/*
 * LED blink with FreeRTOS
 */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

#include <string.h>

#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/adc.h"

#include "hc06.h"

#include <math.h>
#include <stdlib.h>

#define UART_ID uart1

const int BTN1 = 15;
const int BTN2 = 14;
const int BTN3 = 13;
const int BTN4 = 12;

const int LED1 = 16;
const int LED2 = 17;
const int LED3 = 18;
const int LED4 = 19;

typedef struct btn {
    int id;
    int val;
} info;

QueueHandle_t xQueueInfo;

void gpio_callback(uint gpio, uint32_t events){
    if (events == 0x4) {
        info data;
        data.val = 1;
        if(gpio == BTN1){
            data.id = 1;
            xQueueSendFromISR(xQueueInfo, &data, 0);
        }
        else if(gpio == BTN2){
            data.id = 2;
            xQueueSendFromISR(xQueueInfo, &data, 0);
        }
        else if(gpio == BTN3){
            data.id = 3;
            xQueueSendFromISR(xQueueInfo, &data, 0);
        }
        else if(gpio == BTN4){
            data.id = 4;
            xQueueSendFromISR(xQueueInfo, &data, 0);
        }
    }
    else if (events == 0x8) {
        info data;
        data.val = 0;
        if(gpio == BTN1){
            data.id = 1;
            xQueueSendFromISR(xQueueInfo, &data, 0);
        }
        else if(gpio == BTN2){
            data.id = 2;
            xQueueSendFromISR(xQueueInfo, &data, 0);
        }
        else if(gpio == BTN3){
            data.id = 3;
            xQueueSendFromISR(xQueueInfo, &data, 0);
        }
        else if(gpio == BTN4){
            data.id = 4;
            xQueueSendFromISR(xQueueInfo, &data, 0);
        }
    }
}

void adc_1_task(void *p) {
    adc_init();
    adc_gpio_init(27);

    while (1) {
        uint16_t result;
        adc_select_input(1); // Select ADC input 1 (GPIO27)
        result = adc_read();

        // CÓDIGO AQUI
        info data;
        data.id = 11;
        data.val = result;
        xQueueSend(xQueueInfo, &data, portMAX_DELAY);
        
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void adc_2_task(void *p) {
    adc_init();
    adc_gpio_init(26);

    while (1) {
        uint16_t result;
        adc_select_input(0); // Select ADC input 0 (GPIO26)
        result = adc_read();

        // CÓDIGO AQUI
        info data;
        data.id = 12;
        data.val = result;
        xQueueSend(xQueueInfo, &data, portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void HC06_task2(void *p) {
    uart_init(HC06_UART_ID, HC06_BAUD_RATE);
    gpio_set_function(HC06_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(HC06_RX_PIN, GPIO_FUNC_UART);
    hc06_init("ChanceBall", "1234");

    info data;

    while (true) {
        if(xQueueReceive(xQueueInfo, &data, pdMS_TO_TICKS(100))){
            if(data.id == 1){
                if(data.val == 1){
                    uart_putc_raw(UART_ID, 2);
                    uart_putc_raw(UART_ID, 0);
                    uart_putc_raw(UART_ID, 1);
                    uart_putc_raw(UART_ID, -1); 
                
                    // printf("BTN1 Pressed\n");
                    gpio_put(LED1, 1);

                }
                else{
                    uart_putc_raw(UART_ID, 2);
                    uart_putc_raw(UART_ID, 0);
                    uart_putc_raw(UART_ID, 0);
                    uart_putc_raw(UART_ID, -1); 

                    // printf("BTN1 Released\n");
                    gpio_put(LED1, 0);
                }
            }
            else if(data.id == 2){
                if(data.val == 1){
                    uart_putc_raw(UART_ID, 3);
                    uart_putc_raw(UART_ID, 0);
                    uart_putc_raw(UART_ID, 1);
                    uart_putc_raw(UART_ID, -1); 

                    // printf("BTN2 Pressed\n");
                    gpio_put(LED2, 1);
                }
                else{
                    uart_putc_raw(UART_ID, 3);
                    uart_putc_raw(UART_ID, 0);
                    uart_putc_raw(UART_ID, 0);
                    uart_putc_raw(UART_ID, -1); 

                    // printf("BTN2 Released\n");
                    gpio_put(LED2, 0);
                }
            }
            else if(data.id == 3){
                if(data.val == 1){
                    uart_putc_raw(UART_ID, 4);
                    uart_putc_raw(UART_ID, 0);
                    uart_putc_raw(UART_ID, 1);
                    uart_putc_raw(UART_ID, -1); 

                    // printf("BTN3 Pressed\n");
                    gpio_put(LED3, 1);
                }
                else{
                    uart_putc_raw(UART_ID, 4);
                    uart_putc_raw(UART_ID, 0);
                    uart_putc_raw(UART_ID, 0);
                    uart_putc_raw(UART_ID, -1); 

                    // printf("BTN3 Released\n");
                    gpio_put(LED3, 0);
                }
            }
            else if(data.id == 4){
                if(data.val == 1){
                    uart_putc_raw(UART_ID, 5);
                    uart_putc_raw(UART_ID, 0);
                    uart_putc_raw(UART_ID, 1);
                    uart_putc_raw(UART_ID, -1); 

                    // printf("BTN4 Pressed\n");
                    gpio_put(LED4, 1);
                }
                else{
                    uart_putc_raw(UART_ID, 5);
                    uart_putc_raw(UART_ID, 0);
                    uart_putc_raw(UART_ID, 0);
                    uart_putc_raw(UART_ID, -1); 

                    // printf("BTN4 Released\n");
                    gpio_put(LED4, 0);
                }
            }
            else if(data.id == 11){
                char buffer[50];
                int etapa1 = data.val - 2048;
                double divisor = 2047/255;
                int etapa2 = etapa1 / divisor;

                if(etapa2 > -30 && etapa2 < 30){
                    etapa2 = 0;
                }
                sprintf(buffer, "ADC 1: %d\n", etapa2);
                // printf(buffer);

                uint8_t msb = (etapa2 >> 8) & 0xFF;
                uint8_t lsb = etapa2 & 0xFF;

                uart_putc_raw(UART_ID, 0);
                uart_putc_raw(UART_ID, msb);
                uart_putc_raw(UART_ID, lsb);
                uart_putc_raw(UART_ID, -1); 

            }
            else if(data.id == 12){
                char buffer[50];
                int etapa1 = data.val - 2048;
                double divisor = 2047/255;
                int etapa2 = etapa1 / divisor;

                if(etapa2 > -30 && etapa2 < 30){
                    etapa2 = 0;
                }
                sprintf(buffer, "ADC 2: %d\n", etapa2);
                // printf(buffer);

                uint8_t msb = (etapa2 >> 8) & 0xFF;
                uint8_t lsb = etapa2 & 0xFF;

                uart_putc_raw(UART_ID, 1);
                uart_putc_raw(UART_ID, msb);
                uart_putc_raw(UART_ID, lsb);
                uart_putc_raw(UART_ID, -1); 
            }

            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
}

// void HC06_task(void *p) {
//     uart_init(HC06_UART_ID, HC06_BAUD_RATE);
//     gpio_set_function(HC06_TX_PIN, GPIO_FUNC_UART);
//     gpio_set_function(HC06_RX_PIN, GPIO_FUNC_UART);
//     hc06_init("aps2_2D3Y", "4242");

//     while (true) {
//         uart_puts(HC06_UART_ID, "OLAAA ");
//         vTaskDelay(pdMS_TO_TICKS(100));
//     }
// }

int main() {
    stdio_init_all();

    // printf("Start bluetooth task\n");

    xQueueInfo = xQueueCreate(32, sizeof(info));


    // Initialize GPIO pins for buttons
    gpio_init(BTN1);
    gpio_set_dir(BTN1, GPIO_IN);
    gpio_pull_up(BTN1);
    gpio_set_irq_enabled_with_callback(BTN1, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    gpio_init(BTN2);
    gpio_set_dir(BTN2, GPIO_IN);
    gpio_pull_up(BTN2);
    gpio_set_irq_enabled(BTN2, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);

    gpio_init(BTN3);
    gpio_set_dir(BTN3, GPIO_IN);
    gpio_pull_up(BTN3);
    gpio_set_irq_enabled(BTN3, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);

    gpio_init(BTN4);
    gpio_set_dir(BTN4, GPIO_IN);
    gpio_pull_up(BTN4);
    gpio_set_irq_enabled(BTN4, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);

    // Initialize GPIO pins for LEDs
    gpio_init(LED1);
    gpio_set_dir(LED1, GPIO_OUT);

    gpio_init(LED2);
    gpio_set_dir(LED2, GPIO_OUT);

    gpio_init(LED3);
    gpio_set_dir(LED3, GPIO_OUT);

    gpio_init(LED4);
    gpio_set_dir(LED4, GPIO_OUT);

    xTaskCreate(adc_1_task, "ADC_Task 1", 4096, NULL, 1, NULL);
    xTaskCreate(adc_2_task, "ADC_Task 2", 4096, NULL, 1, NULL);
    xTaskCreate(HC06_task2, "UART_Task 1", 4096, NULL, 1, NULL);

    vTaskStartScheduler();

    while (true)
        ;
}
