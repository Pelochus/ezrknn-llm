FROM ubuntu:focal

COPY setup.sh /setup.sh
COPY entrypoint.sh /entrypoint.sh

RUN ./setup.sh
ENTRYPOINT ["/entrypoint.sh"]
