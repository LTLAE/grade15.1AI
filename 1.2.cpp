#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



class State {
public:
    int leftMissionaries = 0;
    int leftCannibals = 0;
    int rightMissionaries = 0;
    int rightCannibals = 0;
    int boatPosition = 0;   // 0 left 1 right

    State(int people) {
        this->leftMissionaries = people;
        this->leftCannibals = people;
    }

    bool safe(State state) {
        return (state.leftMissionaries >= state.leftCannibals || state.leftMissionaries == 0) &&
               (state.rightMissionaries >= state.rightCannibals || state.rightMissionaries == 0) &&
               leftCannibals >=0 && leftMissionaries >= 0 && rightCannibals >= 0 && rightMissionaries >= 0;
    }

    vector<State> getNextState(State thisState, int boatSize) {
        vector<State> steps = {};   // this vector records all possible next states
        // try boarding the boat
        for (int missionariesOnBoat = 0; missionariesOnBoat <= boatSize; missionariesOnBoat++) {
            for (int cannibalsOnBoat = 0; cannibalsOnBoat <= boatSize - missionariesOnBoat; cannibalsOnBoat++){
                State nextState = thisState;
                // no one boards the boat or boat not safe
                if (missionariesOnBoat + cannibalsOnBoat <= 0 || cannibalsOnBoat > missionariesOnBoat) continue;
                // if boat on left
                if (thisState.boatPosition == 0){
                    nextState.leftMissionaries -= missionariesOnBoat;
                    nextState.leftCannibals -= cannibalsOnBoat;
                    nextState.rightMissionaries += missionariesOnBoat;
                    nextState.rightCannibals += cannibalsOnBoat;
                    nextState.boatPosition = 1;
                } else {
                    // if boat on right
                    nextState.leftMissionaries += missionariesOnBoat;
                    nextState.leftCannibals += cannibalsOnBoat;
                    nextState.rightMissionaries -= missionariesOnBoat;
                    nextState.rightCannibals -= cannibalsOnBoat;
                    nextState.boatPosition = 0;
                }
                // if next state is safe, add it to the vector
                if (nextState.safe(nextState)) {
                    steps.push_back(nextState);
                }
            }
        }
        return steps;
    }

    vector<State> solve(State initialState, int boatSize) {
        vector<State> path = {};    // record path
        vector<int> pathTraceBack = {}; //record where the path from
        int stateCount = 0;
        // use BFS to solve the problem
        vector<State> queue = {initialState};
        vector<State> visitedStates = {initialState};
        while (!queue.empty()) {
            // problem solved: all missionaries and cannibals are at the right bank
            if (queue.front().leftMissionaries == 0 && queue.front().leftCannibals == 0) {
                return path;
            }
            // pick the first state in the queue
            State thisState = queue.front();
            // record this path and remove it from the queue
            path.push_back(thisState);
            queue.erase(queue.begin());
            // get all possible next states and add them to the queue
            vector<State> nextStates = thisState.getNextState(thisState, boatSize);
            // insert all not visited states to the queue
            for (State nextState : nextStates) {
                if (find(visitedStates.begin(), visitedStates.end(), nextState) == visitedStates.end()) {
                    visitedStates.push_back(nextState);
                    queue.push_back(nextState);
                    pathTraceBack.push_back(stateCount);
                }
            }
            stateCount++;
        }
        return {};
    }

    void printResult (vector<State> path) {
        if (path.empty()) {
            cout << "No solution found!" << endl;
            return;
        }
        for (int timer = 0; timer < path.size(); timer++){
            cout << "Step " << timer + 1 << ": ";
            for (int missionariesCount = 0; missionariesCount < path[timer].leftMissionaries; missionariesCount++) cout << "✝️";
            for (int cannibalsCount = 0; cannibalsCount < path[timer].leftCannibals; cannibalsCount++) cout << "👹";
            if (path[timer].boatPosition == 0) cout << "🚤";
            else (cout << " ");
            cout << " /// river /// ";
            if (path[timer].boatPosition == 1) cout << "🚤";
            else (cout << " ");
            for (int missionariesCount = 0; missionariesCount < path[timer].rightMissionaries; missionariesCount++) cout << "✝️";
            for (int cannibalsCount = 0; cannibalsCount < path[timer].rightCannibals; cannibalsCount++) cout << "👹";
            cout << endl;
        }
    }

    // override operator== in order to use find()
    bool operator==(const State& other) const {
        return leftMissionaries == other.leftMissionaries &&
               leftCannibals == other.leftCannibals &&
               rightMissionaries == other.rightMissionaries &&
               rightCannibals == other.rightCannibals &&
               boatPosition == other.boatPosition;
    }
};


int main() {
    int people = 0;  // number of missionaries and cannibals, x means x missionaries and x cannibals
    int boatSize = 0;
    cout << "Enter the number of people: ";
    cin >> people;
    cout << "Enter the boat size: ";
    cin >> boatSize;
    State initialState(people);
    vector<State> path = initialState.solve(initialState, boatSize);
    initialState.printResult(path);
}

// problem 01: only record last step and avoid it
// problem 02: need trace back using vector<int> pathTraceBack = thisState.index
// problem 03: allow infinite loop but set a limit