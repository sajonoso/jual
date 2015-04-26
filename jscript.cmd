@echo off
/* 2>nul:

rem  This batch file runs the Windows Scripting Host (WSH) and executes the source file passed as the first argument
rem  The embedded script implements some functions to make the WSH engine compatible with JualScript

set JSCRIPTOUT=tmp.jsz
echo /* > %JSCRIPTOUT%
type %~f0 >> %JSCRIPTOUT%
set TARGETSCRIPT=NUL
if EXIST %1 set TARGETSCRIPT=%1
if NOT %TARGETSCRIPT%==NUL (
  type %TARGETSCRIPT% >> %JSCRIPTOUT%
  cscript /nologo /E:jscript %JSCRIPTOUT% %*
  del %JSCRIPTOUT%
)
goto :eof
*/


function print(szOut)
{
    var szTmp=szOut;
    if (typeof szOut == 'string') szTmp=szOut.replace(/\n/g,"\r\n");
    if (typeof szOut == 'boolean') szTmp=szOut?"true":"false";
    WScript.echo(szTmp);
};

function charAt(sz,i) {return sz.charAt(i)};
function charCodeAt(sz,i) {return sz.charCodeAt(i)};
function concat() { return Array.prototype.slice.call(arguments).join(""); };
fromCharCode = String.fromCharCode;
function indexOf(sz,p,i) { return sz.indexOf(p,i) };
function join(a,sep) { return a.join(sep) };
function length(obj) {return obj.length};
function replace(sz,s,r) { return sz.replace(s,r) };
function split(sz,sep) { return sz.split(sep) };
function slice(sz,s,e) { return sz.slice(s,e) };
function toLowerCase(sz) { return sz.toLowerCase() };
function toUpperCase(sz) { return sz.toUpperCase() };
function toString(obj,rad) { return obj.toString(rad?rad:10) };

var arg=[]; for (i=0; i<WScript.arguments.length; i++) { arg[i] = WScript.arguments(i); };

