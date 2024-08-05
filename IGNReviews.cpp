#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Bridges.h"
#include "DataSource.h"
#include "data_src/Game.h"
#include "BSTElement.h"

using namespace std;
using namespace bridges;


// class MapfromScratch {
// private:
//     vector<pair<string, vector<string>>> map_data;
// public:
//     void insert(const string& key, const vector<string>& value) {
//         for (auto& pair : map_data) {
//             if (pair.first == key) {
//                 pair.second = value;
//                 return;
//             }
//         }
//         map_data.push_back({key, value});
//     }

//     vector<string> get(const string& key) {
//         for (const auto& pair : map_data) {
//             if (pair.first == key) {
//                 return pair.second;
//             }
//         }
//         return {};
//     }

//     bool contains(const string& key) {
//         for (const auto& pair : map_data) {
//             if (pair.first == key) {
//                 return true;
//             }
//         }
//         return false;
//     }
// };



// BST function to insert game titles and ratings
BSTElement<string, string>* insertIntoBST(string title, string rating, BSTElement<string, string> *root) {
    if (root == nullptr) {
        root = new BSTElement<string, string>(title);
        root->setLabel(rating);
        return root;
    }
    if (title > root->getKey()) {
        root->setRight(insertIntoBST(title, rating, root->getRight()));
    } else {
        root->setLeft(insertIntoBST(title, rating, root->getLeft()));
    }
    return root;
}

//void searchGamesByGenre(MapfromScratch& genre_map) {
void searchGamesByGenre(const unordered_map<string, vector<string>>& genre_map) {
    string genre;
    cout << "Enter the genre to search for: ";
    cin.ignore(); // to ignore any leftover newline character
    getline(cin, genre);

    auto it = genre_map.find(genre);
    if (it != genre_map.end()) {
        cout << "Games with genre '" << genre << "':" << endl;
        for (const auto& title : it->second) {
            cout << title << endl;
        }
    } else {
        cout << "No games found for this genre." << endl;
    }
}


// void searchGamesByPlatform(MapfromScratch& platform_map) {
void searchGamesByPlatform(const unordered_map<string, vector<string>>& platform_map) {
    string platform;
    cout << "Enter the platform to search for: ";
    cin.ignore(); // to ignore any leftover newline character
    getline(cin, platform);

    auto it = platform_map.find(platform);
    if (it != platform_map.end()) {
        cout << "Games for platform '" << platform << "':" << endl;
        for (const auto& title : it->second) {
            cout << title << endl;
        }
    } else {
        cout << "No games found for this platform." << endl;
    }
}


void searchGame(const vector<Game>& game_list) {
    string title;
    cout << "Enter the title of the game to search: ";
    cin.ignore(); // to ignore any leftover newline character
    getline(cin, title);

    for (const auto& game : game_list) {
        if (game.getTitle() == title) {
            cout << "Game found:" << endl;
            cout << "\tTitle: " << game.getTitle() << endl
                 << "\tPlatform Type: " << game.getPlatformType() << endl
                 << "\tRating: " << game.getRating() << endl
                 << "\tGenres: ";
            for (const auto& genre : game.getGameGenre())
                cout << genre << ", ";
            cout << endl;
            return;
        }
    }
    cout << "Game not found." << endl;
}

void displayTopGames(const vector<Game>& game_list) {
    // Map to store the highest rating for each unique game title
    map<string, double> title_to_rating;

    // Populate the map with the highest rating for each game title
    for (const auto& game : game_list) {
        const string& title = game.getTitle();
        double rating = game.getRating();

        // Update the map if the current rating is higher than the stored one
        if (title_to_rating.find(title) == title_to_rating.end() || title_to_rating[title] < rating) {
            title_to_rating[title] = rating;
        }
    }

    // Define a max-heap (priority queue) for unique games
    auto comp = [](const pair<string, double>& a, const pair<string, double>& b) { return a.second < b.second; };
    priority_queue<pair<string, double>, vector<pair<string, double>>, decltype(comp)> max_heap(comp);

    // Push all unique game titles with their ratings into the heap
    for (const auto& entry : title_to_rating) {
        max_heap.push(entry);
    }

    // Display the top 10 unique games
    cout << "Top 10 Rated Games:" << endl;
    int count = 0;
    while (!max_heap.empty() && count < 10) {
        const auto& top_game = max_heap.top();
        cout << count + 1 << ". " << top_game.first << " - Rating: " << top_game.second << endl;
        max_heap.pop();
        ++count;
    }
}


void visualizeTopGames(Bridges& bridges, const vector<Game>& game_list) {
    BSTElement<string, string>* root = nullptr;
    for (int i = 0; i < 10 && i < game_list.size(); ++i) {
        string title = game_list[i].getTitle();
        string rating = to_string(game_list[i].getRating());
        root = insertIntoBST(title, rating, root);
    }

    bridges.setDataStructure(root);

    queue<BSTElement<string, string> *> q;
    q.push(root);
    int level = 0;

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            BSTElement<string, string> *node = q.front();
            q.pop();

            if (node->getLeft() != nullptr) {
                q.push(node->getLeft());
            }
            if (node->getRight() != nullptr) {
                q.push(node->getRight());
            }

            if (level % 2 == 0) {
                node->setColor("yellow");
            } else {
                node->setColor("purple");
            }
        }
        level++;
    }

    bridges.visualize();
}

int main(int argc, char **argv) {
    Bridges bridges(0, "largebug239", "798763852353");
    bridges.setTitle("How to access the IGN Game Data");

    DataSource ds(&bridges);
    vector<Game> game_list = ds.getGameData();

    // Create unordered maps for quick lookups

    // MapfromScratch genre_map;
    // MapfromScratch platform_map;
    unordered_map<string, vector<string>> genre_map;
    unordered_map<string, vector<string>> platform_map;

    for (const auto& game : game_list) {
        for (const auto& genre : game.getGameGenre()) {
            genre_map[genre].push_back(game.getTitle());
        }
        platform_map[game.getPlatformType()].push_back(game.getTitle());
    }

    int choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Search for a game and display its information" << endl;
        cout << "2. Search for games by genre" << endl;
        cout << "3. Search for games by platform" << endl;
        cout << "4. Display the top 10 games in ranking" << endl;
        cout << "5. Visualize the data of the top 10 games" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                searchGame(game_list);
            break;
            case 2:
                searchGamesByGenre(genre_map);
            break;
            case 3:
                searchGamesByPlatform(platform_map);
            break;
            case 4:
                displayTopGames(game_list);
            break;
            case 5:
                visualizeTopGames(bridges, game_list);
            break;
            case 6:
                cout << "Exiting the program." << endl;
            break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}

