#include "ladder.h"

void error(string word1, string word2, string msg){
    cout << word1 << ", " << word2 << ": " << msg << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int m = str1.length();
    int n = str2.length();

    vector<vector<int>> distance(m+1, vector<int>(n+1));

    for(int i = 0; i <= m; ++i)
        distance[i][0] = i;

    for(int j = 0; j <= n; ++j)
        distance[0][j] = j;

    for(int j = 1; j <= n; ++j){
        for(int i = 1; i <= m; ++i){
            int cost = (str1[i-1] == str2[j-1]) ? 0 : 1;
            distance[i][j] = min({distance[i-1][j] + 1, distance[i][j-1] +1, distance[i-1][j-1] +cost});
        }
    }
    return distance[m][n] <= d;
}
bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while(!ladder_queue.empty()){
        auto ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for(string word : word_list){
            if(is_adjacent(last_word, word)){
                if(visited.find(word) == visited.end()){
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if(word == end_word){
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    vector<string> empty;
    return empty;
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    cout << file_name << endl;
    if (!file) {  // Check if the file was successfully opened
        std::cerr << "Error opening the file." << std::endl;
    }
    string word;
    while(file >> word){
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder){
    if(ladder.empty()){
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for(const string& s : ladder)
        cout << s << " ";
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "/home/justt13/ICS46/ics-46-hw-9-NisuJT/src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}