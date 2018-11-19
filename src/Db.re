type names =
  | Black
  | White;

module Person = {
  type t = {
    id: int,
    name: string,
  };
  let decode = str => {
    let json = Json.parseOrRaise(str);
    Json.Decode.{
      id: json |> field("id", int),
      name: json |> field("name", string),
    };
  };

  let encode = person =>
    Json.Encode.(
      object_([("id", int(person.id)), ("name", string(person.name))])
    )
    ->Json.stringify;
};

module Color = {
  type t = {
    id: int,
    name: names,
  };

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

  let decode = str => {
    let json = Json.parseOrRaise(str);
    Json.Decode.{
      id: json |> field("id", int),
      name: json |> map(strToColor, string),
    };
  };

  let encode = color =>
    Json.Encode.(
      object_([
        ("id", color.id->int),
        ("name", color.name->colorToStr->string),
      ])
    )
    ->Json.stringify;
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

let getPerson = (key: int) =>
  (personStore^)->Belt.Map.Int.getExn(key)->Person.decode->Person;

let getColor = (key: int) =>
  (colorStore^)->Belt.Map.Int.getExn(key)->Color.decode->Color;
