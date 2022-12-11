DirectX Foundations 6.1 SDK

The \DXF directory on this CD contains all DirectX Foundation 
SDK components less DirectMedia.
__________________________________________________________________


Contents:

- Installation
- Updated SDK
- CD Layout
- What's New
- What's Changed
- Known Issues 
- Compiler Support

__________________________________________________________________


INSTALLATION:

To install the DirectX 6.1 SDK and/or Runtime, select "Install DirectX 
Foundation 6.1 SDK" from the main menu or execute setup.exe in the
\DXF directory of the CD.  If you are installing over the top of an
existing MSDN Platform SDK, read the "UPDATED SDK" section of this readme.

You should UNINSTALL PREVIOUS RELEASES of the DirectX SDK prior to 
installing DirectX 6.1 (see UnInstall).  The directory structure and file 
names have changed significantly.  


UnInstall:

To uninstall, use "Add/Remove Programs" from the Control Panel and 
uninstall any previous versions of the DirectX Foundation SDK.

__________________________________________________________________


UPDATED SDK

As with the previous DX6 release, we've tried to integrate better with
the MSDN Platform SDK.  If you have a previous installation of the 
Platform SDK, installation of the DX6.1 Foundation SDK will detect 
this and offer to install to that directory.  Otherwise, you can 
choose to install the SDK wherever you'd like.  

Other major improvements include DirectMusic (see below), more detailed
and accurate documentation and reworked D3DIM samples showing new 
functionality.

__________________________________________________________________


CD LAYOUT

The following is a brief description of the directories found in the \DXF
directory of this CD.  Depending on options specified during installation,
some of these directories can be installed on your hard drive.

\Bin
    High level DirectX applications & tools.
    All can be accessed from the Start menu if "Utilities" are installed.

\Debug
    Debug versions of the DirectX 6.1 DLLs.

\Doc
    Contains documentation for the DirectX APIs.  The latest documentation
    for the DX6.1 is best viewed with HTMLHelp.  The HTMLHelp viewer requires
    installation Internet Explorer 4.0 (IE4) and one active control.  This
    is only required on Win95 installations.  View the readme.txt file in the
    \Extras\msie401\ directory for more information.  If you chose not to 
    install (IE4), you can still view the DX6.1 documentation by accessing 
    the files in DXF\docs\directx6\word.

\Essentls
    DMusProd (Direct Music Producer)
       - Direct Music Producer is the authoring tool for Direct Music.  It
         allows composers to use the interactive and variable resources of 
         DirectMusic along with the consistent sound performance of DLS.  The
         Music Producer setup program and all files are located here.
    DMusProd.jpn (Direct Music Producer with Japanese localized install)
       - This is the same as the previous (DMusProd) folder, however the
         install is localized for Japanese.
 
\Extras
    DMusic
       - Contains a batch file that will install the updated DMusic run-time 
         components on NT5.  See the 'readme' in the same directory for
         operation instructions.
    DSound
       - Voice Manager.  The Voice Manager Property Set specification enables
         advanced voice management for DirectSound3D on supported sound cards.
         This provides easier support of hardware accelerated DirectSound3D.
    DDSPlugin
       - This contains a Photoshop plugin to support import and export of 
         DXTn-compressed textures using the DDS file format.
    DX6 Drivers
       - This directory contains an HTML document that contains links to IHV
         web sites where DX6 drivers can be located.
    Win98
       - For those of you developing on Win98 that would like a complete set
         of DirectX debug DLLs, we have shipped debug DLLs for both 
         DSound and DInput.  The DX6.1 SDK setup will not update these 
         components.  See the \DXF\extras\Win98\Readme.txt for more 
         information.
  
\Include
    contains include files for DirectDraw, Direct3D, DirectSound, 
    DirectInput, DirectPlay and DirectMusic

\Lib
    contains library files for DirectDraw, Direct3D, DirectSound, 
    DirectInput and DirectPlay.
    *.LIB : COFF libraries (used by Microsoft Visual C++ 2.0 or higher).
    There is also a sub-directory that contains Borland 11.0 versions 
    of the libraries.

\License
    Text versions of the DirectX SDK and End User License Agreements and 
    the Redistributable License Agreement.

