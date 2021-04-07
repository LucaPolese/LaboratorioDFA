#include <iostream>
#include "automata.h"

using namespace std;

/**
 * Constructor for Abstract DFA.
 * 
 * @param noStates
 *            Number of states in the DFA.
 */
AbstractDFA::AbstractDFA(int noStates) : numStates(noStates), actState(initialState){}

/**
 * Reset the automaton to the initial state.
 */
void AbstractDFA::reset() { actState = initialState; }

/**
 * Performs one step of the DFA for a given letter. If there is a transition
 * for the given letter, then the automaton proceeds to the successor state.
 * Otherwise it goes to the sink state. By construction it will stay in the
 * sink for every input letter.
 * 
 * @param letter
 *            The current input.
 */
void AbstractDFA::doStep(char letter) {
    //A check is made to verify that the current state does not correspond to the trap state, otherwise there is no point in proceeding
    if(actState != trapState){
        //The iterator corresponding to the transition function is created with input (current status, letter)
        map<tpair, int>::iterator ftran = transitionF.find(tpair(actState,letter));
        //This is done to verify that the iterator is in a state that allows it to consume the input symbol.
        if(ftran != transitionF.end()){
            //The automata shifts to the state determined by the transition function
            actState = ftran->second;
        }else{
            //The automata is in a state where it isn't possible to proceed, as there are no further transition functions.
            actState = trapState;
        }
    }
}

/**
 * Check if the automaton is currently accepting.
 * 
 * @return True, if the automaton is currently in the accepting state.
 */
bool AbstractDFA::isAccepting() {
   return actState;
}

/**
 * Run the DFA on the input.
 * 
 * @param inputWord
 *            stream that contains the input word
 * @return True, if if the word is accepted by this automaton
 */
bool AbstractDFA::run(const string &inputWord) {
    this->reset();
    for(int i = 0; i < inputWord.length(); i++) {
        doStep(inputWord[i]);
    }
    return isAccepting();
}


/**
 * Construct a new DFA that recognizes exactly the given word. Given a word
 * "foo" the constructed automaton looks like: -> () -f-> () -o-> () -o-> []
 * from every state (including the final one) every other input letter leads
 * to a distinguished sink state in which the automaton then remains
 * 
 * @param word
 *            A String that the automaton should recognize
 */
WordDFA::WordDFA(const string &word) : AbstractDFA(word.length()+1) {
    /*The idea behind this DFA is that each letter of the word must represent a distinct state of the automaton
     *The class WordDFA inherits the sub-object from AbstractDFA, so it is necessary to make a construction of it
     *based on the length of the chosen word + 1.
     *The choice of the +1 is due to the fact that initial state has to be included.
     *Every state which is not a trapState has to consume a symbol, so each symbol between the position 0 and actState-1
     *of the word array has been consumed and that the finalState is reached if and only if the word
     *from 0 to word.length()-1 has been consumed.
     *This means that the finalState is reached when actState == word.length()*/
    for(int i = 0; i < word.length();i++){
        //The ith pair has been created
        pair<int,char> newState(i,word[i]);
        //The new transition function has been added to the transition function map
        transitionF.insert(pair<tpair,int>(newState,i+1));
    }
    //The last state is considered as the final one, so it's added to the finalState vector
    finalStates.insert(finalStates.end(),word.length());
}

/**
 * Construct a new DFA that recognizes comments within source code. There
 * are three kinds of comments: single line comment that starts with // and ends
 * with a newline, multiline comments that starts with (* and ends with *), and
 * multiline comments that starts with { and ends with }
 */
CommentDFA::CommentDFA() : AbstractDFA(0) {
    // TODO: fill in correct number of states
    // TODO: build DFA recognizing comments
}

/**
 * Performs one step of the DFA for a given letter. This method works
 * differently than in the superclass AbstractDFA.
 * 
 * @param letter
 *            The current input.
 */
void CommentDFA::doStep(char letter) {
    // TODO: implement accordingly
}	


