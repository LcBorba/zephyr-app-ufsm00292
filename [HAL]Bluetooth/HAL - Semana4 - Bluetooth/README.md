

README com **anotações, tentativas e arquivos de configuração** usados para colocar a
**SAMD21 Xplained Pro (ATSAMD21J18A)** falando BLE via **BTLC1000 Xplained Pro**.

> Objetivo: anunciar e trocar dados via **NUS (Nordic UART Service)** no iOS/Windows,
com host BLE no **Zephyr RTOS** e controlador externo **BTLC1000** por **HCI-UART (H:4)**.
Também foi validado iBeacon via **Microchip Studio**.

## Estrutura
```
configs/
  peripheral_nus/
    prj.conf                 # DEFAULT (115200, SEM RTS/CTS)
    prj_full_rtscts.conf     # Alternativa (1M, COM RTS/CTS)
    boards/
      samd21_xpro.overlay            # DEFAULT (115200, SEM RTS/CTS)
      samd21_xpro_full_rtscts.overlay# Alternativa (1M, COM RTS/CTS)

docs/
  troubleshooting.md
  microchip_studio_beacon.md

scripts/
  build.ps1
```

## Hardware
- **Placa base**: SAMD21 Xplained Pro (ATSAMD21J18A) — console via **USB/EDBG**.
- **Módulo BLE**: Atmel/Microchip **BTLC1000 Xplained Pro** no **EXT1**.
- **UART do EXT1**: SERCOM4 (TX=PB08/Pad0, RX=PB09/Pad1).
- **RTS/CTS** (opcional, recomendado para 1 Mbit/s): RTS=PB11(Pad3), CTS=PB10(Pad2). Ideal usar a placa **BTLC1000 XPRO ADP** em modo 4‑wire.

## Zephyr — Sample
Usamos `zephyr/samples/bluetooth/peripheral_nus` (substitui o antigo `peripheral_uart`).

### Build (Windows/PowerShell)
> Ajuste o caminho do workspace conforme seu ambiente.
```powershell
cd C:\Users\angel\zephyrproject
py -m west update
py -m west zephyr-export

# Build limpo usando o sample do Zephyr
py -m west build -b samd21_xpro -p -s zephyr\samples\bluetooth\peripheral_nus

# Gravar (EDBG)
py -m west flash
```

### Teste no iOS
- App **Adafruit Bluefruit Connect** → aba **UART** → conectar no device “Zephyr …”
- Envie texto; o NUS deve ecoar. (Logs locais via USB/EDBG se ativar `CONFIG_PRINTK/LOG`).

## Sobre as DUAS variantes
- **DEFAULT (115200, SEM RTS/CTS)**: mais fácil para validar quando não há cabeamento CTS/RTS.
- **FULL (1 Mbit/s, COM RTS/CTS)**: robusto e recomendado para uso contínuo (requer ligação CTS/RTS).

## Microchip Studio (BluSDK) — iBeacon (opcional)
Em `docs/microchip_studio_beacon.md` está o roteiro que validou o rádio (iBeacon) antes do Zephyr.
