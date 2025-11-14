# Build + Flash para SAMD21 XPRO usando o sample peripheral_nus
# Uso: clique direito -> Run with PowerShell (ajuste caminhos se necessário)

$workspace = "C:\Users\angel\zephyrproject"
$sample = "zephyr\samples\bluetooth\peripheral_nus"

Set-Location $workspace
py -m west update
py -m west zephyr-export

# Build limpo
py -m west build -b samd21_xpro -p -s $sample

# Gravar via EDBG
py -m west flash
