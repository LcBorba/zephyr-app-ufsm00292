/* Ficheiro: meu_sensor.c */
#include "meu_sensor.h"

// Esta variável estática guarda o nosso valor "falso"
static float fake_temp = 20.0f;

float get_sensor_temp(void)
{
    // Incrementa a temperatura em 0.5 a cada chamada
    fake_temp += 0.5f;

    // Se a temperatura ficar muito alta, reinicia
    if (fake_temp > 30.0f) {
        fake_temp = 20.0f;
    }

    return fake_temp;
}