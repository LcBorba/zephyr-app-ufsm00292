10/10 - instalação zephyrRTOS
	instalação Renode
	testes zephyrRTOS+Renode, samr21

17/10 - Estudos: ZephyrRTOS
				 componentes samr21
				 
24/10
O projeto consiste em um sistema embarcado de detecção de quedas para idosos, utilizando o BNO055 Xplained Pro Extension Kit. O código, realiza a leitura contínua dos dados reais da IMU (aceleração, giroscópio e orientação) e aplica um algoritmo de detecção baseado em picos de aceleração e mudanças bruscas de orientação para identificar quedas. Quando uma queda é detectada, o sistema aciona um alerta local, envia uma notificação via Bluetooth.

Estrutura do código:

 ├── Inclusões e Definições
 │      ├── Inclui bibliotecas do Zephyr (kernel, sensor, bluetooth, logging, etc.)
 │      └── Define constantes:
 │             ├── THRESH_IMPACT → aceleração mínima para detectar impacto
 │             ├── THRESH_ANGLE  → variação angular para detectar mudança brusca
 │             ├── IMMOBILE_TIME → tempo parado após o impacto
 │             └── IMU_POLL_MS   → intervalo entre leituras do BNO055
 │      
 │
 ├── Estruturas de Dados
 │      └── imu_sample_t
 │             └── Armazena leituras reais do BNO055 (ax, ay, az, pitch, roll)
 │
 ├── Funções de Leitura e Comunicação
 │      ├── imu_read(sample)
 │      │      ├── Lê dados do sensor BNO055
 │      │      └── Atualiza estrutura imu_sample_t
 │      ├── ble_notify_fall(evt)
 │      │      └── Envia notificação com dados da queda
 │      └── ui_alert_fall()
 │             └── Mostra alerta local
 │
 ├── Funções Auxiliares
 │      ├── calculate_magnitude(ax, ay, az)
 │      │      └── Calcula o módulo da aceleração total
 │      └── detect_fall(sample, evt)
 │             ├── Analisa sequência de leituras da IMU
 │             ├── Verifica pico de aceleração e variação angular
 │             ├── Confirma imobilidade após impacto
 │             └── Retorna true se padrão de queda for identificado
 │
 ├── Inicialização
 │      └── setup()
 │             ├── Inicializa subsistemas (sensor BNO055, BLE, UI)
 │             ├── Exibe mensagem de inicialização
 │             └── Prepara o sistema para o loop principal
 │
 ├── Loop Principal (main)
 │      ├── Executa setup()
 │      ├── Inicia laço contínuo:
 │      │      ├── Lê dados da IMU (imu_read)
 │      │      ├── Analisa dados (detect_fall)
 │      │      ├── Se houve queda:
 │      │      │      ├── Mostra alerta local (ui_alert_fall)
 │      │      │      └── Envia notificação (ble_notify_fall)
 │      │      └── Aguarda próximo ciclo de leitura (k_msleep(IMU_POLL_MS))
 │      └── Repete indefinidamente
 │
 └── Fim do Programa



 14/11
 Implementação lógica do main (sem integração)


