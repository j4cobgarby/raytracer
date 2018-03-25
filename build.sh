#!/bin/bash

if /usr/bin/make ; then
    echo "=========== RUNNING ============="
    `pwd`/raycaster $1
else
    echo "!!! Build failed!"
fi
