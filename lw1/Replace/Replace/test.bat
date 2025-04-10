@echo off 

set PROGRAM="%~1"

if ERRORLEVEL 1 goto err

%PROGRAM% test-data\input0.txt test-data\output.txt a b
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output.txt test-data\answer0.txt || goto err
echo Test 1 passed!

%PROGRAM% test-data\input1.txt test-data\output.txt ma pa
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output.txt test-data\answer1.txt || goto err
echo Test 2 passed!

%PROGRAM% test-data\input1.txt test-data\output.txt ma
if %ERRORLEVEL% EQU 0 goto err
echo Test 3 passed!

%PROGRAM% test-data\input2.txt test-data\output.txt 1231234 XYZ
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output.txt test-data\answer2.txt || goto err
echo Test 4 passed!

%PROGRAM% test-data\input3.txt test-data\output.txt : tam
if %ERRORLEVEL% EQU 1 goto err
fc test-data\output.txt test-data\answer3.txt || goto err
echo Test 5 passed!

echo All tests passed
exit 0

:err
echo Program testing failed
exit 1
