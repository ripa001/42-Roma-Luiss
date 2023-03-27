FROM debian:buster

RUN apt-get -y update && apt-get -y upgrade && apt update -y && apt upgrade -y

RUN apt install php-fpm php-mysql -y && apt install curl -y

# COPY /etc/mysql/mariadb.conf.d/50-server.cnf /etc/mysql/mariadb.conf.d/


COPY ./tools/script.sh /
RUN chmod 777 /script.sh
COPY ./tools/wp-config.php /




CMD ["/script.sh"]