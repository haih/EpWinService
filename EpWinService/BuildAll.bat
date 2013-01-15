if not exist "C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv.exe" goto :VS9Compile

"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" EpWinService80.sln /build "Debug" /project "EpWinService\EpWinService80.vcproj" /projectconfig "Debug"
"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" EpWinService80.sln /build "Release" /project "EpWinService\EpWinService80.vcproj" /projectconfig "Release"

:VS9Compile

if not exist "C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE\devenv.exe" goto :VS10Compile

"C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE\devenv" EpWinService90.sln /build "Debug" /project "EpWinService\EpWinService90.vcproj" /projectconfig "Debug"
"C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE\devenv" EpWinService90.sln /build "Release" /project "EpWinService\EpWinService90.vcproj" /projectconfig "Release"

:VS10Compile

if not exist "C:\Program Files\Microsoft Visual Studio 10.0\Common7\IDE\devenv.exe" goto :VS11Compile

"C:\Program Files\Microsoft Visual Studio 10.0\Common7\IDE\devenv" EpWinService100.sln /build "Debug" /project "EpWinService\EpWinService100.vcxproj" /projectconfig "Debug"
"C:\Program Files\Microsoft Visual Studio 10.0\Common7\IDE\devenv" EpWinService100.sln /build "Release" /project "EpWinService\EpWinService100.vcxproj" /projectconfig "Release"

:VS11Compile

if not exist "C:\Program Files\Microsoft Visual Studio 11.0\Common7\IDE\devenv.exe" goto :Done

"C:\Program Files\Microsoft Visual Studio 11.0\Common7\IDE\devenv" EpWinService110.sln /build "Debug" /project "EpWinService\EpWinService110.vcxproj" /projectconfig "Debug"
"C:\Program Files\Microsoft Visual Studio 11.0\Common7\IDE\devenv" EpWinService110.sln /build "Release" /project "EpWinService\EpWinService110.vcxproj" /projectconfig "Release"


:Done