echo "NEV-2021"
timeout /t 5
start "" C:\Users\thesi\Desktop\NEV-2021\Debug\NEV_2021.exe -in:"C:\Users\thesi\Desktop\NEV-2021\NEV_2021\test.txt"  -out:"C:\Users\thesi\Desktop\NEV-2021\NEVGeneration\NEVGeneration\asm.asm" m l i
echo (get-content -path C:\Users\thesi\Desktop\NEV-2021\NEVGeneration\NEVGeneration\asm.asm)[-1] | powershell -command -
timeout /t 15
echo "NEV-2021 asm"
start "" C:\Users\thesi\Desktop\NEV-2021\NEVGeneration\NEVGeneration\asm.asm
call C:\Users\thesi\Desktop\NEV-2021\auto\asm.bat
pause