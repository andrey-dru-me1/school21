FROM ubuntu:latest

RUN apt update \
  && apt upgrade -y \
  && apt install -y make gcc pkg-config libgtest-dev lcov check libncurses5-dev libncursesw5-dev

COPY . /root/

CMD cd /root && make clean && make && make test && make gcov_report