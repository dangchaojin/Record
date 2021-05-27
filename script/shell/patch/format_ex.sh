#!/bin/sh

patchname='core_service_format.patch'
filename='interfaces/kits/js/napi/network_search/src/napi_radio.cpp'
echo ${filename}

line=`cat ${patchname} | grep -n "@@ napi_value InitNapiRadioNetwork(napi_env env, napi_value exports)" |cut -d: -f1`
echo line ${line}
#line1=5
line1=`echo ${line} |cut -d' ' -f1`
#line2=9
line2=`echo ${line} |cut -d' ' -f2`
echo line1 ${line1} line2 ${line2}

start1=`cat ${filename} | grep -n "DECLARE_NAPI_FUNCTION(\"getRadioTech\", GetRadioTech)" |cut -d: -f1`
if  [ ! -n "$start1" ] ;then
    echo "its empty!"
    start1=1
fi

offset=22
start2=`expr ${start1} + ${offset}`

offset1=0
offset2=1
end1=`expr ${start1} + ${offset1}`
end2=`expr ${start2} + ${offset2}`
echo ${start1} ${end1}
echo ${start2} ${end2}

sed -i ''${line1}'s#@@ -\([0-9]\+\)#@@ -'${start1}'#1' ${patchname}
sed -i ''${line2}'s#@@ -\([0-9]\+\)#@@ -'${start2}'#1' ${patchname}

sed -i ''${line1}'s#+\([0-9]\+\)#+'${end1}'#1' ${patchname}
sed -i ''${line2}'s#+\([0-9]\+\)#+'${end2}'#1' ${patchname}

#######################################################################################################################

echo ${filename}

line2=`cat ${patchname} | grep -n "@@ static napi_module _radioModule = {\.nm_version = 1," |cut -d: -f1`
line1=`expr ${line2} - 4`
echo line1 ${line1} line2 ${line2}

start1=`cat ${filename} | grep -n "napi_module _radioModule =" |cut -d: -f1`
if  [ ! -n "$start1" ] ;then
    echo "its empty!"
    start1=1
fi

offset=6
start2=`expr ${start1} + ${offset}`

offset1=2
offset2=3
end1=`expr ${start1} + ${offset1}`
end2=`expr ${start2} + ${offset2}`
echo ${start1} ${end1}
echo ${start2} ${end2}

sed -i ''${line1}'s#@@ -\([0-9]\+\)#@@ -'${start1}'#1' ${patchname}
sed -i ''${line2}'s#@@ -\([0-9]\+\)#@@ -'${start2}'#1' ${patchname}

sed -i ''${line1}'s#+\([0-9]\+\)#+'${end1}'#1' ${patchname}
sed -i ''${line2}'s#+\([0-9]\+\)#+'${end2}'#1' ${patchname}

#######################################################################################################################

patchname='core_service_format.patch'
filename='interfaces/kits/js/napi/sim/src/napi_sim.cpp'
echo ${filename}

line=`cat ${patchname} | grep -n "@@ napi_value InitNapiSim(napi_env env, napi_value exports)" |cut -d: -f1`
echo line ${line}
#line1=25	########
line1=`echo ${line} |cut -d' ' -f1`
#line2=29	########
line2=`echo ${line} |cut -d' ' -f2`
echo line1 ${line1} line2 ${line2}

start1=`cat ${filename} | grep -n "napi_property_descriptor desc\[\] = {DECLARE_NAPI_FUNCTION(\"getISOCountryCodeForSim\", GetIsoCountryCodeForSim)," |cut -d: -f1`	########
if  [ ! -n "$start1" ] ;then
    echo "its empty!"
    start1=1
fi

offset=8	########
start2=`expr ${start1} + ${offset}`

offset1=0	#######
offset2=1	#########

end1=`expr ${start1} + ${offset1}`
end2=`expr ${start2} + ${offset2}`
echo ${start1} ${end1}
echo ${start2} ${end2}

