#!/bin/bash

cd ../..

system_architecture=$(getconf LONG_BIT)

gdb build/bin/linux/$system_architecture/sandbox $@
