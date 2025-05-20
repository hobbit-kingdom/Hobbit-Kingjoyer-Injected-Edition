Virtual CD Audio:

This is a proxy with a subset of DxWnd functionalities to just play CD audio tracks.
To use:

Copy to the target program folder the following files:
	winmm.dll 
	winmm.ini 
Copy to the same target folder these files from the DxWnd folder:
	dxwplay.dll
	libogg.dll
	libvorbis.dll
	libvorbisfile.dll
Make a "Music" foder with CD audio track files inside. As for DxWnd CDAudio emulation,
customize "winmm.ini" if necessary (comments inside the file explain how to do that)

BEWARE: If you use Virtual CD Audio (VCDA), the target program MUST NOT BE a target for DxWnd as well.
In such a case, when using VCDA, keep DxWnd turned off or disable hooking or disable "Sound > Virtual CD Audio" flag.
Similarly, when using DxWnd, rename "winmm.dll" in the target folder to disable it.

Additional notes:
On modern Windows operating systems, the "winmm.dll" proxy file will often be ignored and the real system library will be used instead. 
In this case, it is best to use the internal DxWnd CDAudio emulation instead. 
Or if you are comfortable with a hex editor, then one possibility to force the loading of the proxy is to edit the reference to "winmm.dll" in the game's executable to something else like "winm2.dll" and rename the copied "winmm.dll" file similarly.

Also on Windows XP SP3, it appears that using the proxy can cause an error requiring similar renaming action to be taken if a stand alone proxy is to be used.