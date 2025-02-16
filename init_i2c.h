#ifndef INIT_I2C_H
#define INIT_I2C_H

#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
ssd1306_t ssd;
volatile bool cor = true;

void init_i2c()
{
    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);                    // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);                    // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA);                                        // Pull up the data line
    gpio_pull_up(I2C_SCL);                                        // Pull up the clock line
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd);                                         // Configura o display
    ssd1306_send_data(&ssd);                                      // Envia os dados para o display

    // Limpa o display. O display inicia com todos os pixels DESLIGADOS.
    //ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
}

void atualiza_display(uint16_t X, uint16_t Y) // atualiza o display com o caractere inserido pelo usuario
{
    ssd1306_fill(&ssd, cor);
    ssd1306_rect(&ssd, 3, 3, 122, 58, !cor, cor);
    // verifica posição X e Y para o quadrado não passar dos limites da tela
    if (X > 121)
    {
        X = 121;
    }
    if (Y > 56)
    {
        Y = 56;
    }
    ssd1306_draw_string(&ssd, "*", X, Y); // Desenha o quadrado com as posições X e Y dos valores do joystick, anteriormente tratados para o limite da tela
    ssd1306_send_data(&ssd);
}

#endif