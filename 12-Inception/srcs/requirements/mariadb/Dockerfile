# FROM debian:buster

# RUN apt-get update -y && apt-get install mariadb-server -y

# COPY ./tools/50-server.cnf /etc/mysql/mariadb.conf.d/


# COPY ./tools/script.sh /
# RUN chmod 777 /script.sh

# CMD ["/script.sh"]
FROM alpine:3.13

RUN apk update && apk upgrade && \
    apk add --no-cache mariadb mariadb-client

COPY tools/configure.sh /tmp/configure.sh

ENTRYPOINT [ "sh", "/tmp/configure.sh" ]
