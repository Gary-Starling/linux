#!/bin/bash

c=0
max=0
min=0
work=1

func_nod () #max min
{
    #echo "max=$1 min=$2"

    let "c=$1%$2"

    if [[ $c -eq 0 ]]
    then
        echo "GCD is $2"
    else
        func_nod $2 $c #berem delitel' kak delimoe i ostatok, kak delitel
    fi
}


while [[ work ]]
do
    read a b

    if [[ -z $a || -z $b ]]
    then
        echo "bye"
        exit
    fi

    if [[ $a -gt $b ]]
    then
        max=$a; min=$b;
    elif [[ $a -lt $b ]]
    then
        max=$b; min=$a;
    else #ravni
        max=$a; min=$b;
    fi   

    func_nod $max $min    
done