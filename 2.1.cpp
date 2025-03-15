#include <iostream>

using namespace std;

int goal[3][3] = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};
// the space would be set to 0
bool dfsFound = 0;

class State{
public:
    int state[3][3];

    State(int r1c1, int r1c2, int r1c3, int r2c1, int r2c2, int r2c3, int r3c1, int r3c2, int r3c3){
        state[0][0] = r1c1;
        state[0][1] = r1c2;
        state[0][2] = r1c3;
        state[1][0] = r2c1;
        state[1][1] = r2c2;
        state[1][2] = r2c3;
        state[2][0] = r3c1;
        state[2][1] = r3c2;
        state[2][2] = r3c3;
    }

    State swap(State thisState, int row1, int col1, int row2, int col2){
        State nextState = thisState;
        int temp = nextState.state[row1][col1];
        nextState.state[row1][col1] = nextState.state[row2][col2];
        nextState.state[row2][col2] = temp;
        return nextState;
    }

    void printState(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                cout << state[i][j] << " ";
            }
            cout << endl;
        }
    }

    int getZeroRow(State input){
        for(int row = 0; row < 3; row++){
            for(int col = 0; col < 3; col++){
                if(input.state[row][col] == 0){
                    return row;
                }
            }
        }
        cout << "Zero not found" << endl;
        return -1;
    }

    int getZeroCol(State input){
        for(int row = 0; row < 3; row++){
            for(int col = 0; col < 3; col++){
                if(input.state[row][col] == 0){
                    return col;
                }
            }
        }
        cout << "Zero not found" << endl;
        return -1;
    }

    // overload the == operator in order to use find()
    bool operator==(const State &other){
        for(int col = 0; col < 3; col++){
            for(int row = 0; row < 3; row++){
                if(this->state[col][row] != other.state[col][row]){
                    return false;
                }
            }
        }
        return true;
    }

    // return true if reached goal
    bool isGoal(){
        for(int row = 0; row < 3; row++){
            for(int col = 0; col < 3; col++){
                if(state[row][col] != goal[row][col]){
                    return false;
                }
            }
        }
        return true;
    }

    // this function returns a vector that contains every possible next state after moving the 0
    vector<State> moveZero(State thisState){
        vector<State> results;
        // try move 0 up
        if(thisState.getZeroRow(thisState) != 0){
            results.push_back(thisState.swap(thisState, thisState.getZeroRow(thisState), thisState.getZeroCol(thisState), thisState.getZeroRow(thisState) - 1, thisState.getZeroCol(thisState)));
        }
        // try move 0 down
        if(thisState.getZeroRow(thisState) != 2){
            results.push_back(thisState.swap(thisState, thisState.getZeroRow(thisState), thisState.getZeroCol(thisState), thisState.getZeroRow(thisState) + 1, thisState.getZeroCol(thisState)));
        }
        // try move 0 left
        if(thisState.getZeroCol(thisState) != 0){
            results.push_back(thisState.swap(thisState, thisState.getZeroRow(thisState), thisState.getZeroCol(thisState), thisState.getZeroRow(thisState), thisState.getZeroCol(thisState) - 1));
        }
        // try move 0 right
        if(thisState.getZeroCol(thisState) != 2){
            results.push_back(thisState.swap(thisState, thisState.getZeroRow(thisState), thisState.getZeroCol(thisState), thisState.getZeroRow(thisState), thisState.getZeroCol(thisState) + 1));
        }
        return results;
    }

    void bfsSolver (State initialState){
        vector<State> bfsSteps = {initialState};
        vector<int> bfsStepsTraceBack = {-1}; // store the index of the parent state
        vector<State> queue = {initialState};
        int currentStateParent = 0;
        bool goalReached = 0;
        while (queue.size() > 0) {
            // pop the first element in the queue
            State currentState = queue[0];
            queue.erase(queue.begin());
            // check whether it is the goal state
            if (currentState.isGoal()) {
                goalReached = 1;
                cout << "Goal reached" << endl;
                break;
            }
            // add all possible next states to the queue
            vector<State> nextStates = currentState.moveZero(currentState);
            for (int timer = 0; timer < nextStates.size(); timer++) {
                queue.push_back(nextStates[timer]);
                bfsSteps.push_back(nextStates[timer]);
                bfsStepsTraceBack.push_back(currentStateParent);
            }
            // current state is the parent of all next states
            // all states are added to the queue in order
            currentStateParent++;
        }
        if (!goalReached){
            cout << "Goal not reachable." << endl;
        } else {
            // trace back the path
            vector<State> solutionSteps = {};
            // last state in bfsSteps share the same parent with the goal state
            for (int parentIndex = currentStateParent; parentIndex >= 0 ; parentIndex = bfsStepsTraceBack[parentIndex])
                solutionSteps.push_back(bfsSteps[parentIndex]);

            // print the path in reversed order
            for (int timer = solutionSteps.size() - 1; timer >= 0; timer--) {
                solutionSteps[timer].printState();
                cout << endl;
            }
        }
    }

    void dfsSolver(State thisState, vector<State> &dfsPath, vector<State> &visitedStates, bool &dfsFound) {
        visitedStates.push_back(thisState);
        if (dfsFound) return;

        // Check if goal state is reached
        if (thisState.isGoal()) {
            dfsFound = true;
            dfsPath.push_back(thisState);
            return;
        }

        // Generate next possible states
        vector<State> nextStates = thisState.moveZero(thisState);
        for (State nextState : nextStates) {
            if (find(visitedStates.begin(), visitedStates.end(), nextState) == visitedStates.end()) {
                dfsPath.push_back(thisState); // Add to path only when exploring this branch
                dfsSolver(nextState, dfsPath, visitedStates, dfsFound);
                if (dfsFound) return;
                dfsPath.pop_back(); // Backtrack
            }
        }
    }

    // calculate manhattan distance between current state and goal state
    int getManhattanDistance(State thisState) {
        int totalDistance = 0;
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                int value = thisState.state[row][col];
                switch (value) {
                    case 1: // use abs() to get absolute value
                        totalDistance += abs(row - 0) + abs(col - 0);
                        break;
                    case 2:
                        totalDistance += abs(row - 0) + abs(col - 1);
                        break;
                    case 3:
                        totalDistance += abs(row - 0) + abs(col - 2);
                        break;
                    case 8:
                        totalDistance += abs(row - 1) + abs(col - 0);
                        break;
                    case 0:
                        totalDistance += abs(row - 1) + abs(col - 1);
                        break;
                    case 4:
                        totalDistance += abs(row - 1) + abs(col - 2);
                        break;
                    case 7:
                        totalDistance += abs(row - 2) + abs(col - 0);
                        break;
                    case 6:
                        totalDistance += abs(row - 2) + abs(col - 1);
                        break;
                    case 5:
                        totalDistance += abs(row - 2) + abs(col - 2);
                        break;
                    default:
                        // default would never be reached in normal situations
                        cout << "Invalid value" << endl;
                        exit(114);
                }
            }
        }
        return totalDistance;
    }

    State findStateWithMinHeuristic(vector<State> openList) {
        int minHeuristic = 114514;
        State minHeuristicState = openList[0];
        for (int timer = 0; timer < openList.size(); timer++) {
            int currentHeuristic = getManhattanDistance(openList[timer]);
            if (currentHeuristic < minHeuristic) {
                minHeuristic = currentHeuristic;
                minHeuristicState = openList[timer];
            }
        }
        return minHeuristicState;
    }

    void aStarSolver (State initialState){
        // the design of heuristic function: manhattan distance + steps
        vector<State> visitedStates = {initialState};   // aka closed list
        vector<State> solutionSteps = {initialState};
        int goalReached = 0;
        vector<State> openList = {initialState};

        while(1){
            // this state: minimal heuristic
            State thisState = findStateWithMinHeuristic(openList);
            openList.erase(find(openList.begin(), openList.end(), thisState));
            solutionSteps.push_back(thisState);
            // if goal reached
            if (thisState.isGoal()) {
                cout << "Goal reached" << endl;
                goalReached = 1;
                break;
            }
            // add next state to visited states
            visitedStates.push_back(thisState);
            // add all possible next states aka neighbors to open list
            // hint: if a state was added to openList, it must not be in visitedStates
            vector<State> nextStates = thisState.moveZero(thisState);
            for (int timer = 0; timer < nextStates.size(); timer++) {
                if (find(visitedStates.begin(), visitedStates.end(), nextStates[timer]) == visitedStates.end()) {
                    openList.push_back(nextStates[timer]);
                }
            }
        }
        // not like bfs, only minimal heuristic would be recorded in solutionSteps
        // print the path
        for (int timer = 0; timer < solutionSteps.size(); timer++) {
            solutionSteps[timer].printState();
            cout << endl;
        }

    }
};




int main() {
    State initialState = State(2, 8, 3, 1, 6, 4, 7, 0, 5);
    cout << "Solve with DFS" << endl;
    initialState.bfsSolver(initialState);
    cout << "DFS done" << endl;
    vector<State> dfsPath = {};
    vector<State> dfsVisitedStates = {};
    cout << "Solve with DFS" << endl;
    initialState.dfsSolver(initialState, dfsPath, dfsVisitedStates, dfsFound);
    // print dfs result
    for (int timer = 0; timer < dfsPath.size(); timer++) {
        dfsPath[timer].printState();
        cout << endl;
    }
    cout << "DFS done" << endl;
    cout << "Solve with A*" << endl;
    initialState.aStarSolver(initialState);
    cout << "A* done" << endl;

}
