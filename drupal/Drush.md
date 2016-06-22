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


