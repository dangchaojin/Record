#!/bin/sh
#define:此脚本作用是检测pas配置文件配置项缺漏
#author:dcj
echo "execution script: $0"

checkFun(){
    ## check number of parameter
    if test $# -ne 4
    then
        echo "param num is: $#, error! so return!"
        return 1
    fi
    echo "Start Checking filename:$1  section:$2  checkstr:$3  addstr:$4"

    ## check file exists?
    if ! test -e $1   ##test test in redhat
    then
    ##    echo "$1 is exists"
    ##else
        echo "$1 does not exist"
        touch $1
    fi

    ## check section exists?
    if [ $(grep -c "\[$2\]" $1) -eq 0 ];
    then
        echo "section: [$2] does not exist in file, now add to file."
		echo -e "" >> $1
        echo -e "[$2]" >> $1          ##根据系统不同，有的可以直接用\n
        ##printf "\n[$2]\n" >> $1
        sed -i "/\[$2\]/a\\$4" $1
    else
        strTmp=$3
        echo "[$2] already in file, check checkstr:${strTmp% *}."
        echo "[$2] already in file, check checkstr:${strTmp%% *}."
        echo "[$2] already in file, check checkstr:${strTmp%=*}."
        echo "[$2] already in file, check checkstr:${strTmp%%=*}."

        ##if [ $(grep -c " *${strTmp%%=*} *=" $1) -eq 0 ];   ##%% | %
        ##if [ $(grep -c "\<${strTmp%% *}" $1) -eq 0 ];
        if [ $(grep -c "$3" $1) -eq 0 ];
        then
            echo "section:[$2] need add str: "$3""
            sed -i "/\[$2\]/a\\$4" $1
        fi
    fi

    return 0
}

##format:         fileName               sectionName   addStr   checkStr
checkFun "/opt/mcu/pas/conf/pasdebug.ini" "HcmInfo"   "add"   "add = add1"
checkFun "/opt/mcu/pas/conf/pasdebug.ini" "dcj"       "dcj"   "dcj = cj1"
checkFun "/opt/mcu/pas/conf/spcfg.ini" "HcmInfo"   "add"   "add = add1"

##echo "return value: $?"


##test step:
## 1.file ?
## 2.param



## https://www.cnblogs.com/ftl1012/p/9250684.html
