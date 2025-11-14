#ifndef APP_H
#define APP_H

#include <zephyr/kernel.h>

// Estrutura de mensagem genérica
typedef struct {
    char tipo[16];
    int valor;
} sensor_msg_t;

#define MSGQ_MAX_MSG 10
#define MSGQ_ALIGN   4

extern struct k_msgq sensor_msgq;

// Protótipos das threads
void data_center_thread(void *, void *, void *);
void sensor_temp_thread(void *, void *, void *);
void sensor_lux_thread(void *, void *, void *);
void sensor_humidity_thread(void *, void *, void *);

#endif
