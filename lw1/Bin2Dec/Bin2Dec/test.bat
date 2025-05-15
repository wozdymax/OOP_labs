@echo off

set PROGRAM="%~1"

if ERRORLEVEL 1 goto ERRORLEVEL

echo SIUUUUUUUUUUUUUUU

%PROGRAM% < test-data\input0.txt > test-data\output.txt
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output.txt test-data\answer0.txt || goto err
echo Test with 400 passed!

%PROGRAM% 1010 > test-data\output.txt
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output.txt test-data\answer1.txt || goto err
echo Test with 10 passed!

%PROGRAM% -100 > test-data\output.txt
if %ERRORLEVEL% EQU 0 goto err
fc test-data\output.txt test-data\answer2.txt || goto err
echo Test with invalid bin number passed!

%PROGRAM% 1111111111111111111111111111111 > test-data\output.txt
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output.txt test-data\answer3.txt || goto err
echo Test with MAX_INT passed!

%PROGRAM% 10000000000000000000000000000000 > test-data\output.txt
if %ERRORLEVEL% EQU 0 goto err
fc test-data\output.txt test-data\answer4.txt || goto err
echo Test witn MAX_INT+1 passed!

echo All tests passed!
exit 0

err:
echo Program testing failed!
exit 1