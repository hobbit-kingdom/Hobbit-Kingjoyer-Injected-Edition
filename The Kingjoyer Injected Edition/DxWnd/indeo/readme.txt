
    Readme for indeo.ps1 PowerShell script for generating .reg files that 
    enable/disable Indeo codecs.

    The PS script builds the .reg files using the following checks:
    - OS version (must be Windows 8 or later).
    - OS bits (64 or 32) to determine correct registry paths.
    - Existence of the correct file naming for built-in indeo codec files.
    - Determines Windows installation drive letter.

    Indeo Video codecs were commonly used by old games from the 90's and early 2000's. 
    These codecs come with Windows but have been disabled by default since 2009 by 
    Microsoft due to security concerns. The .reg files can be used to enable or disable 
    the built-in Windows Indeo codecs.

    The codecs are:
    Intel Indeo(R) Video R3.2
    Intel Indeo® Video 4.5
    Indeo®-video 5.10
    Indeo® audio software

    Warning:
    If you have already installed third party codec packs to handle IndeoVideo playback 
    these registry changes might not work or might produce unwanted results.

    Disclaimer:
    You are enabling the codecs under your own risk understanding that a malicious video 
    file might take advantage of the IndeoCodec vulnerabilities.

    See the Microsoft 2009 article regarding reasons for disabling the Indeo codecs here:
    https://support.microsoft.com/en-us/topic/microsoft-security-advisory-vulnerabilities-in-the-indeo-codec-could-allow-remote-code-execution-december-8-2009-680127c6-f4fd-e533-b641-6ab3a25fb4f4

    And the Microsoft Security Advisory 954157:
    https://learn.microsoft.com/en-us/security-updates/securityadvisories/2009/954157

    NOTE:
    For older than Win8 versions of Windows there is a batch file version in the legacy folder.
