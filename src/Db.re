type person = {
  id: int,
  name: string,
};
type storable = person;
let add = (storable: storable): Future.t(Belt.Result.t(unit, string)) =>
  Future.make(resolve => {
    Js.Global.setTimeout(() => resolve(Belt.Result.Ok()), 2000);
  });
