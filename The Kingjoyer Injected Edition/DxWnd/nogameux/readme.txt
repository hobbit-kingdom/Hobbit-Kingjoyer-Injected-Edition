by dippy dipper, UCyborg, Cthulhu, gho and an extract from several game forums:


So Microsoft has nuked the metadata server for their Games Explorer feature that was part of Win Vista and 7. 
What this means is that old games that have the GameUX shim are trying to connect to the Microsoft server and hanging forever consuming CPU power. 
This hang up would also occure in the past if the computer was not connected to the internet but it is now happening even if connected.

Symptoms related to this problem:

o	Game fails to open, but their processes can be seen in the taskmgr
o	The rundll32.exe process related to gameux.dll spikes up to >50% of CPU usage
o	Running a second copy of the game or renaming the game executable works around it

A possible and probably best method to disable the gameux invocation is suggested by UCyborg: you just have to just tell the Shim Engine to ignore those entries so it doesn't even try invoking GameUX. There are two registry files here, GameUX_DisableShims.reg disables the entries while the other restores the initial state. If particular game has already been launched before importing GameUX_DisableShims.reg, visiting the game's executable properties, selecting Compatibility tab and clicking OK is required for changes to take effect. 
Remember that you may also need to flush the SDB cache with the "sdbinst -c" command (which does the same as visiting the Compatibility tab of the executable) for the registry changes to take effect. 

Another possible method to fix this problem for all games at once is to redirect the gameux service to the localhost, a host that is surely always available and then would never hang the client invocation. You can use the nogameux.reg registry script. This is the registry hack:

[HKEY_CLASSES_ROOT\Local Settings\Software\Microsoft\Windows\GameUX\ServiceLocation]
"Games"="localhost"

Another method is to replace the original gameux.dll with a proxy that never tries to connect to the gameux server and simply returns immediately. In this case you have to locate the gameux.dll file in  %SystemRoot%\system32 or %SystemRoot%\SysWOW64 depending on the OS architecture, then rename it as gameux_orig.dll and copy the proxy gameux.dll where the original file was.