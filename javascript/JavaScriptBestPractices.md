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