#include <iostream>
#include <string>
#include <set>
#include <map>

/**
 * DFA Automata for the regular expression (a + bc)*
 * q0(accepting), q1(rejecting), q2(rejecting)
 * q0/a -> q0
 * q0/b -> q1
 * q0/c -> q2
 * q1/a,b -> q2
 * q1/c -> q0
 * q2/a,b,c -> q2
*/
class Dfa {
    /**
     * Alphabet for input
    */
    std::set<char> alphabet { 'a', 'b', 'c' };

    /**
     * State structure
    */
    struct State
    {
        /**
         * State name - string
        */
        std::string name;

        /**
         * Is accepting state
        */
        bool isAccepting;

        /**
         * State constructor
        */
        State(const std::string& _name, bool _isAccepting) {
            isAccepting = _isAccepting;
            name = _name;
        }
    };

    /**
     * Automata states
    */
    State *q0, *q1, *q2;
    
    /**
     * Automata lambda function
    */
    std::map<std::pair<State*, char>, State*> lambda;


    /**
     * Current state
    */
    State *current;

public:
    /**
     * Dfa constructor - initialize states and lambda function
    */
    Dfa() {
        q0 = new State("q0", true);
        q1 = new State("q1", false);
        q2 = new State("q2", false);
        lambda[{ q0, 'a' }] = q0;
        lambda[{ q0, 'b' }] = q1;
        lambda[{ q0, 'c' }] = q2;
        lambda[{ q1, 'a' }] = q2;
        lambda[{ q1, 'b' }] = q2;
        lambda[{ q1, 'c' }] = q0;
        lambda[{ q2, 'a' }] = q2;
        lambda[{ q2, 'b' }] = q2;
        lambda[{ q2, 'c' }] = q2;
    }

    /**
     * Dfa destructor free states memory allocation
    */
    ~Dfa(){
        delete q0;
        delete q1;
        delete q2;
    }

    /**
     * Read input function
    */
    bool read(const std::string& input, bool log = false){
        current = q0;
        for(const char c: input) {
            if(alphabet.find(c) == alphabet.end()) {
                // Log not in alphabet error on logging mode
                if(log) {
                    std::cout << "Character " << c << " is not in alphabet, exiting..." << std::endl;
                }
                return false;
            }
            State* next = lambda[{ current, c }];

            // Log states, characters and movement on logging mode
            if(log) {
                std::cout << "In state: " << current->name << std::endl
                    << "Reading character: " << c << std::endl
                    << "Moving to state: " << next->name << std::endl << std::endl;
            }
            current = next;
        }

        // Log final status on loggin mode
        if(log) {
            std::string finalStatus = current->isAccepting ? "accepted" : "rejected";
            std::cout << "String " << input << " is " <<  finalStatus << " by the automata" << std::endl;
        }
        return current->isAccepting; 
    }
};

int main(int argc, char* argv[]) {
    bool log = argc > 1 && argv[1] == std::string("--log");
    std::string input;
    std::cin >> input;
    std::cout << std::boolalpha << Dfa().read(input, log);
    return 0;
}