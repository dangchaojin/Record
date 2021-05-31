#!/bin/sh

# 1. 格式类问题自己格式化，可以用此脚本或ide，确认格式化刷完后，能否解决问题
# 2. 如果刷完不能解决，手动改并报出来，然后研究修改规则，确认无法通过修改规则，此类问题表格汇总记录
# 3. 修改规则后，统一由党朝劲上传到各个仓库
# 4. 手动修改后的要刷一下，确认是否又有问题，如有反馈，优先重点解决
# 5. 由于格式化引入的问题重点优先解决，研究规则，原则上不能引入新问题


echo "formating..."

find . -name *.cpp -o -name *.h -o -name *.c | xargs ./clang-format -style=file -i

echo "format complete"
echo "please check the code specification again!"
