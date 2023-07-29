#!/bin/bash

cd ./../..

system_architecture=$(getconf LONG_BIT)

./build/bin/linux/$system_architecture/sandbox $@
