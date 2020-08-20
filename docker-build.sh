#!/bin/bash

ASIO_VERSION="1.18.0"

if [ "$1" == "--promt" -o "$1" == "-p" ];then
    printf "Which asio version? : "
    read ASIO_VERSION
fi

./hooks/docker-build-asio.sh --asio-version ${ASIO_VERSION}