sed -i ''${line1}'s#@@ -\([0-9]\+\)#@@ -'${start1}'#1' ${patchname}
sed -i ''${line2}'s#@@ -\([0-9]\+\)#@@ -'${start2}'#1' ${patchname}

sed -i ''${line1}'s#+\([0-9]\+\)#+'${end1}'#1' ${patchname}
sed -i ''${line2}'s#+\([0-9]\+\)#+'${end2}'#1' ${patchname}

#######################################################################################################################

patchname='core_service_format.patch'
filename='interfaces/kits/js/napi/sim/src/napi_sim.cpp'
echo ${filename}

line2=`cat ${patchname} | grep -n "@@ static napi_module _simModule = {\.nm_version" |cut -d: -f1`
line1=`expr ${line2} - 4`
echo line1 ${line1} line2 ${line2}

start1=`cat ${filename} | grep -n "static napi_module _simModule = {\.nm_version" |cut -d: -f1`	########
if  [ ! -n "$start1" ] ;then
    echo "its empty!"
    start1=1
fi

offset=6	########
start2=`expr ${start1} + ${offset}`

offset1=2	########
offset2=3	########

end1=`expr ${start1} + ${offset1}`
end2=`expr ${start2} + ${offset2}`
echo ${start1} ${end1}
echo ${start2} ${end2}
sed -i ''${line1}'s#@@ -\([0-9]\+\)#@@ -'${start1}'#1' ${patchname}
sed -i ''${line2}'s#@@ -\([0-9]\+\)#@@ -'${start2}'#1' ${patchname}

sed -i ''${line1}'s#+\([0-9]\+\)#+'${end1}'#1' ${patchname}
sed -i ''${line2}'s#+\([0-9]\+\)#+'${end2}'#1' ${patchname}

#######################################################################################################################

#patchname='core_service_format.patch'
#filename='network_search/src/network_register.cpp'
#echo ${filename}

#line1=37	########
#line1=`cat ${patchname} | grep -n "" |cut -d: -f1`
#echo line1 ${line1}

#start1=`cat ${filename} | grep -n "registrationState == REG_STATE_NOT_REG_EMERGENCY_CALL_ENABLED" |cut -d: -f1`	########
#if  [ ! -n "$start1" ] ;then
#    echo "its empty!"
#    start1=1
#fi

#offset1=0	#######
#end1=`expr ${start1} + ${offset1}`

#echo ${start1} ${end1}

#sed -i ''${line1}'s#@@ -\([0-9]\+\)#@@ -'${start1}'#1' ${patchname}
#sed -i ''${line1}'s#+\([0-9]\+\)#+'${end1}'#1' ${patchname}

#######################################################################################################################

patchname='core_service_format.patch'
filename='network_search/src/network_search_state.cpp'
echo ${filename}

line=`cat ${patchname} | grep -n "@@ NetworkSearchState &NetworkSearchState::operator=(const NetworkSearchState &stat" |cut -d: -f1`
echo line ${line}
line1=`echo ${line} |cut -d' ' -f1`
echo line1 ${line1}

start1=`find . -name *.cpp |xargs grep -n "static_cast<const void \*>(state.networkType_\.get()), sizeof(NetworkType)) != 0) {" |cut -d: -f2`
#start1=`cat ${filename} | grep -n "static_cast<const void \*>(state.networkType_\.get()), sizeof(NetworkType)) != 0) {" |cut -d: -f1`	########
start1=`echo ${start1} |cut -d' ' -f1`
if  [ ! -n "$start1" ] ;then
    echo "its empty!"
    start1=1
fi

offset1=0	#######
end1=`expr ${start1} + ${offset1}`
echo ${start1} ${end1}
sed -i ''${line1}'s#@@ -\([0-9]\+\)#@@ -'${start1}'#1' ${patchname}
sed -i ''${line1}'s#+\([0-9]\+\)#+'${end1}'#1' ${patchname}

######################################################################

line2=`echo ${line} |cut -d' ' -f2`
echo line2 ${line2}

