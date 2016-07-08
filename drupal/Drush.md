[Introduction to Drush](https://app.pluralsight.com/courses/drush-introduction)
=========================
By [Addison Berry](http://app.pluralsight.com/author/addison-berry) et als.

# Getting Started

## Installing Drush on Linux with Composer

```
curl https://getcomposer.org/installer | sudo php -- --install-dir=/usr/local/bin --filename=composer
sudo composer global require drush/drush
sudo chown -R $USER ~/.drush
```

`drush --version` // validate version

`drush` // see all drush commands

## Installing Drupal

```
drush dl drupal --default-major=7 --drupal-project-rename=drushfun
drush si --db-url=mysql://root:admin@localhost/drushfun --db-su-pw=MY_PASSWORD
```

### Reinstall Drupal

`drush si -y`

## Site Information

`drush status`

# Drush Commands

## Drush Project Manager

### Query
```
(pm-info) drush pmi [package]
(pm-list) drush pml
(pm-releases) drush rl [packages]
(pm-releasenotes) drush rln [package]
```

### (Un)Install/Update Packages
```
(pm-disable) drush dis [packages] -y
(pm-enable) drush en [packages] -y
drush pm-uninstall [packages] -y
(pm-update) drush up [package]
```

## Drush Commands for Site Administrators

* `drush status`: Site status report
* `(pm-updatecode) drush upc --notes`
* `(pm-updatecode) drush upc --security-only`
* `drush updatedb`
    * OR `(pm-update) drush up` which includes both `upc` and `updatedb`
* `drush watchdog-list` for recent entry logs (actions, cron, etc.)
* `drush cc all` to clear cache
* `drush cron` to run cron jobs
* `drush search-status` to get status of indexes
* `drush search-index`: index site for search

## Helpful Drush Commands for Developers

* `drush cc all` to clear cache
* `drush pm-list` to get a list of packages
* `drush en views` to download and enable module *views*
* `(drupal-directory) drush dd views` to return the absolute path of the module *views*
* `(variable-get) drush vget 'site_name'` to get the value of the variable *site_name*
* `(variable-set) drush vset site_name "Demo site"` to set the value of the variable *site_name* to *Demo site*
* `drush php-eval 'var_dump(user_load(1));'` to evaluate php script within drupal environment
* `drush genc 100` to generate 100 nodes (devel-generate module)
* `drush genu 100` to generate 100 user accounts (devel-generate module)
* `drush upwd "admin" --password="my-new-password"`

### SQL

* `drush sql-cli` to connect to the database command line
* `drush sql-conf` to get the configuration details of the sql database
* `(sql-query) drush sqlq "SELECT * FROM node WHERE nid=1"`
* `drush sql-dump --gzip --result-file` to make a backup of the database inside `~/drush-backups/project-name/YYYYMMDDHHSS/`
