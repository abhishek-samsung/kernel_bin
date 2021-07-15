#!/bin/bash

BASEDIR=$(dirname $0)

ln -sf ${PWD}/${BASEDIR}/* ${PWD}/${BASEDIR}/common_source/os/
ln -sf ${PWD}/${BASEDIR}/kernel/* ${PWD}/${BASEDIR}/common_source/os/kernel
ln -sf ${PWD}/${BASEDIR}/kernel/timer/* ${PWD}/${BASEDIR}/common_source/os/kernel/timer
ln -sf ${PWD}/${BASEDIR}/kernel/signal/* ${PWD}/${BASEDIR}/common_source/os/kernel/signal
ln -sf ${PWD}/${BASEDIR}/net/* ${PWD}/${BASEDIR}/common_source/os/net
ln -sf ${PWD}/${BASEDIR}/net/lwip/* ${PWD}/${BASEDIR}/common_source/os/net/lwip
ln -sf ${PWD}/${BASEDIR}/net/lwip/src/* ${PWD}/${BASEDIR}/common_source/os/net/lwip/src
rm ${PWD}/${BASEDIR}/common_source/os/common_source
