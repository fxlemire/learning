Host Redmine With Docker on Windows
===================================

# 1. Host Redmine locally with a MariaDB container with Docker VM system volumes for data

```
docker pull ubuntu:14.04
docker create -v /var/lib/mysql -v /usr/src/redmine/files --name redmine-store ubuntu:14.04 /bin/true

docker pull mariadb
docker run --name redmine-mariadb --volumes-from redmine-store -e MYSQL_ROOT_PASSWORD=SUPER_SECRET_PW -e MYSQL_DATABASE=redmine -d mariadb:latest

docker pull redmine
docker run --name redmine --volumes-from redmine-store --link redmine-mariadb:mysql -p 3000:3000 -d redmine:latest
```

You will need to apply port forwarding in your VM used by Docker. Forward host 127.0.0.1:3000 to guest port 3000. (Also your host internal IP if you want to access it from other computers at home.)

## 2. Backup and Migrate

```
docker run --rm --volumes-from redmine-store -v $(pwd):/backup ubuntu tar cvf /backup/redmine-files.tar /usr/src/redmine/files
docker exec -it redmine-mariadb /bin/bash
> mysqldump -u root -pSUPER_SECRET_PW redmine > /root/redmine-mariadb-backup.sql
> ctrl+p+q
docker cp redmine-mariadb:/root/redmine-mariadb-backup.sql .
```

Then on the new computer, do the steps in *1.*. After that:
```
docker cp redmine-mariadb-backup.sql redmine-mariadb:/root
docker exec -it redmine-mariadb /bin/bash
> mysql -u root -pSUPER_SECRET_PW redmine < /root/redmine-mariadb-backup.sql
> rm /root/redmine-mariadb-backup.sql
> ctrl+p+q
docker cp redmine-files.tar redmine:/root
docker exec -it redmine /bin/bash
> cd /usr/src/redmine/files
> tar xvf /root/redmine-files.tar --strip 4
> rm /root/redmine-files.tar
> ctrl+p+q
```

## 3. Other Useful Operations

A [blog](https://getcarina.com/docs/tutorials/data-volume-containers/) containing useful operations for data volume containers
