@echo off

set PROGRAM="%~1"

if  %ERRORLEVEL% EQU 1 goto err

%PROGRAM% < test-data\input0.txt > test-data\output.txt
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output.txt test-data\answer0.txt || goto err
echo Test 1 passed!

%PROGRAM% < test-data\input1.txt > test-data\output.txt
if %ERRORLEVEL% EQU 0 goto err
fc test-data\output.txt test-data\answer1.txt || goto err
echo Test 2 passed!

%PROGRAM% < test-data\input2.txt > test-data\output.txt
if %ERRORLEVEL% EQU 0 goto err
fc test-data\output.txt test-data\answer2.txt || goto err
echo Test 3 passed!

%PROGRAM% < test-data\input3.txt > test-data\output.txt
if %ERRORLEVEL% EQU 0 goto err
fc test-data\output.txt test-data\answer3.txt || goto err
echo Test 4 passed!

%PROGRAM% < test-data\input4.txt > test-data\output.txt
if %ERRORLEVEL% EQU 0 goto err
fc test-data\output.txt test-data\answer4.txt || goto err
echo Test 5 passed!

%PROGRAM% < test-data\input5.txt > test-data\output.txt
if %ERRORLEVEL% EQU 0 goto err
fc test-data\output.txt test-data\answer5.txt || goto err
echo Test 6 passed!

%PROGRAM% < test-data\input6.txt > test-data\output.txt
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output.txt test-data\answer6.txt || goto err
echo Test 7 passed!

echo All tests passed!
exit 0

:err
echo Program testing failed!
exit 1