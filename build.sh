#!/bin/bash

if /usr/bin/make ; then
    echo "=========== RUNNING ============="
    `pwd`/raycaster
else
    echo "!!! Build failed!"
fi
