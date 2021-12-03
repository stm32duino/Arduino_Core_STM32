FROM ubuntu:latest

ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8

# Install prerequisites
RUN apt-get --quiet=2 update && apt-get install --quiet=2 --assume-yes sudo git python3 python3-pip wget

# Copies your code file from your action repository to the filesystem path `/` of the container
COPY entrypoint.sh /entrypoint.sh

# Code file to execute when the docker container starts up (`entrypoint.sh`)
ENTRYPOINT ["/entrypoint.sh"]
