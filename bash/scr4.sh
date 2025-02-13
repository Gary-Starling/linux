#!/bin/bash

var1=1
var2=2

if [[ !(4 -le 3) ]]
then
 echo "True1"
fi

if [[ -n $0 ]] #esli stroka imeni scr ne pust
then
 echo "True2"
fi

if [[ $# -gt 0 ]] #esli kolich arg >0
then
 echo "True3"
fi

if [[ -z " " ]] #esli  str  pusta
then
 echo "True4"
fi


if [[ $var1==$var2 && $var1!=$var2 ]]
then
 echo "True5"
fi

if [[ -n $1 ]] #esli str ne pusta
then 
 echo "True6" 
fi





