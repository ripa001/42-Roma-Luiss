FROM debian:buster

RUN apt-get -y update && apt-get -y upgrade && apt update -y && apt upgrade -y

RUN apt install php-fpm php-mysql -y && apt install curl -y

# COPY /etc/mysql/mariadb.conf.d/50-server.cnf /etc/mysql/mariadb.conf.d/


COPY ./tools/my_script.sh /
RUN chmod 777 /my_script.sh
COPY ./tools/wp-config.php /




CMD ["/my_script.sh"]