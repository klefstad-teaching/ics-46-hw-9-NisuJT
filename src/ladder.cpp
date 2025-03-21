#include "ladder.h"

void error(string word1, string word2, string msg){
    cout << word1 << ", " << word2 << ": " << msg << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int m = str1.size();
    int n = str2.size();

    int i = 0, j = 0, cost = 0;
    while(cost <= d){
        if(i >= m){
            cost += n-j;
            break;
        }
        else if(j >= n){
            cost += m-i;
            break;
        }
        if(str1[i] != str2[j]){
            if(m < n){
                --i;
            }
            else if(m > n){
                --j;
            }
            ++cost;
        }
        ++i;
        ++j;
    }

    return cost <= d;
    // if(abs(m-n) > d) return false;

    // std::vector<int> prev(n + 1), curr(n + 1);

    // for (int j = 0; j <= n; ++j) {
    //     prev[j] = j;
    // }
    // for (int i = 1; i <= m; ++i) {
    //     curr[0] = i;

    //     for (int j = 1; j <= n; ++j) {
    //         if (str1[i - 1] == str2[j - 1]) {
    //             curr[j] = prev[j - 1]; 
    //         } else {
    //             curr[j] = min({prev[j - 1], curr[j - 1], prev[j]}) + 1;
    //         }
    //     }
    //     if(*min_element(curr.begin(), curr.end()) > d) return false;
    //     swap(prev, curr);
    // }
    // return prev[n] <= d;
}
bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

string lowerCase(const string & input) {
    string result = input;
    for(char& c : result)
        c = tolower(c);
    return result;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    string begin = lowerCase(begin_word);
    string end = lowerCase(end_word);

    if(begin == end || word_list.find(end) == word_list.end()) return {};

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin});
    set<string> visited;
    visited.insert(begin);
    
    while(!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for(string word : word_list){
            if(is_adjacent(last_word, word)){
                if(visited.find(word) == visited.end()){
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if(word == end){
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
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