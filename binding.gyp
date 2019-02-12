{
  "targets": [
    {
      "target_name": "tictactoe",
      "sources": [ "TicTacToe_Minimax/TicTacToe_Minimax.cpp"],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "defines": [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }
  ]
}