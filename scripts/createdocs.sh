#!/bin/bash

exe=doxygen
command -v $exe >/dev/null 2>&1 || { echo >&2 "You need $exe installed to run this script!"; exit 1; }

$exe config/doxy.config
