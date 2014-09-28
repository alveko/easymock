#!/bin/bash

readonly EASYMOCKDIR=$(readlink -f ..)
readonly EASYMOCKGEN=$(readlink -f $EASYMOCKDIR/gen/easymockgen.py)
readonly TEST=$(readlink -f $(dirname $0))

export PYTHONPATH=$PYCPARSER:$PYTHONPATH
export EASYMOCK_GCC=gcc
export EASYMOCK_CFLAGS="-I."

echo "PYTHONPATH      = $PYTHONPATH"
echo "EASYMOCK_GCC    = $EASYMOCK_GCC"
echo "EASYMOCK_CFLAGS = $EASYMOCK_CFLAGS"

rm -rf $TEST/mocks
mkdir $TEST/mocks

$EASYMOCKGEN -o mocks include/em_header_simple_1.h
$EASYMOCKGEN -o mocks include/em_header_simple_2.h
$EASYMOCKGEN -o mocks include/em_header_1.h
$EASYMOCKGEN -o mocks include/em_header_2.h
$EASYMOCKGEN --include-all -o mocks include/em_header_3.h
$EASYMOCKGEN --include em_header_4_b.h -o mocks include/em_header_4.h
$EASYMOCKGEN --include-all -o mocks --name-pfx em include/em_header_system.h
$EASYMOCKGEN --include-all -o mocks \
--wrap fopen \
--wrap fclose \
--wrap open \
--wrap close \
include/em_header_system_wrap.h

exit $?
