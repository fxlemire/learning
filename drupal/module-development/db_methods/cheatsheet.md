http://drupal.org/developing/api/database

# SELECT QUERY

* SQL

```
SELECT column1, column2, columnN
FROM {tablename}
WHERE column1 = $value1
AND column2 <> $value2
ORDERBY 'sticky', DESC
ORDERBY 'created', DESC
LIMIT 10;
```

* Drupal 7

```
$query = db_select('tablename', 'optional alias')
    ->fields('tablename or alias if given', array('column1', 'column2', ..., 'columnN'))
    ->condition('column1', 'value1')
    ->condition('column2', 'value2', 'optional <>')
    ->orderBy('sticky', 'DESC')
    ->orderBy('created', 'DESC')
    ->limit(variable_get('default_nodes_main', 10))
    ->extend('PagerDefault');

return $query->execute()->fetch();

// Calling fields() with no field list will result in a "SELECT *" query.
```

# INSERT QUERY

* SQL

```
INSERT INTO {tablename} ('column1', 'column2') VALUES ('value1', 'value2');
```


* Drupal 7

```
$query = db_insert('tablename')
    ->fields(array('column1', 'column2'))
    ->values(array('column1' => 'value1', 'column2' => 'value2'))
    ->execute();
```

# UPDATE QUERY

* SQL

```
UPDATE {tablename}
SET column1 = value1, column2 = value2
WHERE column3 >= value3;
```

* Drupal 7

```
$query = db_update('tablename')
    ->fields(array('column1' => 'value1', 'column2' => 'value2'))
    ->condition('column3', 'value3', '>=')
    ->execute();

// The third parameter for ->condition() is optional and defaults to "="
```

# MERGE QUERY

* SQL

```
// In tablename, if the field = value exists, update field1 = value1 && field2 = value2
UPDATE {tablename} SET column1 = value1, column2 = value2 WHERE column = value;

// If tablename, if the field = value does NOT exists
INSERT INTO {tablename} ('column', 'column1', 'column2') VALUES ('value', 'value1', 'value2');
```

* Drupal 7

```
db_merge('tablename')
    ->key(array('column' => 'value'))
    ->fields(array(
        'column1' => 'value1',
        'column2' => 'value2'
    ))
    ->execute();
```

# DELETE QUERY

* SQL

```
DELETE FROM {tablename} WHERE column = value;
```

* Drupal 7

```
$query = db_delete('tablename')
    ->condition('column', 'value')
    ->execute();
```
