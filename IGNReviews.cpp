#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Bridges.h"
#include "DataSource.h"
#include "data_src/Game.h"

using namespace std;
using namespace bridges;

template<typename K, typename V>
struct Pair {
    K first; // key pair
    V second; // value pair
};

template<typename K, typename V>
class MapfromScratch {
private:
    vector<Pair<K, vector<V>>> map_data;
public:
    void insert(const K& key, const V& value) {
        for (auto& pair : map_data) {
            if (pair.first == key) {
                pair.second.push_back(value);
                return;
            }
        }
        map_data.push_back({key, {value}});
    }

    vector<V> get(const K& key) const {
        for (const auto& pair : map_data) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return {};
    }

    bool contains(const K& key) const {
        for (const auto& pair : map_data) {
            if (pair.first == key) {
                return true;
            }
        }
        return false;
    }

    const vector<Pair<K, vector<V>>>& getAll() const {
        return map_data;
    }
};

class MaxHeap {
private:
    vector<pair<string, double>> heap;

    int getParent(int index) { return (index - 1) / 2; }
    int getLeftChild(int index) { return 2 * index + 1; }
    int getRightChild(int index) { return 2 * index + 2; }

    void heapifyUp(int index) {
        if (index && heap[getParent(index)].second < heap[index].second) {
            swap(heap[index], heap[getParent(index)]);
            heapifyUp(getParent(index));
        }
    }

    void heapifyDown(int index) {
        int left = getLeftChild(index);
        int right = getRightChild(index);
        int largest = index;

        if (left < heap.size() && heap[left].second > heap[largest].second) {
            largest = left;
        }

        if (right < heap.size() && heap[right].second > heap[largest].second) {
            largest = right;
        }

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    void insert(const pair<string, double>& value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    pair<string, double> extractMax() {
        if (heap.empty()) {
            throw out_of_range("Heap is empty");
        }
        pair<string, double> maxValue = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return maxValue;
    }

    bool empty() const {
        return heap.empty();
    }
};

void searchGamesByGenre(const MapfromScratch<string, string>& genre_map) {
    string genre;
    cout << "Enter the genre to search for: ";
    cin.ignore();
    getline(cin, genre);

    vector<string> games = genre_map.get(genre);
    if (!games.empty()) {
        cout << "Games with genre '" << genre << "':" << endl;
        for (const auto& title : games) {
            cout << title << endl;
        }
    } else {
        cout << "No games found for this genre." << endl;
    }
}

void searchGamesByPlatform(const MapfromScratch<string, string>& platform_map) {
    string platform;
    cout << "Enter the platform to search for: ";
    cin.ignore();
    getline(cin, platform);

    vector<string> games = platform_map.get(platform);
    if (!games.empty()) {
        cout << "Games for platform '" << platform << "':" << endl;
        for (const auto& title : games) {
            cout << title << endl;
        }
    } else {
        cout << "No games found for this platform." << endl;
    }
}

void searchGame(const vector<Game>& game_list) {
    string title;
    cout << "Enter the title of the game to search: ";
    cin.ignore();
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

void listAvailablePlatforms(const MapfromScratch<string, string>& platform_map) {
    cout << "Available Platforms:" << endl;
    vector<string> platforms;

    for (const auto& entry : platform_map.getAll()) {
        if (find(platforms.begin(), platforms.end(), entry.first) == platforms.end()) {
            platforms.push_back(entry.first);
            cout << entry.first << endl;
        }
    }
}

void displayTopGames(const vector<Game>& game_list, const string& platform, const MapfromScratch<string, string>& platform_map) {
    if (!platform_map.contains(platform)) {
        cout << "There is no platform named '" << platform << "'" << endl;
        return;
    }

    MapfromScratch<string, double> title_to_rating;

    // Build the map of game titles to their highest ratings on the specified platform
    for (const auto& game : game_list) {
        if (game.getPlatformType() == platform) {
            const string& title = game.getTitle();
            double rating = game.getRating();

            vector<double> ratings = title_to_rating.get(title);
            if (!ratings.empty()) {
                double existing_rating = ratings.front(); // Assuming the first rating is the highest
                if (existing_rating < rating) {
                    title_to_rating.insert(title, rating);
                }
            } else {
                title_to_rating.insert(title, rating);
            }
        }
    }

    MaxHeap max_heap;

    // Insert all ratings for each title into the max-heap
    for (const auto& entry : title_to_rating.getAll()) {
        for (const auto& rating : entry.second) {
            max_heap.insert({entry.first, rating});
        }
    }

    // Extract top 10 games in order from the heap
    vector<pair<string, double>> top_games;
    int count = 0;
    while (!max_heap.empty() && count < 10) {
        const auto& top_game = max_heap.extractMax();
        top_games.push_back(top_game);
        ++count;
    }

    // Display the top 10 games
    cout << "Top 10 Rated Games for platform '" << platform << "':" << endl;
    for (size_t i = 0; i < top_games.size(); ++i) {
        cout << i + 1 << ". " << top_games[i].first << " - Rating: " << top_games[i].second << endl;
    }
}

int main(int argc, char **argv) {
    Bridges bridges(0, "largebug239", "798763852353");
    bridges.setTitle("How to access the IGN Game Data");

    DataSource ds(&bridges);
    vector<Game> game_list = ds.getGameData();

    MapfromScratch<string, string> genre_map;
    MapfromScratch<string, string> platform_map;

    for (const auto& game : game_list) {
        for (const auto& genre : game.getGameGenre()) {
            genre_map.insert(genre, game.getTitle());
        }
        platform_map.insert(game.getPlatformType(), game.getTitle());
    }

    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Search for a game and display its information" << endl;
        cout << "2. Search for games by genre" << endl;
        cout << "3. Search for games by platform" << endl;
        cout << "4. List all available platforms" << endl;
        cout << "5. Display top 10 games by platform" << endl;
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
                listAvailablePlatforms(platform_map);
                break;
            case 5: {
                string platform;
                cout << "Enter the platform to display top games for: ";
                cin.ignore(); // to ignore any leftover newline character
                getline(cin, platform);
                displayTopGames(game_list, platform, platform_map);
                break;
            }
            case 6:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
