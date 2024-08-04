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
    cout << "Top 10 Games:" << endl;
    for (int i = 0; i < 10 && i < game_list.size(); ++i) {
        cout << i + 1 << ". " << game_list[i].getTitle() << " - Rating: " << game_list[i].getRating() << endl;
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

    int choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Search for a game and display its information" << endl;
        cout << "2. Display the top 10 games in ranking" << endl;
        cout << "3. Visualize the data of the top 10 games" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                searchGame(game_list);
                break;
            case 2:
                displayTopGames(game_list);
                break;
            case 3:
                visualizeTopGames(bridges, game_list);
                break;
            case 4:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}