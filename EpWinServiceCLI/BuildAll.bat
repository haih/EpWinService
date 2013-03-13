if not exist "C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv.exe" goto :VS9Compile

"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" EpWinServiceCLI80.sln /build "Debug" /project "EpWinServiceCLI\EpWinServiceCLI80.vcproj" /projectconfig "Debug"
"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" EpWinServiceCLI80.sln /build "Release" /project "EpWinServiceCLI\EpWinServiceCLI80.vcproj" /projectconfig "Release"
"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" EpWinServiceCLI80.sln /build "Debug Unicode" /project "EpWinServiceCLI\EpWinServiceCLI80.vcproj" /projectconfig "Debug Unicode"
"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\devenv" EpWinServiceCLI80.sln /build "Release Unicode" /project "EpWinServiceCLI\EpWinServiceCLI80.vcproj" /projectconfig "Release Unicode"

:VS9Compile

if not exist "C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE\devenv.exe" goto :VS10Compile

"C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE\devenv" EpWinServiceCLI90.sln /build "Debug" /project "EpWinServiceCLI\EpWinServiceCLI90.vcproj" /projectconfig "Debug"
"C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE\devenv" EpWinServiceCLI90.sln /build "Release" /project "EpWinServiceCLI\EpWinServiceCLI90.vcproj" /projectconfig "Release"
"C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE\devenv" EpWinServiceCLI90.sln /build "Debug Unicode" /project "EpWinServiceCLI\EpWinServiceCLI90.vcproj" /projectconfig "Debug Unicode"
"C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE\devenv" EpWinServiceCLI90.sln /build "Release Unicode" /project "EpWinServiceCLI\EpWinServiceCLI90.vcproj" /projectconfig "Release Unicode"

:VS10Compile

if not exist "C:\Program Files\Microsoft Visual Studio 10.0\Common7\IDE\devenv.exe" goto :VS11Compile

"C:\Program Files\Microsoft Visual Studio 10.0\Common7\IDE\devenv" EpWinServiceCLI100.sln /build "Debug" /project "EpWinServiceCLI\EpWinServiceCLI100.vcxproj" /projectconfig "Debug"
"C:\Program Files\Microsoft Visual Studio 10.0\Common7\IDE\devenv" EpWinServiceCLI100.sln /build "Release" /project "EpWinServiceCLI\EpWinServiceCLI100.vcxproj" /projectconfig "Release"
"C:\Program Files\Microsoft Visual Studio 10.0\Common7\IDE\devenv" EpWinServiceCLI100.sln /build "Debug Unicode" /project "EpWinServiceCLI\EpWinServiceCLI100.vcxproj" /projectconfig "Debug Unicode"
"C:\Program Files\Microsoft Visual Studio 10.0\Common7\IDE\devenv" EpWinServiceCLI100.sln /build "Release Unicode" /project "EpWinServiceCLI\EpWinServiceCLI100.vcxproj" /projectconfig "Release Unicode"

:VS11Compile

if not exist "C:\Program Files\Microsoft Visual Studio 11.0\Common7\IDE\devenv.exe" goto :Done

"C:\Program Files\Microsoft Visual Studio 11.0\Common7\IDE\devenv" EpWinServiceCLI110.sln /build "Debug" /project "EpWinServiceCLI\EpWinServiceCLI110.vcxproj" /projectconfig "Debug"
"C:\Program Files\Microsoft Visual Studio 11.0\Common7\IDE\devenv" EpWinServiceCLI110.sln /build "Release" /project "EpWinServiceCLI\EpWinServiceCLI110.vcxproj" /projectconfig "Release"
"C:\Program Files\Microsoft Visual Studio 11.0\Common7\IDE\devenv" EpWinServiceCLI110.sln /build "Debug Unicode" /project "EpWinServiceCLI\EpWinServiceCLI110.vcxproj" /projectconfig "Debug Unicode"
"C:\Program Files\Microsoft Visual Studio 11.0\Common7\IDE\devenv" EpWinServiceCLI110.sln /build "Release Unicode" /project "EpWinServiceCLI\EpWinServiceCLI110.vcxproj" /projectconfig "Release Unicode"

:Done