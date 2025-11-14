# APP_gfschuster - Mini Estação Ambiental (Zephyr RTOS)

Projeto desenvolvido na disciplina **UFSM00292 – Projeto de Sistemas Embarcados**,  
com o objetivo de criar uma aplicação multitarefa usando **Zephyr RTOS** e **QEMU**.

---

## 👤 Autoria
**Gabriel Fronza Schuster**  
Curso: Engenharia de Computação – UFSM  
Professor: Carlos Henrique Barriquello  
Período: 2025/2  

---

## Semana 1 – Configuração do Ambiente Zephyr RTOS

### Objetivo
Instalar e configurar o ambiente **Zephyr RTOS** e **Zephyr SDK**, testar o emulador **QEMU** com o exemplo `hello_world`, e comprovar o funcionamento do ambiente de desenvolvimento.

---

### Ambiente Utilizado
- **Sistema Operacional:** Windows 10 x64  
- **Zephyr SDK:** 0.17.4  
- **Python:** 3.10+  
- **QEMU:** 8.x  
- **Gerenciador:** `west`  
- **Editor:** VS Code  

---

### Passos Realizados

1. Instalação do **Zephyr SDK** e definição das variáveis de ambiente:
   ```bash
   setx ZEPHYR_TOOLCHAIN_VARIANT zephyr
   setx ZEPHYR_SDK_INSTALL_DIR "C:\Users\Gabe\zephyr-sdk-0.17.4"

2. Inicialização do workspace:
    west init -m https://github.com/ufsm-barriquello/zephyr
    west update
    west zephyr-export

3. Compilação e execução do exemplo hello_world:
    cd zephyr/samples/hello_world
    west build -b qemu_x86 --pristine
    qemu-system-x86_64 -machine accel=tcg -nographic -kernel build/zephyr/zephyr.elf

Resultado:
    *** Booting Zephyr OS build ***
    Hello World! qemu_x86

---

##  Semana 2 – Desenvolvimento da Aplicação APP_gfschuster

###  Objetivo
Criar uma aplicação própria no Zephyr RTOS que simula uma mini estação ambiental com sensores de temperatura e luminosidade.  
A aplicação roda em ambiente QEMU, imprimindo leituras periódicas no console.

---

### Estrutura
APP_gfschuster/
├── src/
│ └── main.c
├── prj.conf
├── CMakeLists.txt
└── run_APP_local.ps1

---

### Descrição
A aplicação cria um laço principal que:
- Gera leituras simuladas de **temperatura (20–29 °C)** e **luminosidade (0–1000 lx)**;
- Exibe os valores periodicamente via `printk()`;
- Usa `k_msleep()` para controlar o tempo de amostragem.

Trecho do código:
```c
printk("=== Mini Estação Ambiental Thread - UFSM ===\n");
printk("Temperatura: %d °C | Luminosidade: %d lx\n", temperatura, luz);

Execução:
.\run_APP_gfschuster.ps1

Saída esperada:
*** Booting Zephyr OS build ***
=== Mini Estação Ambiental Thread - UFSM ===
Temperatura: 26 °C | Luminosidade: 415 lx
Temperatura: 28 °C | Luminosidade: 712 lx

---

##  Semana 3 – Ajustes de estrutura de projeto e planejamento

---

### Estrutura do Projeto

APP_gfschuster/
├── include/
│ └── app.h
├── src/
│ ├── main.c
│ ├── sensor_temp.c
│ ├── sensor_lux.c
│ ├── sensor_humidity.c
│ └── data_center.c
├── CMakeLists.txt
├── prj.conf
└── run_APP_local.ps1

---

## Funcionalidade

O projeto simula uma **mini estação ambiental**, composta por três sensores:

| Sensor | Variável | Intervalo de simulação |
|:-------|:----------|:-----------------------|
| Temperatura | 20–29 °C | 1,0 s |
| Luminosidade | 0–999 lx | 1,2 s |
| Umidade | 40–79 % | 1,5 s |

Os valores coletados são enviados via **fila de mensagens (`k_msgq`)** para uma thread central (`data_center`),  
que calcula médias e exibe os resultados em formato de tabela no console.

---

## Threads do Sistema

| Thread | Função | Prioridade |
|:--------|:--------|:------------|
| `sensor_temp_thread` | Gera valores de temperatura | 2 |
| `sensor_lux_thread` | Gera valores de luminosidade | 2 |
| `sensor_humidity_thread` | Gera valores de umidade | 2 |
| `data_center_thread` | Recebe dados, calcula médias e imprime tabela | 1 |

---

## Arquitetura de Comunicação

```mermaid
flowchart LR
    A[Sensor de Temperatura] -->|k_msgq_put| C[Thread Central 🧩]
    B[Sensor de Luminosidade] -->|k_msgq_put| C
    D[Sensor de Umidade] -->|k_msgq_put| C
    C -->|printk (UART/QEMU)| E[Console / Interface Python]