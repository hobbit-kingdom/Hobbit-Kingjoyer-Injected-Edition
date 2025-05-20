@echo off

::Obtain admin rights if system is newer than WinXP
ver | find "6" > nul
if %ERRORLEVEL% == 1 goto WinXP

rem ----------------- obtain admin start -----------------
:obtain_admin
>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"
if '%errorlevel%' NEQ '0' goto UACPrompt
goto gotAdmin

:UACPrompt
echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
set params = %*:"=""
echo UAC.ShellExecute "%~s0", "%params%", "", "runas", 1 >> "%temp%\getadmin.vbs"
"%temp%\getadmin.vbs" && exit /B

:gotAdmin
if exist "%temp%\getadmin.vbs" ( del "%temp%\getadmin.vbs" )
pushd "%CD%" && CD /D "%~dp0"
rem ----------------- obtain admin end -----------------

:WinXP

echo Indeo codec enabler/disabler cmd batch for WinXP, Vista and Win7
echo -----------------------------------------------------------------
echo This batch file will generate .reg files and import them to the 
echo system registry to enable or disable the Indeo codecs for WinXP,
echo Vista and Win7 systems. (Note: WinXP needs at least Service Pack 2)
echo(
echo The codecs are:
echo - Intel Indeo(R) Video R3.2
echo - Intel Indeo(R) Video 4.5
echo - Indeo(R)-video 5.10
echo - Indeo(R) audio software
echo(
echo Disclaimer: Microsoft has disabled the built-in Indeo codecs due to 
echo vulnerabilities.(Microsoft Security Advisory 954157) If you 
echo enable them you are doing so on your own risk.
echo(

:PROMPT1
set /p yesno=Continue (Y/N)?
if /i "%yesno%" NEQ "Y" GOTO EOF

echo Initial cleanup...
del indeo_codecs_enable.reg
del indeo_codecs_disable.reg
echo(

set Version=
for /f "skip=1" %%v in ('wmic os get version') do if not defined Version set Version=%%v
for /f "delims=. tokens=1-3" %%a in ("%Version%") do (
  set Version.Build=%%c
)
:: Windows version numbers 2600=XP, 3790=XP-64bit, 6002=Vista, 7601=Win7
if %Version.Build% == 2600 (GOTO LEGACYWIN)
if %Version.Build% == 3790 (GOTO LEGACYWIN)
if %Version.Build% == 6002 (GOTO LEGACYWIN)
if %Version.Build% == 7601 (GOTO LEGACYWIN)
if %Version.Build% GEQ 9200 (GOTO WIN8)
echo Windows Build %Version.Build% is too old (not supported). Exiting...
pause
exit

:WIN8
echo Windows Build %Version.Build% is newer than Win7 (not supported). Exiting...
pause
exit

:LEGACYWIN
echo Supported Windows Build %Version.Build% detected.
echo Note: To abort at this stage just close the cmd prompt window.
if exist %windir%\syswow64 (GOTO 64BIT) ELSE (GOTO 32BIT)
:64BIT
if exist %windir%\syswow64\ir50_32.dll (GOTO CONT) ELSE (GOTO ABORT)
:CONT
::Start writing the first .reg file
set _tmp=%windir%
set _windir=%_tmp:\=\\%
echo Windows Registry Editor Version 5.00 >> indeo_codecs_enable.reg
echo( >> indeo_codecs_enable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\drivers.desc] >> indeo_codecs_enable.reg
echo "%_windir%\\system32\\ir32_32.dll"="Intel Indeo(R) Video R3.2" >> indeo_codecs_enable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\Drivers32] >> indeo_codecs_enable.reg
echo "vidc.iv32"="%_windir%\\system32\\ir32_32.dll" >> indeo_codecs_enable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\drivers.desc] >> indeo_codecs_enable.reg
echo "%_windir%\\system32\\ir41_32.ax"="Intel Indeo® Video 4.5" >> indeo_codecs_enable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\Drivers32] >> indeo_codecs_enable.reg
echo "vidc.iv41"="%_windir%\\system32\\ir41_32.ax" >> indeo_codecs_enable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\drivers.desc] >> indeo_codecs_enable.reg
echo "%_windir%\\system32\\ir50_32.dll"="Indeo®-video 5.10" >> indeo_codecs_enable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\Drivers32] >> indeo_codecs_enable.reg
echo "vidc.iv50"="%_windir%\\system32\\ir50_32.dll" >> indeo_codecs_enable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\drivers.desc] >> indeo_codecs_enable.reg
echo "%_windir%\\system32\\iac25_32.ax"="Indeo® audio software" >> indeo_codecs_enable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\Drivers32] >> indeo_codecs_enable.reg
echo "msacm.iac2"="%_windir%\\system32\\iac25_32.ax" >> indeo_codecs_enable.reg
::The second .reg file
echo Windows Registry Editor Version 5.00 >> indeo_codecs_disable.reg
echo( >> indeo_codecs_disable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\drivers.desc] >> indeo_codecs_disable.reg
echo "%_windir%\\system32\\ir32_32.dll"=- >> indeo_codecs_disable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\Drivers32] >> indeo_codecs_disable.reg
echo "vidc.iv32"=- >> indeo_codecs_disable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\drivers.desc] >> indeo_codecs_disable.reg
echo "%_windir%\\system32\\ir41_32.ax"=- >> indeo_codecs_disable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\Drivers32] >> indeo_codecs_disable.reg
echo "vidc.iv41"=- >> indeo_codecs_disable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\drivers.desc] >> indeo_codecs_disable.reg
echo "%_windir%\\system32\\ir50_32.dll"=- >> indeo_codecs_disable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\Drivers32] >> indeo_codecs_disable.reg
echo "vidc.iv50"=- >> indeo_codecs_disable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\drivers.desc] >> indeo_codecs_disable.reg
echo "%_windir%\\system32\\iac25_32.ax"=- >> indeo_codecs_disable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\Drivers32] >> indeo_codecs_disable.reg
echo "msacm.iac2"=- >> indeo_codecs_disable.reg