start1=`cat ${filename} | grep -n "static_cast<const void \*>(state.networkState_\.get()), sizeof(NetworkState)) != 0) {" |cut -d: -f1`	########
start1=`echo ${start1} |cut -d' ' -f1`
if  [ ! -n "$start1" ] ;then
    echo "its empty!"
    start1=1
fi

offset1=0	#######
end1=`expr ${start1} + ${offset1}`
echo ${start1} ${end1}
sed -i ''${line2}'s#@@ -\([0-9]\+\)#@@ -'${start1}'#1' ${patchname}
sed -i ''${line2}'s#+\([0-9]\+\)#+'${end1}'#1' ${patchname}

######################################################################

lineStart=`cat ${patchname} | grep -n "@@ void NetworkSearchState::SetOperatorInfo(const std::string &longName, const std:" |cut -d: -f1`
echo lineStart ${lineStart}
line1=`echo ${lineStart} |cut -d' ' -f1`
echo line1 ${line1}

start1=`cat ${filename} | grep -n "static_cast<const void \*>(longName\.c_str()), NETWORK_MAX_FULL_NAME_LEN) != 0) {" |cut -d: -f1`	########
start1=`echo ${start1} |cut -d' ' -f1`
if  [ ! -n "$start1" ] ;then
    echo "its empty!"
    start1=1
fi

offset1=0	#######
end1=`expr ${start1} + ${offset1}`
echo ${start1} ${end1}
sed -i ''${line1}'s#@@ -\([0-9]\+\)#@@ -'${start1}'#1' ${patchname}
sed -i ''${line1}'s#+\([0-9]\+\)#+'${end1}'#1' ${patchname}

########################################     2
offset=5

#line1=51	########
line2=`echo ${lineStart} |cut -d' ' -f2`
echo line2 ${line2}

start2=`expr ${start1} + ${offset}`
echo ${start2}
offset2=0	#######
end2=`expr ${start2} + ${offset2}`
echo ${start2} ${end2}
sed -i ''${line2}'s#@@ -\([0-9]\+\)#@@ -'${start2}'#1' ${patchname}
sed -i ''${line2}'s#+\([0-9]\+\)#+'${end2}'#1' ${patchname}

########################################     3
offset=5

#line1=54	########
line3=`echo ${lineStart} |cut -d' ' -f3`
echo line3 ${line3}

start3=`expr ${start2} + ${offset}`
echo ${start3}
offset1=0	#######
end3=`expr ${start3} + ${offset1}`
echo ${start3} ${end3}
sed -i ''${line3}'s#@@ -\([0-9]\+\)#@@ -'${start3}'#1' ${patchname}
sed -i ''${line3}'s#+\([0-9]\+\)#+'${end3}'#1' ${patchname}

########################################     4
offset=6

#line1=57	########
line4=`echo ${lineStart} |cut -d' ' -f4`
echo line4 ${line4}

start4=`expr ${start3} + ${offset}`
echo ${start4}
offset1=0	#######
end4=`expr ${start4} + ${offset1}`
echo ${start4} ${end4}
sed -i ''${line4}'s#@@ -\([0-9]\+\)#@@ -'${start4}'#1' ${patchname}
sed -i ''${line4}'s#+\([0-9]\+\)#+'${end4}'#1' ${patchname}

########################################     5
offset=5

#line1=60	########
line5=`echo ${lineStart} |cut -d' ' -f5`
echo line5 ${line5}

start5=`expr ${start4} + ${offset}`
echo ${start5}
offset1=0	#######
end5=`expr ${start5} + ${offset1}`
echo ${start5} ${end5}
sed -i ''${line5}'s#@@ -\([0-9]\+\)#@@ -'${start5}'#1' ${patchname}
sed -i ''${line5}'s#+\([0-9]\+\)#+'${end5}'#1' ${patchname}

########################################     6
offset=5

#line1=63	########
line6=`echo ${lineStart} |cut -d' ' -f6`
echo line6 ${line6}

