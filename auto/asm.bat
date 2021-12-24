call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvarsall.bat" x86
ml/c /coff  C:\Users\thesi\Desktop\NEV-2021\NEVGeneration\NEVGeneration\asm.asm
link /OPT:NOREF /DEBUG asm.obj  /SUBSYSTEM:CONSOLE /NODEFAULTLIB:library
call C:\Users\thesi\Desktop\NEV-2021\auto\asm.exe
pause