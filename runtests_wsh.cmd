@echo off
set TMPRESULT=.\result
cd .\testsuite\

echo Clearing Results
rmdir /s /q %TMPRESULT%
ping -n 1 -w 1000 1.2.3.4 >nul:
mkdir %TMPRESULT%
ping -n 1 -w 1000 1.2.3.4 >nul:
echo Running Tests

for %%f in (*.js) do call ..\jscript %%f "parm 1" parm2 parm3 > %TMPRESULT%\%%f_expect
for %%f in (*.js) do call ..\bin\jual %%f "parm 1" parm2 parm3 > %TMPRESULT%\%%f_result
for %%f in (*.js) do call :CompareResults %%f

cd ..\
goto :eof

:CompareResults
    set RRESULT=FAIL
    fc %TMPRESULT%\%1_expect %TMPRESULT%\%1_result | find "FC: no differences encountered" > nul:
    if %ERRORLEVEL%==0 set RRESULT=PASS
    echo Result: %RRESULT% - %1
goto:eof
