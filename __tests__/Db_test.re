open Jest;
open Expect;
open Db;
describe("ReasonDb stores a person", () => {
  test("To store a Person", () => {
    let me: Person.t = {id: 0, name: "alex"};
    let _ = add(Person(me));
    expect(getPerson(0)) |> toEqual("alex");
  })
});
