@echo off
if "%1"=="" goto loop
copy pol%1.in pol.in >nul
echo Problem Test
echo Data %1
time<enter
pol
time<enter
fc pol.out pol%1.out
del pol.in
del pol.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end
