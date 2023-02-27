set WORKSPACE=%~dp0..
mkdir %WORKSPACE%\build
cmake -S %WORKSPACE% -B %WORKSPACE%\build