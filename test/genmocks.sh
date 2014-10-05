#!/bin/bash

readonly EASYMOCKDIR=$(readlink -f ..)
readonly EASYMOCKGEN=$(readlink -f $EASYMOCKDIR/gen/easymockgen.py)
readonly TEST=$(readlink -f $(dirname $0))

export PYTHONPATH=$PYCPARSER:$PYTHONPATH
export EASYMOCK_GCC=gcc
export EASYMOCK_CFLAGS="-I./include"

echo "PYTHONPATH      = $PYTHONPATH"
echo "EASYMOCK_GCC    = $EASYMOCK_GCC"
echo "EASYMOCK_CFLAGS = $EASYMOCK_CFLAGS"

rm -rf $TEST/mocks
mkdir $TEST/mocks

$EASYMOCKGEN -o mocks include/em_header_simple_*
$EASYMOCKGEN -o mocks subdir/em_header_in_subdir.h

$EASYMOCKGEN -o mocks em_header_1.h
$EASYMOCKGEN -o mocks em_header_2.h
$EASYMOCKGEN -o mocks --include-all em_header_3.h
$EASYMOCKGEN -o mocks --include em_header_4_b.h em_header_4.h
$EASYMOCKGEN -o mocks --include-all --add-func-pfx em em_header_system.h
$EASYMOCKGEN -o mocks --include-all \
--wrap fopen \
--wrap fclose \
--wrap open \
--wrap close \
include/em_header_system_wrap.h

exit $?
