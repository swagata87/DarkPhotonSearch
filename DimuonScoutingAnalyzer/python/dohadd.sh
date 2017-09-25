#!/bin/bash

cd  scouting_crab_projects_Sept4/
echo $(pwd)
#num=101
#num2=0
#num3=1001

for i in */; 
do 
    echo " "
    echo "### $i"; 
    cd "$i/results"
    #echo "------" $(pwd)
    rm newhist*.root

    n=$(ls -1 | wc -l)
    echo $n " files"

    if [ $n -le 100 ]; then 
	hadd -f hist.root AnalysisOutput*root 

    elif [ $n -gt 100 ]; then 
	#let "a=n/100"
	#let "b=n%100"
	#echo $a, $b
        #if [ $b -ne "$num2" ]; then
	#    let a=a+1
	#    echo "do haddin " $a "iterations"
	#fi    
	hadd -f newhist0.root   AnalysisOutput_1.root
	hadd -f newhist1.root   AnalysisOutput_10*.root 
	hadd -f newhist2.root   AnalysisOutput_11*.root
	hadd -f newhist3.root   AnalysisOutput_12*.root
	hadd -f newhist4.root   AnalysisOutput_13*.root
	hadd -f newhist5.root   AnalysisOutput_14*.root
	hadd -f newhist6.root   AnalysisOutput_15*.root
	hadd -f newhist7.root   AnalysisOutput_16*.root
	hadd -f newhist8.root   AnalysisOutput_17*.root
	hadd -f newhist9.root   AnalysisOutput_18*.root
	hadd -f newhist10.root  AnalysisOutput_19*.root

	hadd -f newhist11a.root  AnalysisOutput_2.root
	hadd -f newhist11b.root  AnalysisOutput_20*.root 
	hadd -f newhist12.root   AnalysisOutput_21*.root
	hadd -f newhist13.root   AnalysisOutput_22*.root
	hadd -f newhist14.root   AnalysisOutput_23*.root
	hadd -f newhist15.root   AnalysisOutput_24*.root
	hadd -f newhist16.root   AnalysisOutput_25*.root
	hadd -f newhist17.root   AnalysisOutput_26*.root
	hadd -f newhist18.root   AnalysisOutput_27*.root
	hadd -f newhist19.root   AnalysisOutput_28*.root
	hadd -f newhist20.root   AnalysisOutput_29*.root

	hadd -f newhist21a.root  AnalysisOutput_3.root
	hadd -f newhist21b.root  AnalysisOutput_30*.root 
	hadd -f newhist22.root   AnalysisOutput_31*.root
	hadd -f newhist23.root   AnalysisOutput_32*.root
	hadd -f newhist24.root   AnalysisOutput_33*.root
	hadd -f newhist25.root   AnalysisOutput_34*.root
	hadd -f newhist26.root   AnalysisOutput_35*.root
	hadd -f newhist27.root   AnalysisOutput_36*.root
	hadd -f newhist28.root   AnalysisOutput_37*.root
	hadd -f newhist29.root   AnalysisOutput_38*.root
	hadd -f newhist30.root   AnalysisOutput_39*.root

	hadd -f newhist31.root   AnalysisOutput_4*.root
	hadd -f newhist32.root   AnalysisOutput_5*.root
	hadd -f newhist33.root   AnalysisOutput_6*.root
	hadd -f newhist34.root   AnalysisOutput_7*.root
	hadd -f newhist35.root   AnalysisOutput_8*.root
	hadd -f newhist36.root   AnalysisOutput_9*.root
	
	hadd -f hist.root  newhist*.root
	
    fi
    cd ../..
done;