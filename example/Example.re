open Db;
let me: Person.t = {id: 0, name: "alex"};
// let me: add((me))
let _ = add(Person(me));
let getMe = Person(me);
Js.log(getPerson(0));
// alex
