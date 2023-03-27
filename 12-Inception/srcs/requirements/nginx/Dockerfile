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
FROM debian:buster


RUN apt -y update && apt install -y nginx && apt install openssl -y




# COPY ./conf/default /etc/nginx/sites-available/

COPY ./tools/script.sh /



CMD [ "/script.sh" ]
