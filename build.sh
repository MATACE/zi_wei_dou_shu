#!/bin/bash

MAJOR=1
MINOR=0
PATCH=0


LIB_NAME="pro"

cmake -DPLATFORM=arm -DCMAKE_BUILD_TYPE=Release ..
make -j32
# arm-none-linux-gnueabi-strip libs/lib/lib$LIB_NAME.so.$MAJOR.$MINOR.$PATCH
# cd libs/lib/
# tar -cvzf lib$LIB_NAME.tar.gz lib$LIB_NAME.so*
# mv lib$LIB_NAME.tar.gz ../../