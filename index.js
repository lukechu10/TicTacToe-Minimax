const tictactoe = require("./build/Release/tictactoe.node");

var data = [
    [ '_', '_', '_'],
    [ 'o', 'x', '_'],
    [ '_', '_', '_']];

console.log(typeof data);
console.log(typeof data[0]);

console.log(tictactoe.bestMove(data));