# one_shot_led_timer

## Tarefa 2 da aula síncrona de 29/01/2025

O objetivo é criar uma aplicação de timer de disparo único, que irá desligar três leds sequencialmente em um intervalo de 3 segundos entre cada desligamento.

A interrupção gerada pelo apertar de um botão inicia todo o processo: Os três leds são ligados, o timer é acionado e se inicia o processo de desligamento ditado pelo timer.

A função de callback relacionada ao botão executa as seguintes tarefas:
1) Testa um flag para saber se o botão pode ser usado, isto é, se o timer já terminou de trabalhar.
2) Seta a flag para informar que timer está ativo e botão não pode ser usado
3) Acende os três leds
4) Inicia o timer para contar 3 segundos e chamar a função para desligar o led azul.
        5) A função desliga o led azul e aciona o timer em 3 segundos e chama a função para desligar o led vermelho
               6) A função desliga o led vermelho e aciona o timer em 3 segundos e chama a função para desligar o led verde
                       7) A função desliga o led verde e zera o flag, reabilitando o uso do botão. Daí todo o processo pode ser repetido.

Uma explicação um pouco mais detalhada está nos comentários do programa e no vídeo demonstrativo abaixo.

## Vídeo Demonstrativo 

Confira o vídeo no link abaixo:

[![Assista no YouTube](https://img.youtube.com/vi/EFkrt-PylOI/maxresdefault.jpg)](https://youtu.be/EFkrt-PylOI)
