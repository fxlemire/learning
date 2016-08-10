Debugging a PHP Website Hosted on a VM With VS Code and XDebug On Windows
=========================================================================

# On Your VM

0. Install XDebug: `sudo apt-get install php5-xdebug`
0. Add the following lines to your main php.ini
    * mine is located at /etc/php5/fpm/php.ini
    * find yours in 'Loaded Configuration File' from phpinfo() in your index.php

```
[XDEBUG]
xdebug.remote_autostart=1
xdebug.remote_enable=1
xdebug.remote_port=9000
xdebug.remote_host=[YOUR HOST IP]
```

* [YOUR HOST IP] on Windows, type in your terminal ipconfig (mine is 192.168.1.200)

0. sudo service php5-fpm restart
0. sudo service nginx restart

# On VS Code

0. In Extensions, install PHP Debug
0. In DEBUG, click on the cog -> PHP
0. Your launch.json should look like that:

```
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Listen for XDebug",
      "type": "php",
      "request": "launch",
      "port": 9000,
      "localSourceRoot": "c:/Users/myuser/path/to/public_html",
      "serverSourceRoot": "/var/www/html"
    },
    {
      "name": "Launch currently open script",
      "type": "php",
      "request": "launch",
      "program": "${file}",
      "cwd": "${fileDirname}",
      "port": 9000
    }
  ]
}
```

* "c:/Users/myuser/path/to/public_html": path to your website files on your host
* "/var/www/html": path to your website files on your VM

# Port Forwarding

0. In VirtualBox, right-click on your VM -> Settings -> Network -> Advanced -> Port Forwarding
    * Set the following rule:
        * php-xdebug | TCP | 127.0.0.1 | 9000 | | 9000

# Enjoy

0. Set some breakpoints on the files you want to debug, press F5, and launch your website!
