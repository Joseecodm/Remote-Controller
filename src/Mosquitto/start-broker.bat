@echo off
REM — Ir al directorio del .bat
cd /d "%~dp0"

echo Iniciando Mosquitto broker local en 192.168.76.32:1883...
REM — Si mosquitto.exe está en tu PATH:
mosquitto -c "%~dp0mosquito.conf" -v

REM — Si no, descomenta y ajusta la ruta:
REM "C:\Program Files\mosquitto\mosquitto.exe" -c "%~dp0mosquito.conf" -v

pause
