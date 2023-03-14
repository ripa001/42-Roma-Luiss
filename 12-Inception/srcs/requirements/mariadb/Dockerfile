FROM debian:buster

RUN apt-get update -y && apt-get install mariadb-server -y

COPY /etc/mysql/mariadb.conf.d/50-server.cnf /etc/mysql/mariadb.conf.d/


COPY ./tools/script.sh /


CMD ["/script.sh"]