#!/bin/bash
name=""
age=0
group=""
work=1

while [ $work ]
do
    echo "enter your name:"
    read name
    if [[ -z $name ]]
    then
        echo "bye"
        break
    fi

    echo "enter your age:"
    read age
    if [[ $age -eq 0 ]]
    then
        echo "bye"
        break
    fi    

    if [[ $age -le 16 ]]
    then
        group="child"
    elif [[ $age -ge 17 && $age -le 25 ]]
    then
        group="youth"
    else       
        group="adult"
    fi

    echo "$name, your group is $group"

done
