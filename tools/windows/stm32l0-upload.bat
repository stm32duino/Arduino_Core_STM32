@echo off
set count=1
:wait
    "%~dp0\dfu-util.exe" -l -d 0483:df11 | findstr "Found" >NUL 2>&1
    if %errorlevel% == 0 ( 
	"%~dp0\dfu-util.exe" -d %1:%2,0x0483:0xdf11 -a 0 -s 0x08000000:leave -D %3
    ) else (
        if %count% gtr 10 goto break 
        echo %count%
        set /A count+=1
        ping -n 1 127.0.0.1 >NUL
        goto :wait
    )
)

:break



