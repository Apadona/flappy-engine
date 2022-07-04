#!/bin/sh

cd ../..

if [ -d "cmakefiles" ]; then
    echo "cmakefiles exists, attempting to remove it."
    rm -rf "cmakefiles"
fi

if [ -d "build" ]; then
    echo "build exists, attempting to remove it."
    rm -rf "build"
fi