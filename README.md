# Reasonable JSON DB
A toy JS JSON DB written with ReasonML.

# Example.re

```reason
open Db;
let me: Person.t = {id: 0, name: "alex"};
let _ = add(Person(me));
Js.log(getPerson(0));
```
