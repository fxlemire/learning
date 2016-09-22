Useful Docker Commands
======================

* Clear Dangling Volumes (2 different ways)
    * `docker volume ls -qf dangling=true | xargs -r docker volume rm`
    * `docker volume rm $(docker volume ls -qf dangling=true)`
