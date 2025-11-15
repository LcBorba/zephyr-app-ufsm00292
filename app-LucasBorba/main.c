#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(fall_detection, LOG_LEVEL_INF);

/* -------------------------------------------------------------
 * DEFINIÇÕES DO SISTEMA
 * ------------------------------------------------------------- */

#define THRESH_IMPACT     20.0f     // aceleração (m/s²) indicando impacto (~2g)
#define THRESH_ANGLE      45.0f     // variação brusca de ângulo em graus
#define IMMOBILE_TIME_MS  1500      // tempo parado após impacto
#define IMU_POLL_MS       100       // intervalo entre leituras da IMU

/* Handler do dispositivo BNO055 – configurado pela outra equipe */
static const struct device *imu_dev;

/* -------------------------------------------------------------
 * ESTRUTURAS DE DADOS
 * ------------------------------------------------------------- */

typedef struct {
    float ax, ay, az;      // aceleração
    float pitch, roll;     // orientação
} imu_sample_t;

typedef struct {
    int64_t timestamp;
    float impact_force;
    float angle_change;
} fall_event_t;

/* -------------------------------------------------------------
 * FUNÇÕES DE LEITURA E COMUNICAÇÃO
 * ------------------------------------------------------------- */

/* Lê os dados reais da IMU (via driver configurado por outra equipe) */
static int imu_read(imu_sample_t *sample)
{
    struct sensor_value accel[3];
    struct sensor_value orient[2];

    if (sensor_sample_fetch(imu_dev) < 0) {
        LOG_ERR("Erro ao coletar amostra da IMU");
        return -1;
    }

    sensor_channel_get(imu_dev, SENSOR_CHAN_ACCEL_XYZ, accel);
    sensor_channel_get(imu_dev, SENSOR_CHAN_ROTATION, orient);

    sample->ax = sensor_value_to_double(&accel[0]);
    sample->ay = sensor_value_to_double(&accel[1]);
    sample->az = sensor_value_to_double(&accel[2]);

    sample->pitch = sensor_value_to_double(&orient[0]);
    sample->roll  = sensor_value_to_double(&orient[1]);

    return 0;
}

/* Envia notificação BLE (stub, integração feita pela outra equipe) */
static void ble_notify_fall(const fall_event_t *evt)
{
    LOG_INF("BLE: Notificação de queda enviada. Impacto=%.2f", evt->impact_force);
    /* Implementação da característica BLE será feita em outro módulo */
}

/* Mostra alerta local (LED, console ou OLED — hardware configurado depois) */
static void ui_alert_fall(void)
{
    LOG_WRN("⚠️  QUEDA DETECTADA!");
}

/* -------------------------------------------------------------
 * FUNÇÕES AUXILIARES
 * ------------------------------------------------------------- */

/* Calcula magnitude total da aceleração */
static float calculate_magnitude(float x, float y, float z)
{
    return sqrtf(x * x + y * y + z * z);
}

/* Algoritmo básico de detecção de queda */
static bool detect_fall(const imu_sample_t *s, fall_event_t *evt)
{
    static float last_pitch = 0.0f;
    static float last_roll  = 0.0f;

    float acc_mag = calculate_magnitude(s->ax, s->ay, s->az);
    float angle_delta = fabsf(s->pitch - last_pitch) + fabsf(s->roll - last_roll);

    last_pitch = s->pitch;
    last_roll  = s->roll;

    /* 1 — Pico de impacto */
    if (acc_mag < THRESH_IMPACT)
        return false;

    /* 2 — Mudança brusca de ângulo */
    if (angle_delta < THRESH_ANGLE)
        return false;

    /* 3 — Imobilidade após impacto */
    k_msleep(IMMOBILE_TIME_MS);
    imu_sample_t still;
    imu_read(&still);
    float still_mag = calculate_magnitude(still.ax, still.ay, still.az);

    if (still_mag > 2.0f)  // ainda está se movendo → falso positivo
        return false;

    /* Preenche dados do evento detectado */
    evt->timestamp = k_uptime_get();
    evt->impact_force = acc_mag;
    evt->angle_change = angle_delta;

    return true;
}

/* -------------------------------------------------------------
 * INICIALIZAÇÃO
 * ------------------------------------------------------------- */

static void setup(void)
{
    LOG_INF("Iniciando sistema de detecção de quedas...");

    imu_dev = device_get_binding("BNO055");  // nome configurado por outra equipe
    if (!imu_dev) {
        LOG_ERR("ERRO: sensor BNO055 não encontrado!");
        return;
    }

    /* Inicialização BLE (stub) */
    bluetooth_enable(NULL);
    LOG_INF("BLE ativado.");

    LOG_INF("Sistema pronto.");
}

/* -------------------------------------------------------------
 * LOOP PRINCIPAL
 * ------------------------------------------------------------- */

int main(void)
{
    setup();

    imu_sample_t sample;
    fall_event_t evt;

    while (1) {

        /* Lê dados da IMU */
        if (imu_read(&sample) == 0) {

            /* Analisa e detecta queda */
            if (detect_fall(&sample, &evt)) {
                ui_alert_fall();
                ble_notify_fall(&evt);
            }
        }

        k_msleep(IMU_POLL_MS);
    }

    return 0;
}
