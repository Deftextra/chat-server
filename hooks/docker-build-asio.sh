#!/bin/bash
if [ \( "$1" == "--asio-version" -o "$1" == "-b" \) -a $# -eq 2 ] ; then

  ASIO_VERSION="$2"
  PROJECT_DIRECTORY=$(basename ${PWD})

  docker build --target dev -t radwans/asio:${ASIO_VERSION} \
    --build-arg ASIO_VERSION=${ASIO_VERSION} \
    --build-arg PROJECT_DIRECTORY=${PROJECT_DIRECTORY} .
else
  echo "Usage: ./docker-build [--asio-version | -b] ASIO_VERSION"
fi