\Redist
    Redistributable versions of the DirectX 6.1 DLLs.

\Samples
    Contains all sample code and sample binaries.   See readme.txt file 
    in each sample's directory for more details.  Most samples can be
    accessed from the Start menu.
	
__________________________________________________________________


WHAT'S NEW:

DirectMusic

This release of DirectX 6.1 contains the final release of DirectMusic. 
The DirectMusic DLLs are automatically installed when you run the SDK setup.

The documentation for the DirectMusic API is included with the DirectX 6.1 
documentation. The DirectMusic sample code is also included as part of the 
DirectX 6.1 SDK.  Both of these options are available in the DX6.1 SDK setup.

DirectMusic Producer, the authoring tool for DirectMusic, is also included 
with this release.  It has a separate install which can be found in the 
\DXF\essentials\DMProducer directory on the DirectX 6.1 CD.  For more 
information on DirectMusic Producer, please see the readme.txt which can be 
found in the same directory as the DirectMusic Producer setup program.

WDM support for DirectMusic is still under construction.

__________________________________________________________________


WHAT'S CHANGED

By far the biggest change is the final release of DirectMusic.  However, we've
taken this opportunity to make some minor modification/bug fixes to other areas
of the API.  These modifications are listed by component below.

DDraw

- Enable AGP Command Buffers
- ModeX fixed for AGP machines


D3DIM

- Improved performance of DX5 RAMP rasterizer.  This is provided by an 
additional file d3dramp.dll which is installed by 6.1 setup.

- Improved support for video memory vertex buffers.

- Improved support for PowerVR usage of Clear2.

- Drivers implementing ValidateDevice can now consider texture format if
required.

- Multitexture stage counting is now more accurate.

- Directional and Spot light types now operate correctly on Pentium II.

- Ramp rasterizer now uses blue channel for gray-scale instead of averaging.
This is for compatibility with earlier releases.

- Vertex fog now works with SPECULARENABLE set to false.

- 16-Bit ramp rasterizer now supports COPY mode.

- New cap bit for textures which are not powers of two.  See DX6.1 
Documentation under "D3DPTEXTURECAPS_NONPOW2CONDITIONAL".


DPlay

- The serial service provider could attempt to send multiple blocks of data
simultaneously, which could cause the connection to be lost.  Now access is
serialized.

- If a client was dropped from a session ungracefully and someone else tried to
join the game before the host timed out that player, all subsequent joins
would fail.  Now joins will succeed again once the host completely times out
all players.

__________________________________________________________________


KNOWN ISSUES

DXMedia

- DirectX Media 6.0 is incompatible with the debug version of DirectX 
Foundation 6.1.  Please use the retail version of DirectX Foundation 
if you intend to use any components of DirectX Media including 
DirectAnimation and DirectTransform.


DMusic

- DirectMusic currently has a problem with MIDI files that do not have
a matched pair of MSB and LSB commands. The MIDI specification requires
that a file always have matching MSB and LSB commands. However, the
DirectMusic team has recently discovered that a sequencer product is
creating MIDI files that contain an MSB but no LSB. When these files are
played in this beta version of DirectMusic, you are likely to not hear
some of the tracks. To solve this problem, use the
GUID_IgnoreBankSelectForGM SetParam call on the segment after loading
the MIDI file into it. This removes the MSB and LSB commands and allows
the file to play properly.

- The DMusic samples will not run on NT5 beta 2.  This is because the DX 
run-time installation cannot update NT5 components.  We have included a
batch file that will update the NT5 DMusic DLLs and allow the DMusic
samples to work.  You will find this in the \DXF\extras\DMusic directory.  


DDraw/D3DIM

- When creating mipmaps, it is illegal to specify a 
DDSURFACEDESC.dwMipMapCount which is greater than the power-of-two
of the smallest of the width or height of the top-level surface. For 
example, a 4x2 mipmap can only have dwMipMapCount=2, not 3. The practical 
implication is that you cannot expect a 4x2 mipmap to generate levels 
which are 2x1, 1x1. DirectDraw will only allow the smallest dimension to 
drop to 1, and won't allow deeper mip levels. 

