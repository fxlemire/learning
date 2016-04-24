[JavaScript Best Practices](http://app.pluralsight.com/courses/javascript-best-practices)
=========================
By [Jonathan Mills](http://app.pluralsight.com/author/jonathan-mills)

**Consistency is key**

# Syntax

## Semicolons: always
* Use semicolons in conjunction with ESLint (or JSHint) to prevent potential issues
  * Because in some cases, semicolons are not required, unexpected behavior may arise. Enforcing the use of semicolons
  will help us detect those undesired situations.
  * Also consistent with other languages

## Linting: ESLint
* JSHint: simple and easy to use
* ESLint: more advanced, extensions can be used
  * This one is my preference. Behaves really well with JS frameworks such as React or Angular

## Curly Braces: opening on the same line
We do them the Java way, not the C way. It's not just a matter of taste, it's a matter of automatic semicolon insertion.

```
return
{
  get,
  set
}
```

The above code is not valid because a semicolon will be automatically inserted after `return`. Doing `return {` will work just fine.

So if sometimes we must, then always we should.

## Equality: ===
* ==
  * `1 == '1'` returns true. So will `1 == true`, `0 == false`.
  * == does a type conversion before comparing
* ===
  * All the examples of `==` will return false.
  * It first checks if the type is equal. If so, it compares, it not, it returns false.

Also, doing `if (x)` is bad practice, because code can blow up. `if (typeof x !== 'undefined')` should be used instead.

## Variables: declared at the top
```
console.log(myVar);
var myVar = 10;
```

What actually happens behind the scenes is the following:

```
var myVar;
console.log(myVar);
myVar = 10;
```

To avoid potential confusion: declare all your variables at the top.

## Functions: Function Declarations
* Avoid using function expressions (`var myFunc = func() {};`). Use Declarations instead (`myFunc() {}`).
* Declare them right after your variables.

```
// variables first
var x = 10;

// functions next
function print(input) {
  // variables first
  var x = 0;

  // functions next
  function log() {
    // log stuff
  }

  // run code
  console.log(input);
}

// run code
print(10);
```

# Behaviors

## Strict Mode: `'use strict';`
* Spits out clean errors instead of hiding problems.
* Fixes situations such as creating unintently global variables by forgetting `var`.
* `'use strict';` only applies to its scope.
* Spits out errors when otherwise it would not. For example:
  * Read Only Properties
    * When setting read-only properties and trying to overwrite it later on
  * Deleting Properties
    * `delete` can't delete everything. When illegal, it will only blow up when using strict mode.
    * use `Reflect.deleteProperty` instead.
  * Duplicates
    * in function arguments
  * Octals and Hexadecimals
    * Prevents them. If we really need to use them, then use `parseInt(myNumber, 8)`

## With: never use
Don't use with because of the following problem:

```
var obj = {a: {b: {c: 'hello'}}};
var c = 'this is important';

with (obj.a.b.) {
  console.log(c);
}
```

Strict mode forbids `with`.

If you need to simplify your code, do the following instead:
```
var obj = {a: {b: {c: 'hello'}}};
var c = 'this is important';

(function(newVar) {
  console.log(newVar);
}(obj.a.b.c))
```

## What is This Anyway?
`this` gets bound to the container object.
```
var obj = {
  val: 'Hi there',
  printVal: function() {console.log(this.val);}
};
// obj.printVal() prints 'Hi there'

var print = obj.printVal;
print(); // problem, nothing on the left side for this to refer to! `this` gets bound to the global scope
```
Without `strict` mode, if this does not exist, we will get undefined.
With `strict` mode, we will get an error.

## This in New Objects: `var _this = this`
The `new` keyword binds a new `this` scope onto the function.

Various problems can occur. For example:

```
var obj = function() {
  console.log(this);
  this.hello = 'hello';
  this.greet = function() {
    console.log(this.hello);
  }
  this.delayGreeting = function() {
    setTimeout(this.greet, 1000);
  }
};

var greeter = new obj();

greeter.delayGreeting();
```

The timeout is actually executing a callback, being `this.greet`.
```
function setTimeout(cb, val) {
  cb();
}
```
So it does `cb()`. There is nothing
on the left of the call (no `this` bound), so it will fail.

The best practice is to do `var _this = this` and use `_this` in our code everwhere instead of `this`,
whenever we are dealing with the `this` keyword.

# Async Patterns

## Callbacks: stop using anonymous functions
* To avoid callbacks hell (nested callbacks within nested callbacks within .... you get the point!), declare named functions instead.
* If you need access to a variable outside of your new function, use a closure instead of passing it as an argument
* Error Handling: always use `return` when calling `done()` to make sure you are exiting and make it explicit that you're leaving the function.
```
if (err) {
  return done(err, null);
}
```

## Promises
Promises can replace callbacks. (<ES7: use [PromiseJS](https://www.promisejs.org/) or Node) (ES7: use `async`, `await`)

For example:
```
function asyncMethod(m, cb) {
  setTimeout(() => {
    console.log(m);
    cb();
  }, 500);
}

asyncMethod('Open DB Connection', () => {
  asyncMethod('Find User', () => {
    asyncMethod('Validate User', () => {
      asyncMethod('Do Stuff', () => {});
    });
  });
});
```
could be the following:

PromiseJS:
```
function asyncMethod(m) {
  return new Promise((fulfill, reject) => {
    setTimeout(() => {
      console.log(m);
      fulfill();
    }, 500);
  });
}

function findUser() {
  return asyncMethod('Find User');
}

function validateUser() {
  return asyncMethod('Validate User');
}

function doStuff() {
  return asyncMethod('Do Stuff');
}

asyncMethod('Open DB Connection')
  .then(findUser, new Error())
  .then(validateUser)
  .then(doStuff);
  .then(() => {});
```

## Async - Await (ES7)
```
function asyncMethod(m) {
  return new Promise((fulfill, reject) => {
    setTimeout(() => {
      console.log(m);
      fulfill();
    }, 500);
  });
}

function findUser() {
  return asyncMethod('Find User');
}

function validateUser() {
  return asyncMethod('Validate User');
}

function doStuff() {
  return asyncMethod('Do Stuff');
}

async function main() {
  await asyncMethod('Open DB Connection');
  await findUser();
  await validateUser();
  await doStuff();
}

main();
```

```
function asyncMethod(m, num) {
  return new Promise((fulfill, reject) => {
    setTimeout(() => {
      console.log(`${m} ${num}`);
      fulfill(num + 1);
    }, 500);
  });
}

async function main() {
  let one = await asyncMethod('Open DB Connection', 0);
  let two = await asyncMethod('Find User', one);
  let three = await asyncMethod('Validate User', two);
  let four = await asyncMethod('Do Stuff', three);
}
```

# Production Code

## NPM Settings
* `npm init`
* `npm config set save-exact=true`
  * saves the exact version of the installed package (will not prepend with `^`)
* `"engines": {"node": "<4.2.1"}`

## Environmental Variables
### [Foreman](https://github.com/strongloop/node-foreman)
* `npm install -g foreman`
* `nf start` instead of `node start`
* create a .env file. Foreman will stick it into the `process.env` environment.
```
{
    "port": 9000,
    "connection": {
      "sql": "",
      "mongo": ""
    }
}
```

## Cross Platform Concerns
* Name all files with lowercase and replace spaces by dashes.
  * If the case is not respected in a path, it works fine on Windows and Mac, but will blow up on Linux. This can lead to unexpected errors.

## Simplify Your World
### KISS Principal
Keep it simple... (smarty?)

Don't confuse 'Doing things the best way' with 'Using tools'.

Don't use things because they're cool. Use them because they're useful to you.
