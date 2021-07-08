@echo off
::关闭回显

::测试出一句一句运行的效果
::pause

title Copying
echo "使用bat脚本来复制文件夹和文件"
echo.
:: echo后可以加双引号，也可以不加

:: set SrcPath = "D:\Qt5.12.0\5.12.0\mingw73_64\bin\libgcc_s_seh-1.dll"
:: 显示乱码的另存为ANSI编码
:: xcopy 有询问的拷贝

::@echo on
::打开回显

copy D:\Qt5.12.0\5.12.0\mingw73_64\bin\Qt5Guid.dll                D:\Test_Code\QtMedia\debug
copy D:\Qt5.12.0\5.12.0\mingw73_64\bin\Qt5Cored.dll               D:\Test_Code\QtMedia\debug
copy D:\Qt5.12.0\5.12.0\mingw73_64\bin\Qt5OpenGLd.dll             D:\Test_Code\QtMedia\debug
copy D:\Qt5.12.0\5.12.0\mingw73_64\bin\Qt5Widgetsd.dll            D:\Test_Code\QtMedia\debug
copy D:\Qt5.12.0\5.12.0\mingw73_64\bin\Qt5Networkd.dll            D:\Test_Code\QtMedia\debug
copy "D:\Qt5.12.0\5.12.0\mingw73_64\bin\libstdc++-6.dll"         "D:\Test_Code\QtMedia\debug"
copy "D:\Qt5.12.0\5.12.0\mingw73_64\bin\Qt5Multimediad.dll"       D:\Test_Code\QtMedia\debug
copy D:\Qt5.12.0\5.12.0\mingw73_64\bin\libwinpthread-1.dll        D:\Test_Code\QtMedia\debug
copy D:\Qt5.12.0\5.12.0\mingw73_64\bin\libgcc_s_seh-1.dll         D:\Test_Code\QtMedia\debug
copy D:\Qt5.12.0\5.12.0\mingw73_64\bin\Qt5MultimediaWidgetsd.dll  D:\Test_Code\QtMedia\debug

::  copy第六行中，前后都需要双引号

::  目录中如果有特殊字符，大部分可以用^这个符号来进行转义，而%就要用%%代替
::  路径中出现符号或一些特殊字符可以进行转义，或用双引号把路径括起来（前后都需要双引号）。
::  ————————————————————————————————————含空格或奇怪字符的路径或文件名，加双引号
::  如果【】这些中文字符的路径，在使用时出现文件不存在的提示。那么请检查路
::  径中是否有空格，如果存在空格，那么肯定出错。如果没有空格，那么给定的路
::  径是完整的绝对路径，还是不完整的相对路径，如果使用的是相对路径，那么就
::  要看看脚本运行目录是否不和相对路径的第一个文件夹在一起。

:: call 调用另一个脚本     cd 切换目录

@echo off
echo 脚本执行完成

echo if you confirm you are handsome, input ‘y’?
set /p answer=
echo your input is ‘%answer%’
if ‘%answer%’==‘y’ goto B
::上一行两个地方，双引号或者单引号都可以
exit
:B 
echo handsome
pause


::删除
::del D:\Test_Code\QtMedia\debug\Qt5Guid.dll
::del D:\Test_Code\QtMedia\debug\Qt5Cored.dll
::del D:\Test_Code\QtMedia\debug\Qt5OpenGLd.dll
::del D:\Test_Code\QtMedia\debug\Qt5Networkd.dll
::del D:\Test_Code\QtMedia\debug\Qt5Widgetsd.dll
::del D:\Test_Code\QtMedia\debug\libstdc++-6.dll
::del D:\Test_Code\QtMedia\debug\libgcc_s_seh-1.dll
::del D:\Test_Code\QtMedia\debug\Qt5Multimediad.dll
::del D:\Test_Code\QtMedia\debug\libwinpthread-1.dll
::del D:\Test_Code\QtMedia\debug\Qt5MultimediaWidgetsd.dll