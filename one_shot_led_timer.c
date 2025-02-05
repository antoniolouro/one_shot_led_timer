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
    //O LED azul é desligado e o alarme do LED vermelho é ativado
    gpio_put(LED_BLUE, 0);
    alarm_red = add_alarm_in_ms(3000, turn_off_red, NULL, false);
    return 0;
}

int64_t turn_off_red(alarm_id_t id, void *user_data) {
    //O LED vermelho é desligado e o alarme do LED verde é ativado
    gpio_put(LED_RED, 0);
    alarm_green = add_alarm_in_ms(3000, turn_off_green, NULL, false);
    return 0;
}

int64_t turn_off_green(alarm_id_t id, void *user_data) {
    //O LED verde é desligado e a flag do timer é desativada, permitindo que o botão volte a ser acionado
    gpio_put(LED_GREEN, 0);
    timer_active = false; // Permite novo acionamento
    return 0;
}

void button_callback(uint gpio, uint32_t events) {
    //testa se o timer não está ativo via flag, se não estiver, a callback do botão pode ser executada
    if (!timer_active) { //não está ativo
        timer_active = true;    // Impede novo acionamento do botão
        gpio_put(LED_BLUE, 1);  // Liga os LEDs
        gpio_put(LED_RED, 1);
        gpio_put(LED_GREEN, 1);
        alarm_blue = add_alarm_in_ms(3000, turn_off_blue, NULL, false); // Liga o alarme que dará o tempo de 3s para desligar os LEDs
                                                                        // iniciando pelo azul
    }
}

int main() {
    stdio_init_all();       // Inicializa a comunicação serial
    
    //configuração dos pinos dos LEDs e do botão
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);   // Habilita o pull-up interno do pino do botão tornando-o ativo em nível baixo

    //ativa a interrupção por borda de descida no botão e registra a função de callback
    gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    
    while (1) {
        //printf("Looping eterno\n");
        sleep_ms(150);
      

    }
    return 0;
}

