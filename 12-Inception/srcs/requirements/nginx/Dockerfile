FROM debian:buster

RUN apt update -y && apt upgrade -y

RUN apt install -y nginx && apt install openssl -y

RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
	-keyout /etc/ssl/private/dripanuc.key \
	-out /etc/ssl/certs/dripanuc.pem \
	-subj "/C=IT/ST=Italy/L=Rome/O=42/OU=42/CN=[dripanuc.42.fr](http://dripanuc.42.fr/)"

RUN mkdir -p /run/nginx
COPY conf/nginx.conf /etc/nginx/conf.d/default.conf

ENTRYPOINT ["nginx", "-g", "daemon off;"]