#include <zephyr/kernel.h>
#include <stdlib.h>
#include <string.h>
#include "app.h"

void sensor_humidity_thread(void *a, void *b, void *c)
{
    sensor_msg_t msg;

    while (1) {
        msg.valor = 40 + rand() % 40; // 40% a 79%
        strcpy(msg.tipo, "HUM");
        k_msgq_put(&sensor_msgq, &msg, K_NO_WAIT);
        k_msleep(1500);
    }
}
