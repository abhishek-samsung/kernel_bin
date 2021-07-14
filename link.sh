#!/bin/bash

BASEDIR=$(dirname $0)

ln -sf ${PWD}/${BASEDIR}/* ${PWD}/${BASEDIR}/common_source/os/
rm ${PWD}/${BASEDIR}/common_source/os/common_source
