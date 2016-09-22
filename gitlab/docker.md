Host GitLab Community Edition With Docker on Windows
===================================

# 1. Host GitLab Community Edition locally with Docker VM system volumes for data

```
docker pull ubuntu:14.04
docker create \
  --volume /srv/gitlab/config:/etc/gitlab \
  --volume /srv/gitlab/logs:/var/log/gitlab \
  --volume /srv/gitlab/data:/var/opt/gitlab \
  --name gitlab-store ubuntu:14.04 /bin/true

docker pull gitlab/gitlab-ce
docker run --detach \
  --hostname gitlab.webjomp.com \
  --publish 44300:443 --publish 4000:80 --publish 2200:22 \
  --name gitlab \
  --volumes-from gitlab-store \
  gitlab/gitlab-ce:latest
```

You will need to apply port forwarding in your VM used by Docker. Forward host 127.0.0.1:4000 to guest port 4000. (Also your host internal IP if you want to access it from other computers at home.) Do the same for 127.0.0.1:44300 -> 44300 and 127.0.0.1:2200 -> 2200.

## 2. Backup and Migrate

```
docker run --rm --volumes-from gitlab-store -v $(pwd):/backup ubuntu tar cvf /backup/redmine-files.tar /usr/src/gitlab/files
docker exec -it gitlab-mariadb /bin/bash
> mysqldump -u root -pSUPER_SECRET_PW gitlab > /root/gitlab-mariadb-backup.sql
> ctrl+p+q
docker cp gitlab-mariadb:/root/gitlab-mariadb-backup.sql .
```

Then on the new computer, do the steps in *1.*. After that:
```
docker cp gitlab-mariadb-backup.sql gitlab-mariadb:/root
docker exec -it gitlab-mariadb /bin/bash
> mysql -u root -pSUPER_SECRET_PW gitlab < /root/gitlab-mariadb-backup.sql
> rm /root/gitlab-mariadb-backup.sql
> ctrl+p+q
docker cp gitlab-files.tar gitlab:/root
docker exec -it gitlab /bin/bash
> cd /usr/src/gitlab/files
> tar xvf /root/gitlab-files.tar --strip 4
> rm /root/gitlab-files.tar
> ctrl+p+q
```

## 3. Other Useful Operations

A [blog](https://getcarina.com/docs/tutorials/data-volume-containers/) containing useful operations for data volume containers
