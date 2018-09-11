@echo off
cls
:start
echo DirectX11Engine
date /t
type version.ver
echo:
set /p input="Commit Message : "
echo %input% > version.ver
git add *
git commit -m "%input%"
git push
echo ################################# >> pushHistory.log
echo DirectX11Engine >> pushHistory.log
date /t >> pushHistory.log
time /t >> pushHistory.log
echo %input% >> pushHistory.log
pause
:exit