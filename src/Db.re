open Belt;
open Decode.ParseError;
module D = Decode.AsResult.OfParseError;

type colors =
  | Black
  | White;

module Person = {
  type t = {
    id: int,
    name: string,
  };
  let make = (id, name) => {id, name};
  let decode = json: Result.t(t, Decode.ParseError.failure) =>
    D.Pipeline.succeed(make)
    |> D.Pipeline.field("id", D.int)
    |> D.Pipeline.field("name", D.string)
    |> D.Pipeline.run(json);

  let encode = (person): string => Js.Json.stringify(person);
};

module Color = {
  type t = {
    id: int,
    name: colors,
  };

  let make = (id, name) => {id, name};

  let colorToStr = color =>
    switch (color) {
    | Black => "black"
    | White => "white"
    };

  let strToColor = str =>
    switch (str) {
    | "black" => Black
    | "white" => White
    | _ => Js.Exn.raiseError("Unknown color")
    };

  let decode = json: Result.t(t, Decode.ParseError.failure) =>
    D.Pipeline.succeed(make)
    |> D.Pipeline.field("id", D.int)
    |> D.Pipeline.field("name", name =>
         D.string(name)->Result.map(strToColor)
       )
    |> D.Pipeline.run(json);

  let encode = color => Js.Json.stringify(color);
};

type schema =
  | Person(Person.t)
  | Color(Color.t);

type store = ref(Belt.Map.Int.t(string));
let personStore: store = ref(Belt.Map.Int.empty);
let colorStore: store = ref(Belt.Map.Int.empty);

/* Lets you add any record with a supported schema */
let add = (s: schema) =>
  switch (s) {
  | Person(p) =>
    let _ =
      personStore := (personStore^)->Belt.Map.Int.set(p.id, Person.encode(p));
    Belt.Result.Ok();
  | Color(c) =>
    let _ =
      colorStore := (colorStore^)->Belt.Map.Int.set(c.id, Color.encode(c));
    Belt.Result.Ok();
  };

let getPerson = (key: int) => (personStore^)->Belt.Map.Int.getExn(key)->Person.decode;

let getColor = (key: int) =>
  (colorStore^)->Belt.Map.Int.getExn(key)->Color.decode;
