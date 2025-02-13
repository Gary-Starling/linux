#!/bin/bash
a=10
b=15

let "a = a + b"
echo "$a"

let "a+=b"
echo "$a"

let a=a+b
echo "$a"

let a=$a+$b
echo "$a"

a+=$b
echo "$a"

