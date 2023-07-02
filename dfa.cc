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
    bool read(const std::string& input){
        current = q0;
        for(const char c: input) {
            if(alphabet.find(c) == alphabet.end())
                return false;
            current = lambda[{ current, c }];
        }
        return current->isAccepting;
    }
};

int main() {
    std::string input;
    std::cin >> input;
    std::cout << std::boolalpha << Dfa().read(input);
    return 0;
}