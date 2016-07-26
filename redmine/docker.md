Host Redmine With Docker on Windows
===================================

Host Redmine locally with a MariaDB container with host system volumes for data

```
docker pull ubuntu:14.04
docker create -v /var/lib/mysql -v /usr/src/redmine/files --name redmine-store ubuntu:14.04 /bin/true

docker pull mariadb
docker run --name redmine-mariadb --volumes-from redmine-store -e MYSQL_ROOT_PASSWORD=SUPER_SECRET_PW -e MYSQL_DATABASE=redmine -d mariadb:latest

docker pull redmine
docker run --name redmine --volumes-from redmine-store --link redmine-mariadb:mysql -p 3000:3000 -d redmine:latest
```

You will need to apply port forwarding in your VM used by Docker. Forward host 127.0.0.1:3000 to guest port 3000. (Also your host internal IP if you want to access it from other computers at home.)

A [blog](https://getcarina.com/docs/tutorials/data-volume-containers/) containing useful operations for data volume containers
