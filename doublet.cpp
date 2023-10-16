#include "MinHeap.h"
#include <iostream> 
#include <fstream>
#include <string>
#include <map> 
#include <set>
#include <utility>

using namespace std;

struct Node{
    Node(string word, Node* next){
        this->word = word;
        this->next = next;
    }
    Node(){
        word = "";
        next = nullptr;
    }
    bool operator<(const Node& rhs){
        return word < rhs.word;
    }
    string word;
    Node* next;
};

struct LinkedList{
    Node* head;
    //Node* tail;
};

//Function prototypes
void getWords(istream& infile, int size, set<string>& wordList, string start, string end);
int getHeuristic(string word1, string word2);
void graphSearch(Node** graph, set<string>& dictionary, string start, string end, unsigned int numWords);

int main(int argc, char* argv[]){
    ifstream file(argv[3]);
    string startWord = argv[1];
    string endWord = argv[2];

    //Case-insensitive, so make everything uppercase to standardize
    for (unsigned int i = 0; i < startWord.size(); i++) startWord[i] = toupper(startWord[i]);
    for (unsigned int i = 0; i < endWord.size(); i++) endWord[i] = toupper(endWord[i]);

    //set<string> wordBank = getWords(file, startWord.size());    
    int numWords;
    file >> numWords;
    set<string> wb;
    getWords(file, numWords, wb, startWord, endWord);

    return 0;
}

void getWords(istream& infile, int size, set<string>& wordList, string start, string end){
    //int numWords;
    //infile >> numWords;
    Node* graph[size];

    //set<string> wordList;
    for (int i = 0; i < size; i++){
        string currWord; 
        infile >> currWord;
        //if (currWord.size() != size) continue;  //Words that have different length than start/end work are inapplicable

        //Make everything upper-case so that < operator will work appropriately
        for (unsigned int j = 0; j < currWord.size(); j++){
            currWord[j] = toupper(currWord[j]);
        }   
        wordList.insert(currWord);
        Node* curr = new Node(currWord, nullptr);
        //LinkedList* list = new LinkedList;
        //list->head = curr;
        //list->tail = curr;
        //list->head->next = list->tail;
        graph[i] = curr;
    }
    //return wordList;
    for (int i = 0; i < size; i++){
        Node* curr = graph[i];    
        string currWord = curr->word;
        for (unsigned int j = 0; j < currWord.size(); j++){
            for (int k = 65; k <= 90; k++){
                string neighbor = currWord;
                neighbor[j] = static_cast<char>(k);
                if (neighbor != currWord && wordList.find(neighbor) != wordList.end()){
                    Node* newNode = new Node(neighbor, nullptr);
                    curr->next = newNode;
                    curr = newNode;
                }
            }
        }
        //graph[i]->tail = curr;
    }
    //buildGraph(wordList, graph, size);
    graphSearch(graph, wordList, start, end, size);
}

int getHeuristic(string word1, string word2){
    int h = 0;
    for (unsigned int i = 0; i < word1.size(); i++){
        if (word1[i] != word2[i]) h++;  //Counts number of letters which do not match letter in same position in endWord
    }
    return h;
}

void graphSearch(Node** graph, set<string>& dictionary, string start, string end, unsigned int numWords){
    MinHeap<Node> heap(2);
    set<string> removed;
    map<string, int> g; //Stores the number of moves since the start state
    map<string, int> p; //Stores the priority of a node in the heap

    int startIdx;
    for (unsigned int i = 0; i < numWords; i++){
        if (graph[i]->word == start){
            startIdx = i;
            break;
        }
    }
    
    p[start] = getHeuristic(start, end) * (start.size() + 1) + getHeuristic(start, end);
    heap.add(*graph[startIdx], p[start]);
    g[start] = 0;
    int expansions = 0;

     while (!heap.isEmpty()){
        string curr = heap.peek().word;
       
        if (curr == end){
            cout << g[curr] << endl << expansions << endl;
            return;
        }

        /*Since priorities are updated by re-adding the node, it is necessary
        to check the node removed from the heap has not already been removed*/
        while (removed.find(curr) != removed.end() && !heap.isEmpty()){
            heap.remove();
            if (!heap.isEmpty()) curr = heap.peek().word;
        }
        if (heap.isEmpty()){
            cout << "No transformation" << endl << expansions << endl;
            return;
        } 
        Node* n = heap.peek().next;
        //cout << heap.peek()->word << endl;
        heap.remove();
        removed.insert(curr);
        expansions++;

        //Iterate through all words within one letter of the current word
        
        while (n != nullptr) {
            
            int priority = (start.size() + 1) * (g[curr] + 1 + getHeuristic(n->word, end)) + getHeuristic(n->word, end);
            //Make sure word is undiscovered, or a shorter path to the word has been discovered
            if (g.find(n->word) == g.end() || p[n->word] > priority){
                heap.add(*n, priority);
                g[n->word] = g[curr] + 1; 
                p[n->word] = priority;
            }
            n = n->next;
        }
    }
    cout << "No transformation" << endl << expansions << endl;

}

