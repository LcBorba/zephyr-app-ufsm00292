#include <zephyr/kernel.h>
#include <stdlib.h>
#include <string.h>
#include "app.h"

void sensor_temp_thread(void *a, void *b, void *c)
{
    sensor_msg_t msg;

    while (1) {
        msg.valor = 20 + rand() % 10; // 20°C a 29°C
        strcpy(msg.tipo, "TEMP");
        k_msgq_put(&sensor_msgq, &msg, K_NO_WAIT);
        k_msleep(1000);
    }
}
