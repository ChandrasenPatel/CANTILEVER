#include <iostream>
#include <cstdlib> 
#include <ctime>   
using namespace std;
int main() {

    srand(time(0));

    int max_number = 100;
    int min_number = 1;

    int secretNumber = (rand() % max_number) + min_number;

    int guess = 0;
    int attempts = 0;

    cout << "--- Welcome to the Number Guessing Game! ---" <<endl;
    cout << "I have chosen a secret number between " << min_number << " and " << max_number << "." << endl;
    cout << "Try to guess it!" << endl;
    cout << "-----------------------------------------------" <<endl;


    do {
        cout << "Enter your guess: ";
        
        if (!(cin >> guess)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue; 
        }

        attempts++;

       
        if (guess > secretNumber) {
            cout << "Try a smaller number." << endl;
        } else if (guess < secretNumber) {
            cout << "Try a larger number." << endl;
        } else {
            cout <<"\n Congratulations! You won. " << secretNumber
                      << " in " << attempts << " attempts!" <<endl;
            break; 
        }

    } while (true); 

    cout << "\n--- Game Over ---" <<endl;

    return 0;
}