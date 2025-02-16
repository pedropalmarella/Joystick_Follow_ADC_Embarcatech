# LEDs RGB e Display SSD1306 com Joystick + PWM

Este projeto utiliza o microcontrolador **RP2040** para controlar dois **LEDs RGB**, exibir um **quadrado em um display SSD1306** e responder a um **joystick** para movimentar o quadrado e controlar a intensidade dos LEDs. Além disso, o projeto implementa um botão para alternar o estado de um LED verde e modificar a borda do display, bem como um botão adicional para ativar ou desativar o PWM dos LEDs.

### Vídeo de apresentação: https://www.youtube.com/watch?v=t50Sv5OA47g
### Funcionalidades Implementadas

#### Controle de LEDs RGB
- **LED Azul**: O brilho do LED azul é controlado pelo eixo Y do joystick. 
  - Quando o joystick está na posição central (valor 2048), o LED azul permanece apagado.
  - À medida que o joystick é movido para cima (valores menores) ou para baixo (valores maiores), o LED aumenta seu brilho gradualmente, atingindo intensidade máxima nos extremos (0 e 4095).
  
- **LED Vermelho**: O brilho do LED vermelho é controlado pelo eixo X do joystick.
  - Quando o joystick está na posição central (valor 2048), o LED vermelho permanece apagado.
  - Movendo o joystick para a esquerda (valores menores) ou para a direita (valores maiores), o LED aumenta de brilho, sendo mais intenso nos extremos (0 e 4095).

- Ambos os LEDs são controlados via **PWM** para permitir uma variação suave da intensidade luminosa.

#### Controle do Display SSD1306
- Um **quadrado 8x8 pixels** será exibido no display SSD1306, inicialmente centralizado.
- O quadrado se moverá de forma proporcional aos valores capturados pelos eixos X e Y do joystick.

#### Botões do Joystick e Funcionalidades Adicionais
- **Botão do Joystick** (GPIO 22):
  - Alterna o estado do **LED Verde** a cada acionamento.
  - Modifica a borda do display, alternando entre 2 estilos a cada novo acionamento.
  
- **Botão A** (GPIO 5):
  - Ativa ou desativa os **LEDs PWM** a cada acionamento.
  
- **Botão B** (GPIO 6):
  - Entra no modo BOOTSEL

## Desafios do Código
Criar, centralizar o quadrado e delimitar seu movimento dentro do display foi um verdadeiro desafio, pois os valores ADC do joystick são muito altos, então foi necessário fazer uma divisão para que os valores fossem traduzidos corretamente, também foi criado uma condição que delimita o quadrado dentro do display, na qual caso o valor X ou Y passassem do limite, os mesmos seriam lidos como o valor limite.

## Tecnologias Utilizadas

- **Microcontrolador**: Raspberry Pi Pico (RP2040)
- **Linguagem de Programação**: C (usando o **Pico SDK**)
- **Ambiente de Desenvolvimento**: Visual Studio Code (VSCode) com Pico SDK
- **Hardware**:
  - **LED RGB** (pinos GPIO 11, 12, 13)
  - **Botão do Joystick** (GPIO 22)
  - **Joystick** (GPIO 26 e 27)
  - **Botão A** (GPIO 5)
  - **Botão B** (GPIO 6)
  - **Display SSD1306** (via I2C, GPIO 14 e GPIO 15)
