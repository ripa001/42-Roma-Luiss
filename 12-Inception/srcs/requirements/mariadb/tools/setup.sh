#!/bin/sh

mysql_install_db --user=root --datadir=/var/lib/mysql
/usr/bin/mysqld --user=root --init_file=/init_file