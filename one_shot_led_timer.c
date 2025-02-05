#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

#define LED_BLUE 11
#define LED_RED 12
#define LED_GREEN 13
#define BUTTON 5

volatile bool timer_active = false;
alarm_id_t alarm_blue, alarm_red, alarm_green;  // IDs dos alarmes

int64_t turn_off_blue(alarm_id_t id, void *user_data);
int64_t turn_off_red(alarm_id_t id, void *user_data);
int64_t turn_off_green(alarm_id_t id, void *user_data);

int64_t turn_off_blue(alarm_id_t id, void *user_data) {
    gpio_put(LED_BLUE, 0);
    alarm_red = add_alarm_in_ms(3000, turn_off_red, NULL, false);
    return 0;
}

int64_t turn_off_red(alarm_id_t id, void *user_data) {
    gpio_put(LED_RED, 0);
    alarm_green = add_alarm_in_ms(3000, turn_off_green, NULL, false);
    return 0;
}

int64_t turn_off_green(alarm_id_t id, void *user_data) {
    gpio_put(LED_GREEN, 0);
    timer_active = false; // Permite novo acionamento
    return 0;
}

void button_callback(uint gpio, uint32_t events) {
    if (!timer_active) {
        timer_active = true;
        gpio_put(LED_BLUE, 1);
        gpio_put(LED_RED, 1);
        gpio_put(LED_GREEN, 1);
        alarm_blue = add_alarm_in_ms(3000, turn_off_blue, NULL, false);
    }
}

int main() {
    stdio_init_all();
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);

    gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    
    while (1) {
      
        sleep_ms(100);
      
    }
}

