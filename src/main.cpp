#include <iostream>
#include "Manager.h"

int main() {
    Manager manager = Manager();

    cout << "Welcome to the Water Network Manager" << endl << "What would you like to do?" << endl;

    while (true) {
        //TODO
        cout << endl
             << "[1] T2.1" << endl
             << "[2] T2.2" << endl
             << "[3] T2.3" << endl
        //DONE
             << "[4] Test Reservoir removals from the network" << endl
             << "[5] Test Pumping Station removals from the network" << endl
             << "[6] Test Pipe removals from the network" << endl
             << "[0] Exit" << endl << endl;

        int option;
        cin >> option;

        switch (option) {
            case 4:
                while (true) {
                    cout << "Do you wish to manage the [S]mall or [L]arge network?" << endl;
                    char network;
                    cin >> network;
                    if (network == 'S' or network == 's') {
                        manager.removeReservoirCheckImpact(&manager.smallGraph);
                        break;
                    } else if (network == 'L' or network == 'l') {
                        manager.removeReservoirCheckImpact(&manager.largeGraph);
                        break;
                    } else {
                        cout << "Invalid option" << endl;
                        continue;
                    }
                }
                break;
            case 5:
                while (true) {
                    cout << "Do you wish to manage the [S]mall or [L]arge network?" << endl;
                    char network;
                    cin >> network;
                    if (network == 'S' or network == 's') {
                        manager.removeStationCheckImpact(&manager.smallGraph);
                        break;
                    } else if (network == 'L' or network == 'l') {
                        manager.removeStationCheckImpact(&manager.largeGraph);
                        break;
                    } else {
                        cout << "Invalid option" << endl;
                        continue;
                    }
                }
                break;
            case 6:
                while (true) {
                    cout << "Do you wish to manage the [S]mall or [L]arge network?" << endl;
                    char network;
                    cin >> network;
                    if (network == 'S' or network == 's') {
                        manager.removePipeCheckImpact(&manager.smallGraph);
                        break;
                    } else if (network == 'L' or network == 'l') {
                        manager.removePipeCheckImpact(&manager.largeGraph);
                        break;
                    } else {
                        cout << "Invalid option" << endl;
                        continue;
                    }
                }
                break;
            case 0:
                return 0;
            default:
                cout << "Invalid option" << endl;
                continue;
        }
    }
    return 0;
}
