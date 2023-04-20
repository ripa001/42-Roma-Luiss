#!/bin/sh

#wait for mariadb, then connect with credentials

while ! mariadb -h$DB_HOSTNAME -u$DB_USER -p$DB_PWD $DB_NAME &>/dev/null;
do
    sleep 3
    echo "waiting..."
	echo "Host: $DB_HOSTNAME\n\
			User: $DB_USER\n\
			Pwd: $DB_PWD\n\
			Name: $DB_NAME\n " 
done

if [ ! -f "/var/www/html/wordpress/index.php" ];
then

	mv /tmp/index.html /var/www/html/wordpress/index.html

	wp core download --allow-root
	wp config create --dbname=$DB_NAME --dbuser=$DB_USER --dbpass=$DB_PWD --dbhost=$DB_HOSTNAME --dbcharset="utf8" --dbcollate="utf8_general_ci" --allow-root
	wp db create --allow-root
	wp core install --url=$DOMAIN_NAME --title="Inception" --admin_user=$WP_ADMIN_USR --admin_password=$WP_ADMIN_PWD --admin_email=$WP_ADMIN_EMAIL --skip-email --allow-root
	wp user create $WP_USR $WP_EMAIL --role=author --user_pass=$WP_PWD --allow-root
	wp theme activate twentytwentythree --allow-root

fi

echo "WORDPRESS START STATUS : OK"

/usr/sbin/php-fpm7 -F -R