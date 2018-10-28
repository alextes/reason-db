module Person = {
  type t = {
    id: int,
    name: string,
  };

  let compare = (p1, p2) => p1.id - p2.id;

  let decode = json =>
    Json.Decode.{
      id: json |> field("id", int),
      name: json |> field("name", string),
    };

  let encode = person =>
    Json.Encode.(
      object_([("id", int(person.id)), ("name", string(person.name))])
    );
};

module type Storable = {
  type t = {id: int};
  let encode: t => string;
  let decode: string => t;
};

module Int = {
  type t = int;
  let compare = compare;
};
module IntMap = Map.Make(Int);
let store = IntMap.empty;
let add = (person: Person.t, store) => {
  let m = IntMap.add(person.id, Person.encode(person), store);
  Future.value(Belt.Result.Ok(m));
};
