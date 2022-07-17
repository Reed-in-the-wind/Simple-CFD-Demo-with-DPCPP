#!/bin/bash

if [ $1 == 'clean' ];then
    rm -rf *.exe
else
    dpcpp -fsycl-unnamed-lambda $1 -o main.exe
fi

