echo "Compiling source code..."
echo
g++ -std=c++17 dfa.cc -o dfa
echo "Testing strings against regular expression (a + bc)*"
echo
for i in {1..5}; do
    test="test/test${i}.txt"
    echo "Input test: $(cat $test)"
    echo "Result: $(./dfa < $test)"
    echo
done
