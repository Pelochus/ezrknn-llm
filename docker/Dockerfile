FROM ubuntu:24.04

COPY setup.sh /setup.sh
COPY entrypoint.sh /entrypoint.sh

RUN ./setup.sh
ENTRYPOINT ["/entrypoint.sh"]
