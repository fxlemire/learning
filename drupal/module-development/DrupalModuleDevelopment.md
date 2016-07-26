Drupal Module Development
=========================

# API References

* https://api.drupal.org/api/drupal/7.x

# Sanitization

* check_plain()
    * displays any special character as plain text
* check_markup()
    * like filtered_html format
* check_url() & l()
    * strips dangerous protocols
* t()
    * allows translation and also variable substitution where those variables can be sanitized prior to output
* filter_xss()
    * similar to filtered_html format. removes html tags that are not whitelisted.
    * removes everything that can cause a cross site scripting attack
* filter_xss_admin()
    * allows all html tags but removes scripts and styles attributes
* drupal_mail
    * doesn't allow headers to be injected
* db_merge
    * use the query builders with variable replacements to safely handle data

# Render

* render_example
* [Render Arrays in Drupal 7](https://drupal.org/node/930760)

# Queries

* `$node = db_query('SELECT nid, title FROM {node} WHERE type = :type AND nid = :nid', array(':type => $type, ':nid' => $nid))->fetchObject();`
* [All fetch functions on Drupal API](https://api.drupal.org/api/drupal/includes%21database%21database.inc/interface/DatabaseStatementInterface/7.x)
* http://drupal.org/developing/api/database
* http://upgrade.boombatower.com
    * [SQL Conversion Tool](http://dupgrade.com/tools/sql/inline)

```
$select = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->condition('promote', 1)
    ->condition('status', 1)
    ->orderBy('sticky', 'DESC')
    ->orderBy('created', 'DESC')
    ->extend('PagerDefault')
    ->limit(variable_get('default_nodes_main', 10))
    ->addTag('node_access')
    ->execute();
```

* INSERT INTO node (title, uid) VALUES ("Example", 1)
```
$nid = db_insert('node')
    ->fields(array('title', 'uid'))
    ->values(array('title' => 'Example', 'uid' => 1))
    ->execute();
```

* UPDATE node SET title = "Example", uid = 1 WHERE created >= (UNIX_TIMESTAMP() - 3600)
```
$num_updated = db_update('node')
    ->fields(array('uid' => 5, 'status' => 1))
    ->condition(P'created', REQUEST_TIME - 3600, '>=')
    ->execute();
```

* DELETE FROM node WHERE nid = 5
```
$num_deleted = db_delete('node')
    ->condition('nid', 5)
    ->execute();
```

* Hook query alter
```
function hook_query_alter(&$query) {
    if ($query->hasTag('node_access')) {
        $query->condition('created', time() - 3600, '>');
    }
}

$select = db_select('node', 'n')
    ...
    ->addTag('node_access');
```

* Connect to multiple database types at the same time
```
$databases['default']['default'] = array(
    'driver' => 'mysql',
    'database' => 'databasename',
    'username' => 'username',
    'password' => 'password',
    'host' => 'localhost',
    'prefix' => ''
);

$databases['external']['default'] = array(
    'driver' => 'oracle',
    'database' => 'bigdb',
    'username' => 'scott',
    'password' => 'tiger',
    'host' => 'bigdb.externalsite.com',
    'prefix' => ''
);
```
