FROM ubuntu:bionic AS dev

LABEL maintainer="Radwan Suufi <rd.90@hotmail.com>"
LABEL version="1.0"

WORKDIR /tmp

# Install asio dependencies.
ARG PROJECT_DIRECTORY
ARG ASIO_VERSION
ENV PROJECT_DIRECTORY ${PROJECT_DIRECTORY}
ENV ASIO_VERSION ${ASIO_VERSION}
ENV ASIO_ROOT=/usr/local/include

RUN apt-get -qq update && apt-get install -q -y software-properties-common && \
  apt-get -qq update && apt-get install -qy g++ gcc git cmake make clang && \
  apt-get update && \ 
  apt-get install -y cmake g++ make clang-tidy && \
  apt-get install wget

RUN wget --max-redirect 3 https://deac-ams.dl.sourceforge.net/project/asio/asio/${ASIO_VERSION}%20%28Stable%29/asio-${ASIO_VERSION}.tar.gz && \
   mkdir /tmp/asio &&  tar zxf asio-${ASIO_VERSION}.tar.gz -C /tmp/asio --strip-components=1 && \
   rm -rf asio-${ASIO_VERSION}.tar.gz && \
   cd asio && ./configure && cd .. &&  \
   make -C asio && make -C asio/include install && rm -rf asio

RUN echo ${ASIO_ROOT}
ENTRYPOINT [ "/bin/bash"]

# Running server
FROM alpine:latest as server
WORKDIR /root/
COPY --from=dev /project/chat-server/bin/server_run .
CMD ["./server_run"]

# Running client
FROM alpine:latest as client
WORKDIR /root/
COPY --from=dev /project/chat-server/bin/client_run .
CMD ["./client_run"]
