:: https://jingyan.baidu.com/article/6fb756ec98a317241858fbfe.html

::  1、放到相应目录下
::  2、第一次运行，生成private目录
::  3、需加密文件放到private目录下
::  4、第二次运行，加密，隐藏文件夹
::  5、第三次运行，输入密码，文件显示及解密

::温馨提示：
::当Private文件夹被隐藏时，通过文件夹选项设置
::如果选择“显示隐藏的文件、文件夹和驱动器”，那么该文件还是处于加密状态。
::如果取消勾选“隐藏受保护的系统文件”，那么Private文件夹将不再处于隐藏状态。


cls
@ECHO OFF
title Folder Private
if EXIST "HTG Locker" goto UNLOCK
if NOT EXIST Private goto MDLOCKER
:CONFIRM
echo 你确定要加密隐藏Private文件夹吗？(Y/N)
set/p "cho=>"
if %cho%==Y goto LOCK
if %cho%==y goto LOCK
if %cho%==n goto END
if %cho%==N goto END
echo Invalid choice.
goto CONFIRM
:LOCK
ren Private "HTG Locker"
attrib +h +s "HTG Locker"
echo Folder locked
goto End
:UNLOCK
echo 输入密码来解锁文件夹
set/p "pass=>"
if NOT %pass%== 1234567dcj goto FAIL
attrib -h -s "HTG Locker"
ren "HTG Locker" Private
echo Folder Unlocked successfully
goto End
:FAIL
echo Invalid password
goto end
:MDLOCKER
md Private
echo Private created successfully
goto End
:End