start6=`expr ${start5} + ${offset}`
echo ${start6}
offset1=0	#######
end6=`expr ${start6} + ${offset1}`
echo ${start6} ${end6}
sed -i ''${line6}'s#@@ -\([0-9]\+\)#@@ -'${start6}'#1' ${patchname}
sed -i ''${line6}'s#+\([0-9]\+\)#+'${end6}'#1' ${patchname}

########################################################################################################################

start1=`cat ${filename} | grep -n "static_cast<const void \*>(networkState_\.get()), sizeof(NetworkState)) != 0) {" |cut -d: -f1`	########
if  [ ! -n "$start1" ] ;then
    echo "its empty!"
    start1=1
fi

#line1=66	########
line1=`cat ${patchname} | grep -n "@@ std::unique_ptr<NetworkState> NetworkSearchState::GetNetworkState()" |cut -d: -f1`
echo line1 ${line1}

echo ${start1}
offset1=0	#######
end1=`expr ${start1} + ${offset1}`
echo ${start1} ${end1}
sed -i ''${line1}'s#@@ -\([0-9]\+\)#@@ -'${start1}'#1' ${patchname}
sed -i ''${line1}'s#+\([0-9]\+\)#+'${end1}'#1' ${patchname}

########################################################################################################################

start1=`cat ${filename} | grep -n "static_cast<const void \*>(networkType_\.get()), sizeof(NetworkType)) != 0) {" |cut -d: -f1`	########
if  [ ! -n "$start1" ] ;then
    echo "its empty!"
    start1=1
fi

#line1=69	########
line1=`cat ${patchname} | grep -n "@@ std::unique_ptr<NetworkType> NetworkSearchState::GetNetworkType()" |cut -d: -f1`
echo line1 ${line1}

echo ${start1}
offset1=0	#######
end1=`expr ${start1} + ${offset1}`
echo ${start1} ${end1}
sed -i ''${line1}'s#@@ -\([0-9]\+\)#@@ -'${start1}'#1' ${patchname}
sed -i ''${line1}'s#+\([0-9]\+\)#+'${end1}'#1' ${patchname}

#######################################################################################################################

patchname='core_service_format.patch'
filename='sim/include/sim_file.h'
echo ${filename}

#line1=76	########
line1=`cat ${patchname} | grep -n "const char \*THREE_DIGITS_MNC_INCLUDED_IN_MCCMNC\[MCCMNC_NUM\] = {\"302370\", \"302720\", \"310260\", \"405025\"," |cut -d: -f1`
line1=`expr ${line1} - 1`
echo line1 ${line1}

start1=`cat ${filename} | grep -n "THREE_DIGITS_MNC_INCLUDED_IN_MCCMNC\[MCCMNC_NUM\]" |cut -d: -f1`	########
#start1=`cat ${filename} | grep -n "THREE_DIGITS_MNC_INCLUDED_IN_MCCMNC\[MCCMNC_NUM\]" |cut -d: -f1`	########
start1=`echo ${start1} |cut -d' ' -f1`

if  [ ! -n "$start1" ] ;then
    echo "its empty!"
    start1=1
fi
echo ${start1}


offset1=0	#######
end1=`expr ${start1} + ${offset1}`
sed -i ''${line1}'s#@@ -\([0-9]\+\)#@@ -'${start1}'#1' ${patchname}
sed -i ''${line1}'s#+\([0-9]\+\)#+'${end1}'#1' ${patchname}

#############################
offset=15	########

line1=`expr ${line1} + 4`
echo line1 ${line1}

start1=`expr ${start1} + ${offset}`
echo ${start1}
offset1=1	#######
end1=`expr ${start1} + ${offset1}`
echo ${start1} ${end1}
sed -i ''${line1}'s#@@ -\([0-9]\+\)#@@ -'${start1}'#1' ${patchname}
sed -i ''${line1}'s#+\([0-9]\+\)#+'${end1}'#1' ${patchname}

#######################################################################################################################

git apply --unidiff-zero ${patchname}

