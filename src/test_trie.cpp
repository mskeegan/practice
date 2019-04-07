#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>

#include "trie.h"

const char* swdatadir = "data/star-wars-movie-scripts/";
const char* swdatafiles[3] = {"SW_EpisodeIV.txt","SW_EpisodeV.txt","SW_EpisodeVI.txt"};

std::vector<std::string> readSWDialog(const char* filename){  
    std::ifstream dialog_file(filename);
    std::vector<std::string> dialog;
    std::string line;
    if (dialog_file.is_open()){
        getline(dialog_file,line); // skip first line
        while (getline(dialog_file,line)) {
            std::istringstream ss(line);
            std::string text;
            int i = 0;
            std::vector<std::string> line_fields;
            while (getline(ss,text,'"')){
                if (i++ % 2 == 1) {
                    line_fields.push_back(text);
                }
            }
            dialog.push_back(line_fields.back());
        }
    }
    return dialog;
}

void run_trie_test(){
    char filename[128];
    std::vector<std::string> dialogs;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 128; j++) {
            filename[j] = '\0';
        }
        strncpy(filename,swdatadir,sizeof(filename));
        strncat(filename,swdatafiles[i],(sizeof(filename)-strlen(filename)));
        std::vector<std::string> file_dialogs = readSWDialog(filename);
        std::copy(file_dialogs.begin(),file_dialogs.end(),std::back_inserter(dialogs));
    }

    Trie autocompletions;
    std::cout << "Adding a total of " << dialogs.size() << " dialogs to trie." << std::endl;
    autocompletions.build_trie(dialogs);
    std::vector<std::string> completions = autocompletions.get_completions("H");
    for (auto s : completions ) {
        std::cout << s << std::endl;
    }
}