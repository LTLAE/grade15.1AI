#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Modus Ponens
    cout << "Modus Ponens" << endl;
    vector <pair<string, string>> rules1 = {{"P", "Q"}, {"Q", "R"}};
    string input1 = "P";
    string process1 = input1;
    // search rules table to find the output of input1
    while (1) {
        // when process can't be found in rules table.first, then it is the output
        if (find_if(rules1.begin(), rules1.end(), [&process1](const pair<string, string>& rule) { return rule.first == process1; }) == rules1.end()) {
            cout << "The output of " << input1 << " is " << process1 << endl;
            break;
        }
        for (pair<string, string> rule: rules1) {
            if (rule.first == process1) {
                process1 = rule.second;
                break;
            }
        }
    }

    // Conjunction Introduction
    cout << "Conjunction Introduction" << endl;
    vector <string> input2 = {"P", "Q", "nR"};
    string output2 = input2[0] + " ^ " + input2[1] + " ^ " + input2[2];
    // do and op
    cout << "The output of " << input2[0] << " ^ " << input2[1] << " ^ " << input2[2] << " is " << output2 << endl;

    // Tautology
    cout << "Tautology" << endl;
    vector <pair<string, pair<string, string>>> rule3 = {{"The object", {"is", "potato"}},
                                                         {"The object", {"is not", "potato"}}};
    string input3 = "The object";
    bool positive3 = false;
    bool negative3 = false;
    // do or op
    for (pair<string, pair<string, string>> rule: rule3) {
        if (rule.first == input3) {
            cout << "The object " << rule.second.first << " " << rule.second.second << "or ";
            // calculate rules
            if (rule.second.first == "is") {
                positive3 = true;
            } else if (rule.second.first == "is not") {
                negative3 = true;
            }
        }
    }
    cout << "\b\b" << endl;
    if (positive3 && negative3) {
        cout << "Condition always true." << endl;
    } else {
        cout << "The object is not a tautology" << endl;
    }

    // Contradiction
    cout << "Contradiction" << endl;
    vector <pair<string, pair<string, string>>> rule4 = {{"The object", {"is", "potato"}},
                                                         {"The object", {"is not", "potato"}}};
    string input4 = "The object";
    bool positive4 = false;
    bool negative4 = false;
    // do and op
    for (pair<string, pair<string, string>> rule: rule4) {
        if (rule.first == input4) {
            cout << "The object " << rule.second.first << " " << rule.second.second << "and ";
            // calculate rules
            if (rule.second.first == "is") {
                positive4 = true;
            } else if (rule.second.first == "is not") {
                negative4 = true;
            }
        }
    }
    cout << "\b\b" << endl;
    if (positive4 && negative4) {
        cout << "Condition always false." << endl;
    } else {
        cout << "The object is not a contradiction" << endl;
    }

    //Syllogism
    cout << "Syllogism" << endl;
    vector <pair<string, string>> rules5 = {{"P", "Q"}, {"Q", "R"}};
    string input5 = "P";
    string process5 = input1;
    // search rules table to find the output of input1
    while (1) {
        // when process can't be found in rules table.first, then it is the output
        if (find_if(rules5.begin(), rules5.end(), [&process5](const pair<string, string>& rule) { return rule.first == process5; }) == rules5.end()) {
            cout << "The output of " << input1 << " is " << process5 << endl;
            break;
        }
        for (pair<string, string> rule: rules1) {
            if (rule.first == process5) {
                process5 = rule.second;
                break;
            }
        }
    }




}
