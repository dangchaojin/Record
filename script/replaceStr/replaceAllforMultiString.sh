#放到文件夹根目录执行即可
#适用于大量字符串批量替换所有文件
#替换规则需要从EXCEL中选中old列和new列一次复制到arr数组中,第一列oldString，第二列newString
#    old string             new string

arr=(
HRIL_CDMA_SMS_DigitMode	HRilCdmaSmsDigitMode
HRIL_CDMA_SMS_NumberPlan	HRilCdmaSmsNumberPlan
HRIL_CDMA_SMS_NumberMode	HRilCdmaSmsNumberMode
HRIL_DataConfigInfo	HRilDataConfigInfo
HRIL_DataConfigInfo_v15	HRilDataConfigInfo_V15
HRIL_SIM_IO_Response	HRilSimIOResponse
)

source_filelist=`find . \( -name "*.cpp" -o -name "*.h" -o -name "*.md" -o -name "*.c" -o -name "*.java" \)`

h=0
for (( h >=0 ;h <= $(expr ${#arr[*]} / 2 );h++))
do
        old=${arr[$(expr $h \* 2  + 0)]}
        new=${arr[$(expr $h \* 2  + 1)]}
        echo "$old >> $new"
		
		for file in $source_filelist;
		do
			echo "$file"
			sed -i "s/\<$old\>/$new/g" $file
		done
done