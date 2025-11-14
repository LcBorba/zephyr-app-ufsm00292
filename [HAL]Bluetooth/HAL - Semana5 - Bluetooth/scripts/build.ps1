# scripts/build.ps1 - build & flash básicos (ajuste conforme necessidade)
# Uso:
#   pwsh -File scripts/build.ps1

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$ZEPHYR = "C:\Users\angel\zephyrproject"
cd $ZEPHYR

py -m west build -b samd21_xpro -p -s zephyr\samples\bluetooth\peripheral_nus
py -m west flash   # requer OpenOCD instalado/visível
