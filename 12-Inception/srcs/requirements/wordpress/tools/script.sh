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
	####### BONUS PART ################

	## redis ##
	echo "REDIS START STATUS : OK"
	wp config set WP_REDIS_HOST 127.0.0.1 --allow-root #I put --allowroot because i am on the root user on my VM
	wp config set WP_REDIS_PORT 6379 --raw --allow-root
	wp config set WP_CACHE_KEY_SALT $DOMAIN_NAME --allow-root
	wp config set WP_CACHE true --allow-root
	wp config set WP_REDIS_PASSWORD $REDIS_PASSWORD --allow-root
	wp config set WP_REDIS_SELECTIVE_FLUSH true --allow-root
	# wp config set WP_REDIS_CLIENT phpredis --allow-root
# 	define('WP_CACHE_KEY_SALT', 'your_unique_key_here');
# define('WP_CACHE', true);
# define('WP_REDIS_HOST', '127.0.0.1');
# define('WP_REDIS_PORT', '6379');
# define('WP_REDIS_PASSWORD', 'your_redis_password_here');
# define('WP_REDIS_SELECTIVE_FLUSH', true);
	echo "REDIS CONFIG STATUS : OK"
	wp plugin install redis-cache --activate --allow-root
	cat  wp-config.php
	
	wp plugin update --all --allow-root
	wp redis enable --allow-root
	echo "REDIS PLUGIN STATUS : OK"

	echo "REDIS STATUS : OK"
	###  end of redis part  ###

fi

echo "WORDPRESS START STATUS : OK"

/usr/sbin/php-fpm7 -F -R