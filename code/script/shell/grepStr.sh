
# 获取test字符串后面的字符串
cat test.txt |grep -o "test.*"

# 获取test字符串后面的字符串
awk -F "test" '{print $2}' test.txt

# 获取test字符串后面的字符串
sed 's/.*test//g' test.txt

# 获取test字符串后面的字符串
tr -d a-z0-9 < test.txt


#匹配文件，替换对应的文本
find . -name BUILD.gn |xargs sed -i 's#cesfwk_kits#cesfwk_innerkits#g'


grep匹配多个str
ps -A | grep -E "tel|ril"



#匹配对应的目录（文件）并删除
find . -name "telephony"  | xargs rm -rf
find . -name "netmanager_standard"  | xargs rm -rf




git log --since=2021-10-01 --until=2021-10-31 --author=dangchaojin --pretty=tformat: --numstat | awk '{ add += $1; subs += $2; loc += $1 - $2; total += $1 + $2 } END { printf "  新增代码行: %s\n  移除代码行: %s\n  总增加代码行: %s\n  总修改代码行: %s\n", add, subs, loc, total }'








# 截取字符串
path=ss/usr/share/src/root/home/admin
echo $path

echo ${path%src*} #从右向左截取第一个 src 后的字符串
echo ${path}
echo ${path%/*} #从右向左截取 第一个 / 后的字符串
echo ${path%%/*} #从右向左截取 最后一个 / 后的字符串
echo ${path#*/} #从左向右截取第一个 / 后的字符串
echo ${path##*/} #从左向右截取最后一个 / 后的字符串
echo ${path:3}
echo ${path:6:60} #截取变量path从前三个字符串
echo ${#path} #计算 path变量 一共有几个字符串
echo ${path/root/kyo} #把path变量里的第一个root字符串，替换为 kyo字符串
echo ${path//s/m} #把path变量里的所有的s字符，替换为 m 字符
echo ${path}