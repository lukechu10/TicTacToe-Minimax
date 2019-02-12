// TicTacToe Minimax.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 
#include "pch.h"

// C++ program to find the next optimal move for 
// a player 


namespace Game {
	#define positive 11
	#define negative -11
	
	using namespace std;
	
	constexpr char opponent = 'o'; // min
	constexpr char computer = 'x'; // max
	
	unsigned int minimaxCout = 0;
	unsigned bestDepth = 0;
	
	class Move {
	public:
		signed int value;
		unsigned int row;
		unsigned int col;
	
		Move(signed int value, int row, int col) {
			this->value = value;
			this->row = row;
			this->col = col;
		}
	
		Move(signed int value) {
			this->value = value;
		}
	};
	
	void printVector(vector<vector<int>>& gameState) {
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				cout << gameState[x][y] << "; ";
			}
			cout << endl;
		}
	}
	
	void printVector(vector<vector<char>>& gameState) {
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				cout << gameState[x][y] << "; ";
			}
			cout << endl;
		}
	}
	
	bool endState(vector<vector<char>>& b) {
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				if (b[x][y] == '_') return false;
			}
		}
		return true;
	} // Tie Check
	
	int evaluate(vector<vector<char>>& b) {
		// Checking for Rows for X or O victory. 
		for (int row = 0; row < 3; row++)
		{
			if (b[row][0] == b[row][1] &&
				b[row][1] == b[row][2])
			{
				if (b[row][0] == computer)
					return +10;
				else if (b[row][0] == opponent)
					return -10;
			}
		}
	
		// Checking for Columns for X or O victory. 
		for (int col = 0; col < 3; col++)
		{
			if (b[0][col] == b[1][col] &&
				b[1][col] == b[2][col])
			{
				if (b[0][col] == computer)
					return +10;
	
				else if (b[0][col] == opponent)
					return -10;
			}
		}
	
		// Checking for Diagonals for X or O victory. 
		if (b[0][0] == b[1][1] && b[1][1] == b[2][2])
		{
			if (b[0][0] == computer)
				return +10;
			else if (b[0][0] == opponent)
				return -10;
		}
	
		if (b[0][2] == b[1][1] && b[1][1] == b[2][0])
		{
			if (b[0][2] == computer)
				return +10;
			else if (b[0][2] == opponent)
				return -10;
		}
	
		// Else if none of them have won then return 0 
		return 0;
	} // Win check
	
	signed int minimax(vector<vector<char>>& gameState, bool isMax, unsigned int depth) {
		minimaxCout++;
		bestDepth = max(depth, bestDepth);
	
		if (endState(gameState) || evaluate(gameState) != 0) {
			return evaluate(gameState);
		}
	
		// find out player's char:
		char playerChar;
		if (isMax)
			playerChar = computer;
		else
			playerChar = opponent;
		signed int bestValue;
		if (isMax)
			bestValue = negative;
		else
			bestValue = positive;
	
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				if (gameState[x][y] == '_') {
					// set board for calling minimax()
					gameState[x][y] = playerChar;
					if (isMax) {
						bestValue = max(bestValue, minimax(gameState, !isMax, depth + 1));
					}
					else {
						bestValue = min(bestValue, minimax(gameState, !isMax, depth + 1));
					}
	
					// unset board
					gameState[x][y] = '_';
				}
			}
		}
	
		// deduce return value;
		if (bestValue < 0) bestValue++;
		else if (bestValue > 0) bestValue--;
		return bestValue;
	
	}
	
	Move bestMove(vector<vector<char>>& gameState) {
		if (endState(gameState) || evaluate(gameState) != 0) {
			return Move(evaluate(gameState));
		}
		Move best(0, 0, 0); // stores best move
	
		vector<vector<int>> values(3, { 0, 0, 0 }); // vector to store values of each individual move
	
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				if (gameState[x][y] == '_') {
					// set board for calling minimax()
					gameState[x][y] = computer;
	
					Move tempValue(minimax(gameState, false, 0), x, y);
	
					if (best.value < tempValue.value) {
						best = tempValue;
					}
	
					// record values
					values[x][y] = tempValue.value;
					// unset board
					gameState[x][y] = '_';
				}
			}
		}
	
		// deduce return value;
		if (best.value < 0) best.value++;
		else if (best.value > 0) best.value--;
		return best;
	}
}


Napi::Value bestMove(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	
	// check number of arguments
	if (info.Length() != 1) {
		Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
		return env.Null();
	}
	
	// check argument type
	if (!info[0].IsArray()) {
		Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
		return env.Null();
	}
	
	// create an array variable from args
	Napi::Array arrayData(env, info[0]);
	
	// check array length
	if(arrayData.Length() != 3) {
		Napi::TypeError::New(env, "Wrong length for array. Correct length should be 3").ThrowAsJavaScriptException();
		return env.Null();
	}
	
	// check argument type inside array
	for (int n = 0; n < 3; n++) {
		// see if there are two dimensions to array
		Napi::Value subArray = arrayData[n];
		// check length of array in second dimension
		Napi::Array subArrayData(env, subArray);
		
		if(subArrayData.Length() != 3) {
			Napi::TypeError::New(env, "Wrong length for array in second dimension. Correct length should be 3").ThrowAsJavaScriptException();
			return env.Null();
		}
		
		// check arguments in subArrayData
		for (int x = 0; x < 3; x++) {
			Napi::Value stringData = subArrayData[x];
			if(stringData.IsString()) {
				if(stringData.ToString().Utf8Value().size() != 1){
					Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
					return env.Null();
				}
			}
		}
	}
	
	
	// unpack 2D array
	std::vector<std::vector<char>> data(3, { '_', '_', '_' }); // build this vector
	
	for(unsigned int x = 0; x < arrayData.Length(); x++) {
        for(unsigned int y = 0; y < Napi::Array(env, arrayData.Get(x)).Length(); y++) {
            // std::cout << Napi::Array(env, arrayData.Get(x)).Get(y).ToString().Utf8Value() << "___" << std::endl;
            data[x][y] = Napi::Array(env, arrayData.Get(x)).Get(y).ToString().Utf8Value()[0];
        }
    }
	
	Game::Move computedData = Game::bestMove(data);
	return Napi::Number::New(env, computedData.col + (computedData.row * 3));
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
	exports.Set(Napi::String::New(env, "bestMove"),Napi::Function::New(env, bestMove));
	return exports;
}

NODE_API_MODULE(tictactoe, Init)