Db.add({id: 1, name: "hannibal"})
->Future.tapOk(() => Js.log("Stored something!"))
->Future.tapError(
    err => {
      Js.log("Something went wrong :(");
      Js.log(err);
    },
  );
