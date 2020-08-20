#!/bin/bash
docker run -d -it --name http-server -v ${PWD}:/project/http-server radwans/asio:1.18.0
