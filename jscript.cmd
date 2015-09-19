@echo off
/* 2>nul:
rem  Copyright 2015 Sajon Oso
rem  This batch file runs the Windows Scripting Host (WSH) and executes the source file passed as the first argument
rem  The embedded script loads a library file (jual_compat.js) which will make the WSH engine compatible with JualScript
rem  This compatibility script can be modified for other javascript engines as well like NodeJS.

set JSCRIPTOUT=tmp.jsz
echo /* > %JSCRIPTOUT%
type %~f0 >> %JSCRIPTOUT%
set TARGETSCRIPT=NUL
if EXIST %1 set TARGETSCRIPT=%1
if NOT %TARGETSCRIPT%==NUL (
  type %TARGETSCRIPT% >> %JSCRIPTOUT%
  cscript /nologo /E:jscript %JSCRIPTOUT% %*
  rem del %JSCRIPTOUT%
)
goto :eof
*/



// ## define function to load a library
function includeJS (filename) {
    var fso = new ActiveXObject ("Scripting.FileSystemObject");
    if (!fso.FileExists(filename)) filename = "../" + filename;
    if (!fso.FileExists(filename)) filename = "../bin/" + filename;
    var fileStream = fso.openTextFile (filename);
    var fileData = fileStream.readAll();
    fileStream.Close();
    return fileData;
}

eval(includeJS("jscript2jual.js"));































































// To help debug code when running jscript with this wrapper file, simply subtract the reported error line number by 100
// For the calculation to work this line should be line 99 with a terminating new line character.
