@echo off
cls
:start
Title "Engine2D Pushing"
echo "Engine2D Pushing"
date /t
time /t
If Not Exist version.ver Goto :filenotfound
type version.ver
echo:
set /p input="Commit Message : "
echo %input% > version.ver
git add *
git commit -m "%input%"
git push
echo ################################# >> pushHistory.log
echo "Engine2D Pushing" >> pushHistory.log
date /t >> pushHistory.log
time /t >> pushHistory.log
echo %input% >> pushHistory.log
:exit
pause
Exit
:filenotfound
echo "version.ver not found"
pause
Exit
