#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;

class Moves{
public:
    int dish;
    char from;
    char to;
};

vector<Moves> moves;
ofstream file("../time_and_moves.csv");

void hanoi(int dishCount, char from, char to, char aux) {
    Moves thisMove; // record each move, thisMove would be pushed back to array moves

    // if dish = 1
    if (dishCount == 1) {
        // cout << "Move dish" << dishCount << "from" << from << " to " << to << endl;
        thisMove.from = from;
        thisMove.to = to;
        thisMove.dish = dishCount;
        moves.push_back(thisMove);
        return;
    }
    // recursive call
    hanoi(dishCount - 1, from, aux, to);
    // cout << "Move dish" << dishCount << "from" << from << " to " << to << endl;
    thisMove.from = from;
    thisMove.to = to;
    thisMove.dish = dishCount;
    moves.push_back(thisMove);

    hanoi(dishCount - 1, aux, to, from);

}

void runHanoi(int dishCount){
    moves.clear(); // clear moves array
    // record time using chrono by chatGPT
    cout << "Dish count: " << dishCount << endl;
    auto start = chrono::high_resolution_clock::now(); // start time
    hanoi(dishCount, 'A', 'C', 'B');
    auto end = chrono::high_resolution_clock::now(); // end time
    cout << "Total moves: " << moves.size() << endl;
    chrono::duration<double> duration = end - start; // calculate duration
    cout << "Time taken: " << duration.count() << " seconds" << endl;
    // save time and moves to file
    file << dishCount << "," << duration.count() << "," << moves.size() << endl;
    // print moves
    for (int timer = 0; timer < moves.size(); timer++){
        cout << "Move dish " << moves[timer].dish << " from " << moves[timer].from << " to " << moves[timer].to << endl;
    }
}


int main() {
    // int dishCount = 0;
    // cout << "Enter the number of dishes: ";
    // cin >> dishCount;
    file << "dish_count,time,moves" << endl;
    for (int dishCount = 2; dishCount <= 7; dishCount++)
        runHanoi(dishCount);
    file.close();
}
