# scripts/flash_openocd_examples.ps1 - tentativas A/B para OpenOCD na SAMD21 Xplained Pro
# Ajuste $OPENOCD_BIN e $OPENOCD_SCRIPTS se instalou em outro lugar.

$OPENOCD_BIN     = "C:\Users\angel\AppData\Roaming\xPacks\openocd\xpack-openocd-0.12.0-7\bin\openocd.exe"
$OPENOCD_SCRIPTS = "C:\Users\angel\AppData\Roaming\xPacks\openocd\xpack-openocd-0.12.0-7\share\openocd\scripts"

cd C:\Users\angel\zephyrproject

# Tentativa A: variar backend + reset sob SRST (testar hid, winusb, libusb)
py -m west flash -r openocd `
  --cmd-pre-init "cmsis_dap_backend hid; adapter speed 50; transport select swd; reset_config srst_only srst_nogate connect_assert_srst" `
  --openocd "$OPENOCD_BIN" `
  --openocd-search "$OPENOCD_SCRIPTS"

# Se ainda falhar, tente com winusb:
# py -m west flash -r openocd `
#   --cmd-pre-init "cmsis_dap_backend winusb; adapter speed 50; transport select swd; reset_config srst_only srst_nogate connect_assert_srst" `
#   --openocd "$OPENOCD_BIN" `
#   --openocd-search "$OPENOCD_SCRIPTS"

# E, por fim, libusb:
# py -m west flash -r openocd `
#   --cmd-pre-init "cmsis_dap_backend libusb; adapter speed 50; transport select swd; reset_config srst_only srst_nogate connect_assert_srst" `
#   --openocd "$OPENOCD_BIN" `
#   --openocd-search "$OPENOCD_SCRIPTS"

# Tentativa B: chip-erase + program (substitua backend conforme driver real)
# & "$OPENOCD_BIN" -s "$OPENOCD_SCRIPTS" `
#   -s "C:\Users\angel\zephyrproject\zephyr\boards\atmel\sam0\samd21_xpro\support" `
#   -f "C:\Users\angel\zephyrproject\zephyr\boards\atmel\sam0\samd21_xpro\support\openocd.cfg" `
#   -c "cmsis_dap_backend hid; adapter speed 50; transport select swd; init; targets; at91samd chip-erase; reset halt; program C:/Users/angel/zephyrproject/build/zephyr/zephyr.hex verify reset exit"
