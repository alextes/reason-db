open Db;
let me: Person.t = {id: 0, name: "alex"};
let _ = add(Person(me));
Js.log(getPerson(0));
// alex
