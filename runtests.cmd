@echo off
set TMPRESULT=.\result
cd .\testsuite\
mkdir %TMPRESULT%

for %%f in (*.js) do call ..\jscript %%f > %TMPRESULT%\%%f_expect
for %%f in (*.js) do call ..\bin\jual %%f > %TMPRESULT%\%%f_result
for %%f in (*.js) do call :CompareResults %%f

cd ..\
goto :eof

:CompareResults
    set RRESULT=FAIL
    fc %TMPRESULT%\%1_expect %TMPRESULT%\%1_result | find "FC: no differences encountered" > nul:
    if %ERRORLEVEL%==0 set RRESULT=PASS
    echo Result: %RRESULT% - %1
goto:eof
