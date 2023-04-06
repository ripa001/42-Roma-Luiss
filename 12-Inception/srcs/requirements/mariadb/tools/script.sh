#!/bin/bash

service mysql start 

echo $DB1_PWD $DB1_USER $DB1_NAME

echo "CREATE DATABASE IF NOT EXISTS $DB1_NAME ;" > db1.sql
echo "CREATE USER IF NOT EXISTS '$DB1_USER'@'%' IDENTIFIED BY '$DB1_PWD' ;" >> db1.sql
echo "GRANT ALL PRIVILEGES ON $DB1_NAME.* TO '$DB1_USER'@'%' ;" >> db1.sql
echo "ALTER USER 'root'@'localhost' IDENTIFIED BY '12345' ;" >> db1.sql
echo "FLUSH PRIVILEGES;" >> db1.sql

mysql < db1.sql

kill $(cat /var/run/mysqld/mysqld.pid)

mysqld