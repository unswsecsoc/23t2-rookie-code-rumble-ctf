const express = require("express");
const path = require("path");

const app = express();
const port = 8000;

const FLAG = "BEGINNER{java5cr1pt_15_an_0dd_langu4g3}";

app.use(express.json());

const createNumberedPairs = (arr) => {
  const indexes = Object.keys(arr);
  const values = arr;

  const result = [];

  for (let i = 0; i < indexes.length; i++) {
    result.push([indexes[i], values[i]]);
  }

  return result;
};

const numberedPairsToArray = (numberedPairs) => {
  const arr = [];

  for (let i = 0; i < numberedPairs.length; i++) {
    const currentPair = numberedPairs[i];
    arr.push(currentPair[1]);
  }

  return arr;
};

const challenge = (payload) => {
  const beforeSnapshot = JSON.stringify(payload);

  const pairs = createNumberedPairs(payload);
  const recovered = numberedPairsToArray(pairs);

  const afterSnapshot = JSON.stringify(recovered);

  // Recovered should be the same as payload, right?
  if (beforeSnapshot !== afterSnapshot) {
    return "Congrats! You broke my code somehow. Have a flag: " + FLAG;
  } else {
    return "My code behaved normally! Value: " + afterSnapshot;
  }
};

app.post("/api/challenge", (req, res) => {
  res.send(challenge(req.body));
});

app.use("/", express.static(path.join(__dirname, "static")));

app.listen(port, () => {
  console.log(`App listening on port ${port}`);
});
