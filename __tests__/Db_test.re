open Jest;
open Expect;
open Db;

test("To store a Person", () => {
  let me: Person.t = {id: 0, name: "alex"};
  let _ = add(Person(me));
  expect(getPerson(me.id)) |> toEqual(Person(me));
});