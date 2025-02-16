#include <stdio.h>        
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/font.h"
#include "init_i2c.h"
#include "init_pwm.h"
#include "init_adc_gpio.h"
#include "pico/stdlib.h"  
#include "pico/bootrom.h"

#define DEBOUNCE_TIME 200000 // 200ms em us de debounce
uint32_t last_time = 0;      // captura o tempo do ultimo acionamento do botão para o debounce

volatile bool estado_led_pwm = true; //variavel para alterar o estado dos leds PWM

// Função de interrupção para todos os botões
void btns_callback(uint gpio, uint32_t events)
{
    uint32_t current_time = to_us_since_boot(get_absolute_time()); // captura o momento do acionamento e converte para microsegundos
    if (current_time - last_time > DEBOUNCE_TIME)                  // Verifica se ja passou o tempo do debounce para acionamento novamente do botao
    {
        if (gpio == BTN_A)
        {
            estado_led_pwm = !estado_led_pwm;
        }
        else if (gpio == BTN_B)
        {
            reset_usb_boot(0, 0);
        }
        else if (gpio == SWITCH)
        {
            gpio_put(LED_GREEN, !gpio_get(LED_GREEN));
            cor = !cor;
            ssd1306_fill(&ssd, !cor); // Limpa o display
        }
        last_time = current_time; // Atualiza o tempo para o debounce
    }
}

// Função de configuração geral
void setup()
{
    stdio_init_all();
    init_i2c();                                         
    setup_joystick_btns();                                    
    setup_pwm_led(LED_BLUE, &slice_led_blue, led_blue_level); 
    setup_pwm_led(LED_RED, &slice_led_red, led_red_level);    
}

int main()
{
    uint16_t valor_X, valor_Y; 
    setup();                             
    //interrupções dos botoes A, B e Joystick
    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, btns_callback);
    gpio_set_irq_enabled_with_callback(BTN_B, GPIO_IRQ_EDGE_FALL, true, btns_callback);
    gpio_set_irq_enabled_with_callback(SWITCH, GPIO_IRQ_EDGE_FALL, true, btns_callback);

    while (1)
    {
        
        leitura_joystick(&valor_X, &valor_Y);
        //Perceba que a draw_string no arquivo init_i2c.h recebe 2 inteiros (x e y) de 8 bits, porém os valores do joystick
        //são de 16 bits, então apenas metade é recebido e após isso eu divido por valores(28,69) para que o quadrado fique centralizado
        //passo como parâmetro para que o display seja atualizado com as posições corretamente
        atualiza_display(valor_X/28, valor_Y/69);
        //Impressão dos valores para verificação de erros e acompanhar a posição em px do quadrado
        printf("Valor x: %d | Valor Y: %d\n", valor_X, valor_Y);
        
        //Alteração de estado feita pela irq do botao A que altera o estado da "flag"
        if (estado_led_pwm == true)
        {
            //atualizo o DutyCycle dos leds com os valores fornecidos pelo joystick, (basicamente altera a intesidade dos leds)
            pwm_set_gpio_level(LED_BLUE, valor_X); 
            pwm_set_gpio_level(LED_RED, valor_Y);  
        }
        else{
            //atualizo o DutyCycle dos leds com 0, apagando-os
            pwm_set_gpio_level(LED_BLUE, 0);
            pwm_set_gpio_level(LED_RED, 0);
        }

        sleep_ms(100); // Espera 100 ms antes de repetir o ciclo
    }
}
