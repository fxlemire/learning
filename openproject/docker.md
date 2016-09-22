Host OpenProject With Docker on Windows
===================================

# 1. Host OpenProject locally with Docker VM system volumes for data

```
docker pull ubuntu:14.04
docker create \
  -v /var/lib/openproject/pgdata:/var/lib/postgresql/9.4/main \
  -v /var/lib/openproject/logs:/var/log/supervisor \
  -v /var/lib/openproject/static:/var/db/openproject \
  --name openproject-store ubuntu:14.04 /bin/true

docker pull openproject/community:6.0
docker run -d -p 3001:80 --name openproject -e SECRET_KEY_BASE=SUPER_SECRET_PW \
  --volumes-from openproject-store openproject/community:6.0
```

You will need to apply port forwarding in your VM used by Docker. Forward host 127.0.0.1:3001 to guest port 3001. (Also your host internal IP if you want to access it from other computers at home.)

## 2. Backup and Migrate

```
docker run --rm --volumes-from openproject-store -v $(pwd):/backup ubuntu tar cvf /backup/redmine-files.tar /usr/src/openproject/files
docker exec -it openproject-mariadb /bin/bash
> mysqldump -u root -pSUPER_SECRET_PW openproject > /root/openproject-mariadb-backup.sql
> ctrl+p+q
docker cp openproject-mariadb:/root/openproject-mariadb-backup.sql .
```

Then on the new computer, do the steps in *1.*. After that:
```
docker cp openproject-mariadb-backup.sql openproject-mariadb:/root
docker exec -it openproject-mariadb /bin/bash
> mysql -u root -pSUPER_SECRET_PW openproject < /root/openproject-mariadb-backup.sql
> rm /root/openproject-mariadb-backup.sql
> ctrl+p+q
docker cp openproject-files.tar openproject:/root
docker exec -it openproject /bin/bash
> cd /usr/src/openproject/files
> tar xvf /root/openproject-files.tar --strip 4
> rm /root/openproject-files.tar
> ctrl+p+q
```

## 3. Other Useful Operations

A [blog](https://getcarina.com/docs/tutorials/data-volume-containers/) containing useful operations for data volume containers