- Some popular cards cannot create render targets unless color buffers and 
z-buffers are of the same bit depth.  The constraints are:
     16-bit color buffers require 16-bit z-buffer (no stencils available)
     32-bit color buffers require 32-bit z-buffer of which 8 bits can be 
          stencil if desired.
If these conditions are not met, then the calls will fail on either 
CreateDevice or at SetTendertarget().  If you see such behavior and need 
to avoid it, use GetDeviceIdentifier().


DPlay

- The IDirectPlay4A::EnumConnections( ) API will always return single-byte 
character descriptions of the service provider available on the system.  
In order to obtain fully localized multibyte descriptions without having 
to convert your entire application to Unicode, the following procedure 
may be used:

     a) QueryInterface for an IDirectPlay4 interface (Unicode)
     b) call IDirectPlay4::EnumConnections - this will give you Unicode 
        strings
     c) convert each string to ANSI using the Windows WideCharToMultiByte( )
        function
     d) release the IDirectPlay4 interface
     e) continue to use the IDirectPlay4A interface for the rest of your 
        application

     Alternatively, you can QueryInterface for an IDirectPlay3A interface. 
This will return localized multibyte character strings and eliminate step c).

- The latest drivers for US Robotics modems can cause problems hosting 
a session. This is a bug in the drivers.

- Disconnecting the phone line while enumerating modem sessions can 
result in lock ups.


Samples

- The DMusic samples will not run on NT5 beta 2.  This is because the DX 
run-time installation cannot update NT5 components.  We have included a
batch file that will update the NT5 DMusic DLLs and allow the DMusic
samples to work.  You will find this in the \DXF\extras\DMusic directory.  

- The D3DIM samples can be run with the DX6.1 reference rasterizer, however
the required registry key is not set by default.  You can set the proper
registry key by using the files in the \DXF\samples\Multimedia\D3DIM\bin 
directory.  Without the software rasterizer registry key set you will get 
a message suggesting to enable it when first trying DX6.1 specific samples
such as BumpMap.  Because this is a software rasterizer you should expect 
very slow frame rates.

- Depending on the resolution of your desktop and the available amount of video 
memory in your system, there may not be enough video memory for the sample 
textures.  In this case, the D3DIM samples will still run but will not be able 
to display textures (surfaces will be white).  In order to see the textures you 
can lower your desktop resolution or use a display card with more memory.

- A new sample (EnumTex) showing texture enumeration logic and areas that 
developers should be aware of was added to the SDK.  Unfortunately there is 
no reference from the documentation to this sample.

- The DMHook DLL (helper DLL for DMShell) cannot be compiled with Watcom or 
Borland compilers. Watcom and Borland users should use the pre-made DMHook.dll
that is supplied with the SDK sample binaries.

- DInput sample JoyStiMM.exe returns the error message "Direct Input not 
initialized" if the stick attached is not 3 axis.  This will be fixed in a
future release.

- There are miscellaneous issues with some display hardware & drivers.
Please let us know of any problems you encounter and specify whether you
believe it is sample or driver related.

- If you are using Japanese version of Windows, dialog box text in sample
programs may not display Kanji characters. In order to display Kanji
characters, you need to edit .RC file to change the dialog font to 
Japanese font.

- For further information on samples, reference the dxreadme.txt at
<drive:>\(sdk path)\samples\multimedia.


Debug Installation

- You may see files marked as retail in the debug installation (DDrawex.dll,
DSound.vxd).  This is not an error.  It is not necessary for these files to
have debug versions.  

__________________________________________________________________


COMPILER SUPPORT

DX6.1 samples will work with VC++ 4.2 or better, Watcom 11.0 and Borland C 
Builder 3.  We have tried to create a single environment that will work 
with these compilers.  We have included VC project files (.mdp for support 
of VC 4.2) and makefiles that will work with VC, Watcom and Borland.

For instructions on building the samples, open
CDRom:\DXF\samples\multimedia\DXReadme.txt.  In this readme you will find 
sections on How to Build, Notes for VC++ Users, Notes for Watcom Users and 
Notes for Borland Users.  The SDK will install this readme file to 
<drive:>\(sdk path)\samples\multimedia.

Some samples will not compile with Borland and/or Watcom.  This was most
likely due to modifications that would have been required of components
or header files outside of the Di