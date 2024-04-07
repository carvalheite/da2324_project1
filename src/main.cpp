#include <iostream>
#include "Manager.h"

int main() {
    Manager manager = Manager();

    cout << "Welcome to the Water Network Manager" << endl << "What would you like to do?" << endl;

    while (true) {
        //TODO
        cout << endl
             << "[1]  Determine the maximum amount of water that can reach each or a specific city" << endl
             << "[2]  Determine Water Deficit in network" << endl
             << "[3]  Balance the load across the network" << endl
        //DONE
             << "[4]  Test Reservoir removals from the network" << endl
             << "[5]  Test Pumping Station removals from the network" << endl
             << "[6]  Test Pipe removals from the network" << endl
             << "[0]  Exit" << endl << endl;

        int option;
        cin >> option;

        switch (option) {


            case 1:
                while (true){
                    cout << "Do you wish to manage the [S]mall or [L]arge network?" << endl;
                    char network;
                    cin >> network;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Choose the desired City_Code: (If you wish to display all, write 'all')" << endl;
                    string cityCode;
                    getline(cin, cityCode);

                    if (network == 'S' or network == 's') {
                        manager.maxWaterFlowForCity(&manager.smallGraph, cityCode, "small", true);
                        break;
                    } else if (network == 'L' or network == 'l') {
                        manager.maxWaterFlowForCity(&manager.largeGraph, cityCode, "large", true);
                        break;
                    } else {
                        cout << "Invalid option" << endl;
                        continue;
                    }
                }
                break;
            case 2:
                while (true){
                    cout << "Do you wish to manage the [S]mall or [L]arge network?" << endl;
                    char network;
                    cin >> network;
                    cout << endl;

                    if (network == 'S' or network == 's') {
                        manager.checkWaterDeficit(&manager.smallGraph,"small");
                        break;
                    } else if (network == 'L' or network == 'l') {
                        manager.checkWaterDeficit(&manager.largeGraph,"large");
                        break;
                    } else {
                        cout << "Invalid option" << endl;
                        continue;
                    }
                }
                break;
            case 3:
                while (true){
                    cout << "Do you wish to manage the [S]mall or [L]arge network?" << endl;
                    char network;
                    cin >> network;
                    cout << endl;

                    if (network == 'S' or network == 's') {
                        manager.balanceNetworkFLow(&manager.smallGraph,"small");
                        break;
                    } else if (network == 'L' or network == 'l') {
                        manager.balanceNetworkFLow(&manager.largeGraph,"large");
                        break;
                    } else {
                        cout << "Invalid option" << endl;
                        continue;
                    }
                }
                break;
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
