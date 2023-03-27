FROM debian:buster

RUN apt update -y && apt upgrade -y

RUN apt install vsftpd -y

COPY ./tools/script.sh /

CMD ["/script.sh"]