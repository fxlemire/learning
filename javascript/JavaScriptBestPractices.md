JavaScript Best Practices
=========================
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
