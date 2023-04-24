#!/bin/sh

if [ ! -d "/run/mysqld" ];
then
    mkdir -p /run/mysqld
    chown -R mysql:mysql /run/mysqld
fi

if [ ! -d "/var/lib/mysql/mysql" ];
then
    chown -R mysql:mysql /var/lib/mysql
    echo "MariaDB first launch: OK"
    mysql_install_db --basedir=/usr --datadir=/var/lib/mysql --user=mysql --rpm > /dev/null
    echo "MariaDB first launch 2: OK"

    tmp=`mktemp`
    if [ ! -f "$tmp" ];
    then
        return 1
    fi
    cat << EOF > $tmp

USE mysql;
FLUSH PRIVILEGES;
DELETE FROM mysql.user WHERE User='';
DROP DATABASE test;
DELETE FROM mysql.db WHERE Db='test';
DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1');
ALTER USER 'root'@'localhost' IDENTIFIED BY '12345';
CREATE DATABASE $DB_NAME CHARACTER SET utf8 COLLATE utf8_general_ci;
CREATE USER '$DB_USER'@'%' IDENTIFIED BY '$DB_PWD';
GRANT ALL PRIVILEGES ON $DB_NAME.* TO '$DB_USER'@'%';
FLUSH PRIVILEGES;
EOF
    /usr/bin/mysqld --user=mysql --bootstrap < $tmp
    echo "MariaDB first launch 2: OK"

    rm -f $tmp 
fi

sed -i "s|skip-networking|# skip-networking|g" /etc/my.cnf.d/mariadb-server.cnf
sed -i "s|.*bind-address\s*=.*|bind-address=0.0.0.0|g" /etc/my.cnf.d/mariadb-server.cnf

echo "MariaDB starting: OK"

exec /usr/bin/mysqld --user=mysql --console
