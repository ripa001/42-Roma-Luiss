# FROM alpine:3.13

# RUN	apk update && apk upgrade && apk add --no-cache \
#         nginx \
#         openssl

# # nginx SSL
# # RUN mkdir /etc/nginx/ssl
# # RUN openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes \
# #     -out /etc/nginx/ssl/dripanuc.pem \
# #     -keyout /etc/nginx/ssl/dripanuc.key \
# # 	-subj "/C=IT/ST=Italy/L=Rome/O=42/OU=42/CN=dripanuc"

# # RUN mkdir -p /run/nginx
# # COPY conf/nginx.conf /etc/nginx/conf.d/default.conf

# # ENTRYPOINT ["nginx", "-g", "daemon off;"]
# COPY ./tools/script.sh /



# CMD [ "/script.sh" ]

FROM    alpine:3.13

RUN     apk update && apk upgrade && \
        apk add --no-cache nginx openssl

RUN     mkdir -p /etc/nginx/ssl
RUN     mkdir -p /run/nginx

RUN     mkdir -p /var/www/html

RUN     openssl req -newkey rsa:2048 \
        -x509 \
        -sha256 \
        -days 365 \
        -nodes \
        -keyout /etc/nginx/ssl/inception.key \
        -out /etc/nginx/ssl/inception.pem \
        -subj "/C=IT/ST=Italy/L=Rome/O=42Rome/OU=$USER/CN=$USER"

COPY    conf/nginx.conf /etc/nginx/conf.d/default.conf

ENTRYPOINT [ "nginx", "-g", "daemon off;" ]



# FROM debian:buster


# RUN apt -y update && apt install -y nginx && apt install openssl -y

# # RUN mkdir -p /run/nginxù
# # COPY conf/default /etc/nginx/sites-available/



# # COPY ./conf/default /etc/nginx/sites-available/

# COPY ./tools/script.sh /



# CMD [ "/script.sh" ]
