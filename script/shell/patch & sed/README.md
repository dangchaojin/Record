1.git commit -a -m "test"
2.git diff HEAD <欲对比的提交commit id> -U0 > test.patch
3.后续可以git reset --hand恢复到之前版本
(-U0是对比出的patch里没有太多上下文)
4.根据test.patch写好修改行号的脚本
5.注意format_ex.sh最下面的  git apply --unidiff-zero ${patchname}

format.sh(此脚本原理是调用vs的clang-format插件刷代码格式)

