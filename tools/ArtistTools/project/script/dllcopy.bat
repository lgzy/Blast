REM the TODIR (destination folder) should NOT contain a trailing '\', this script will append it

SETLOCAL

SET PLATFORMENDING=%1
SET TODIR=%2
SET NXDIR=%3
SET PXSHAREDDIR=%4
SET APEXXDIR=%5
SET NVTXDIR=%6
SET GLDIR=%7
SET WINSDKDIR=%8
SET SHAREDDIR=%9

echo Copy %PLATFORMENDING%
echo TARGET = %TODIR%
echo NXDIR  = %NXDIR%
echo PXSHAREDDIR = %PXSHAREDDIR%
echo APEXXDIR = %APEXXDIR%
echo NVTXDIR = %NVTXDIR%
echo GLDIR = %GLDIR%
echo SHAREDDIR = %SHAREDDIR%



IF "%1"=="" GOTO ARGUMENT_ERROR

CALL :UPDATE_TARGET %NXDIR% PhysXCore.dll
CALL :UPDATE_TARGET %NXDIR% PhysXCoreDEBUG.dll
CALL :UPDATE_TARGET %NXDIR% PhysXCooking.dll
CALL :UPDATE_TARGET %NXDIR% PhysXCookingDEBUG.dll
CALL :UPDATE_TARGET %NXDIR% PhysXLoader.dll
CALL :UPDATE_TARGET %NXDIR% PhysXLoaderDEBUG.dll

CALL :UPDATE_TARGET %NXDIR% PhysXDevice.dll
CALL :UPDATE_TARGET %NXDIR% cudart*.dll

CALL :UPDATE_TARGET %NXDIR% PhysX3_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3CHECKED_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3DEBUG_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3PROFILE_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3Common_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3CommonCHECKED_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3CommonDEBUG_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3CommonPROFILE_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3CharacterKinematic_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3CharacterKinematicCHECKED_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3CharacterKinematicDEBUG_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3CharacterKinematicPROFILE_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3Cooking_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3CookingCHECKED_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3CookingDEBUG_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3CookingPROFILE_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3Gpu_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3GpuCHECKED_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3GpuDEBUG_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %NXDIR% PhysX3GpuPROFILE_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %PXSHAREDDIR% PxFoundation_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %PXSHAREDDIR% PxFoundationCHECKED_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %PXSHAREDDIR% PxFoundationPROFILE_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %PXSHAREDDIR% PxFoundationDEBUG_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %PXSHAREDDIR% PxPvdSDK_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %PXSHAREDDIR% PxPvdSDKCHECKED_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %PXSHAREDDIR% PxPvdSDKDEBUG_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %PXSHAREDDIR% PxPvdSDKPROFILE_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %APEXXDIR% APEX_DestructibleDEBUG_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %APEXXDIR% APEX_DestructiblePROFILE_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %APEXXDIR% APEX_Destructible_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %APEXXDIR% APEX_LegacyDEBUG_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %APEXXDIR% APEX_LegacyPROFILE_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %APEXXDIR% APEX_Legacy_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %APEXXDIR% APEX_LoaderDEBUG_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %APEXXDIR% APEX_LoaderPROFILE_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %APEXXDIR% APEX_Loader_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %APEXXDIR% ApexFrameworkDEBUG_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %APEXXDIR% ApexFrameworkPROFILE_%PLATFORMENDING%.dll
CALL :UPDATE_TARGET %APEXXDIR% ApexFramework_%PLATFORMENDING%.dll
IF "%PLATFORMENDING%"=="x64" (
CALL :UPDATE_TARGET %GLDIR%\samples\bin\win64 AntTweakBar64.dll
CALL :UPDATE_TARGET %GLDIR%\samples\bin\win64 Assimp64.dll
CALL :UPDATE_TARGET %WINSDKDIR%\bin\x64 d3dcompiler_47.dll
CALL :UPDATE_TARGET %SHAREDDIR%\shadow_lib GFSDK_ShadowLib_DX11.win64.dll
CALL :UPDATE_TARGET %SHAREDDIR%\hbao GFSDK_SSAO_D3D11.win64.dll
) ELSE (
CALL :UPDATE_TARGET %GLDIR%\samples\bin\win32 AntTweakBar.dll
CALL :UPDATE_TARGET %GLDIR%\samples\bin\win32 Assimp32.dll
CALL :UPDATE_TARGET %WINSDKDIR%\bin\x86 d3dcompiler_47.dll
CALL :UPDATE_TARGET %SHAREDDIR%\shadow_lib GFSDK_ShadowLib_DX11.win32.dll
CALL :UPDATE_TARGET %SHAREDDIR%\hbao GFSDK_SSAO_D3D11.win32.dll
)

CALL :UPDATE_TARGET %NVTXDIR% nvToolsExt*.dll



ENDLOCAL
GOTO END


REM ********************************************
REM NO CALLS TO :UPDATE_TARGET below this line!!
REM ********************************************

:UPDATE_TARGET
IF NOT EXIST %1\%2 (
	REM ECHO File doesn't exist %1\%2
) ELSE (
	REM echo updating %2
  REM echo XCOPY "%1\%2" "%TODIR%"
	XCOPY "%1\%2" "%TODIR%" /D /Y
)
GOTO END

:ARGUMENT_ERROR
ECHO ERROR: too few arguments to dllcopy.bat (need PhysXBinDir ApexBinDir)

:END
