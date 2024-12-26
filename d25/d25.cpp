#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <queue>

std::vector<std::vector<std::vector<char>>> keys, locks;
int n_key=0, n_lock=0;

void combination_parser(std::vector<std::vector<int>> *combinations, std::vector<std::vector<std::vector<char>>> var){
    for(const auto& map : var) {
        std::vector<int> comb;
        for(int column = 0; column < map[0].size(); column++) { 
            int counter = 0;
            for(int row = 1; row < map.size()-1; row++) { 
                if(map[row][column] == '#') { 
                    counter++;
                }
            }
            comb.push_back(counter);
        }
        combinations->push_back(comb);
    }
}

//Debugging
void print(std::vector<std::vector<std::vector<char>>> var){
    for(const auto& map : var) {
        for(const auto& row : map) {
            for(const auto& ch : row) {
                std::cout << ch;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "Number keys: " << n_key << " , number locks: " << n_lock<< std::endl;
}

void print_comb(std::vector<std::vector<int>> combinations){
    for(const auto& comb : combinations) {
        for(const auto& val : comb) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }}

int main(int argc, char const *argv[])
{
    std::string line;
    std::ifstream file;    

    // Input reading
    file.open("input");
    while (getline(file, line)) {
        bool key=false;
        std::vector<std::vector<char>> map(7, std::vector<char>(line.size()));
        for (int i = 0; i < 7; ++i) {
            if (i > 0) getline(file, line);
            for (size_t j = 0; j < line.size(); ++j) {
                map[i][j] = line[j];
                if(i==0 && line[0]=='.'){key=true;}
            }
        }
        if(key){keys.push_back(map); n_key++;}
        else{locks.push_back(map); n_lock++;}
        getline(file, line);
    }
    file.close();

    print(locks);
    print(keys);

    std::vector<std::vector<int>> k_combinations;
    std::vector<std::vector<int>> l_combinations;
    combination_parser(&k_combinations, keys);
    combination_parser(&l_combinations, locks);
    //print_comb(l_combinations);
    //print_comb(k_combinations);

    int total=0;
    for(const auto& comb : k_combinations) {
        for(const auto& pass : l_combinations){
            bool valid = true;
            for(int i=0; i<comb.size();i++){
                if(comb[i] + pass[i] > 5){valid = false;break;}
            }
            if(valid){total++;}
        }
    }
    std::cout<<total;

    return 0;
}