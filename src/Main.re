Db.add({id: 1, name: "hannibal"}, Db.store)
->Future.tapOk((m) => Js.log(m))
->Future.tapError(
    err => {
      Js.log("Something went wrong :(");
      Js.log(err);
    },
  );
