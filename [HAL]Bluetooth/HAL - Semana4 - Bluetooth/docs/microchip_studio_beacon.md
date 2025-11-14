# Microchip Studio — iBeacon (BluSDK)

Fluxo usado para validar rádio BLE do kit antes do Zephyr.

1) Abrir **Microchip Studio 7**; conectar a SAMD21 via **USB/EDBG**.
2) `File -> New -> Example Project...` e escolher o **iBeacon** do BluSDK (SAMD21 + BTLC1000).
3) `Device = ATSAMD21J18A`, `Tool = EDBG`.
4) Compilar e gravar:
   - `Tools -> Device Programming -> EDBG -> Memories` -> selecionar `.elf/.hex` -> `Program`.
   - Ou `Debug -> Start Without Debugging` (compila + grava).
5) Abrir terminal serial (VCOM do EDBG) a **115200 8N1**.
6) Pressionar **SW0** na placa para iniciar/parar a publicidade iBeacon.
7) No iPhone, usar app de scanner BLE (nRF Connect/Bluefruit) e ver Manufacturer Data **0x004C (Apple)**.
8) Personalização: ajustar UUID/Major/Minor/TxPower no código do exemplo e regravar.
