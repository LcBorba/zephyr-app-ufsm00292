# scripts/atprogram_erase_example.ps1 - erase via Microchip/Atmel Studio (se instalado)

$ATPROGRAM = "C:\Program Files (x86)\Atmel\Studio 7.0\atbackend\atprogram.exe"
& "$ATPROGRAM" -t edbg -i SWD -d atsamd21j18a erase