:PROMPT2
set /p question=Do you want to (E)nable or (D)isable the Indeo codecs?
if /i "%question%" NEQ "E" GOTO ENABLE1
cls
reg import indeo_codecs_enable.reg
echo Enabled Indeo codecs in registry...
del indeo_codecs_enable.reg
del indeo_codecs_disable.reg
pause
exit

:ENABLE1
cls
reg import indeo_codecs_disable.reg
echo Disabled Indeo codecs in registry...
del indeo_codecs_disable.reg
del indeo_codecs_enable.reg
pause
exit

:32BIT
if exist %windir%\system32\ir50_32.dll (GOTO CONT2) ELSE (GOTO ABORT)
:CONT2
::Start writing the first .reg file
set _tmp=%windir%
set _windir=%_tmp:\=\\%
echo Windows Registry Editor Version 5.00 >> indeo_codecs_enable.reg
echo( >> indeo_codecs_enable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\drivers.desc] >> indeo_codecs_enable.reg
echo "%_windir%\\system32\\ir32_32.dll"="Intel Indeo(R) Video R3.2" >> indeo_codecs_enable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Drivers32] >> indeo_codecs_enable.reg
echo "vidc.iv32"="%_windir%\\system32\\ir32_32.dll" >> indeo_codecs_enable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\drivers.desc] >> indeo_codecs_enable.reg
echo "%_windir%\\system32\\ir41_32.ax"="Intel Indeo® Video 4.5" >> indeo_codecs_enable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Drivers32] >> indeo_codecs_enable.reg
echo "vidc.iv41"="%_windir%\\system32\\ir41_32.ax" >> indeo_codecs_enable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\drivers.desc] >> indeo_codecs_enable.reg
echo "%_windir%\\system32\\ir50_32.dll"="Indeo®-video 5.10" >> indeo_codecs_enable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Drivers32] >> indeo_codecs_enable.reg
echo "vidc.iv50"="%_windir%\\system32\\ir50_32.dll" >> indeo_codecs_enable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\drivers.desc] >> indeo_codecs_enable.reg
echo "%_windir%\\system32\\iac25_32.ax"="Indeo® audio software" >> indeo_codecs_enable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Drivers32] >> indeo_codecs_enable.reg
echo "msacm.iac2"="%_windir%\\system32\\iac25_32.ax" >> indeo_codecs_enable.reg
::The second .reg file
echo Windows Registry Editor Version 5.00 >> indeo_codecs_disable.reg
echo( >> indeo_codecs_disable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\drivers.desc] >> indeo_codecs_disable.reg
echo "%_windir%\\system32\\ir32_32.dll"=- >> indeo_codecs_disable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Drivers32] >> indeo_codecs_disable.reg
echo "vidc.iv32"=- >> indeo_codecs_disable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\drivers.desc] >> indeo_codecs_disable.reg
echo "%_windir%\\system32\\ir41_32.ax"=- >> indeo_codecs_disable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Drivers32] >> indeo_codecs_disable.reg
echo "vidc.iv41"=- >> indeo_codecs_disable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\drivers.desc] >> indeo_codecs_disable.reg
echo "%_windir%\\system32\\ir50_32.dll"=- >> indeo_codecs_disable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Drivers32] >> indeo_codecs_disable.reg
echo "vidc.iv50"=- >> indeo_codecs_disable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\drivers.desc] >> indeo_codecs_disable.reg
echo "%_windir%\\system32\\iac25_32.ax"=- >> indeo_codecs_disable.reg
echo [HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Drivers32] >> indeo_codecs_disable.reg
echo "msacm.iac2"=- >> indeo_codecs_disable.reg

:PROMPT3
set /p question=Do you want to (E)nable or (D)isable the Indeo codecs?
if /i "%question%" NEQ "E" GOTO ENABLE2
cls
reg import indeo_codecs_enable.reg
echo Enabled Indeo codecs in registry...
del indeo_codecs_enable.reg
del indeo_codecs_disable.reg
pause
exit

:ENABLE2
cls
reg import indeo_codecs_disable.reg
echo Disabled Indeo codecs in registry...
del indeo_codecs_disable.reg
del indeo_codecs_enable.reg
pause
exit

:ABORT
echo ERROR! Proper Indeo codec file not found in system. Aborting...
pause
exit

:EOF
exit
