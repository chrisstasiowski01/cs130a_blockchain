#include "blockchain.h"

#include <cstdlib>




using namespace std;

int main(){
  Blockchain chain;
  while(1){

    cout << "Welcome to the transaction-chain application. . . ." << endl;
    cout << "1) Add a transaction to the chain." << endl;
    cout << "2) Find Balance of a person." << endl;
    cout << "3) Print the chain." << endl;
    cout << "4) Exit." << endl;
    cout << "Which operation do you want to make? (1, 2, 3, 4):" << endl;
    int selection;
    cin >> selection;

    if(selection == 1){
      cout << "Integer amount of money:" << endl;
      int amount;
      cin >> amount;
      cout << "Sender name" << endl;
      string sender;
      cin >> sender;
      cout << "Receiver name" << endl;
      string receiver;
      cin >> receiver;
      chain.add(amount, sender, receiver);
    }

    if(selection == 2){
      cout << "Person name" << endl;
      string person;
      cin >> person;
      cout << chain.getBalance(person) << endl;
    }

    if(selection == 3){
      chain.print();
    }

    if(selection == 4){
      break;
    }
  }
  return 0;
}