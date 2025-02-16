#ifndef INIT_PWM_H
#define INIT_PWM_H

#include "hardware/pwm.h" // Biblioteca para controle de PWM no RP2040
#include "pico/stdlib.h"  // Biblioteca padrão do Raspberry Pi Pico

#define LED_BLUE 12
#define LED_RED 13
#define DIVISOR_PWM 16.0f                     // Divisor fracional do clock para o PWM
const uint16_t PERIOD = 4096;                 // Período do PWM (valor máximo do contador)
uint16_t led_blue_level, led_red_level = 100; // Inicialização dos níveis de PWM para os LEDs
uint slice_led_blue, slice_led_red;           // Variáveis para armazenar os slices de PWM correspondentes aos LEDs

// Função para configurar o PWM de um LED (genérica para azul e vermelho)
void setup_pwm_led(uint led, uint *slice, uint16_t level)
{
    gpio_set_function(led, GPIO_FUNC_PWM); // Configura o pino do LED como saída PWM
    *slice = pwm_gpio_to_slice_num(led);   // Obtém o slice do PWM associado ao pino do LED
    pwm_set_clkdiv(*slice, DIVISOR_PWM);   // Define o divisor de clock do PWM
    pwm_set_wrap(*slice, PERIOD);          // Configura o valor máximo do contador (período do PWM)
    pwm_set_enabled(*slice, true);         // Habilita o PWM no slice correspondente ao LED
}

#endif