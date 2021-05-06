#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <iostream>
#include <string>
#include "openssl/sha.h"

class Blockchain{

  public:
    Blockchain(); // constructor
    ~Blockchain(); // destructor

    // adds transaction to blockchain
    void add(int amount, std::string sender, std::string receiver);

    int getBalance(std::string person); // returns amount of money this person has

    // prints blocks in order from oldest to most recent
    void print();

  private:
    struct Transaction{
      Transaction* prev;
      int amount;
      std::string sender;
      std::string receiver;
      std::string nonce;
      std::string hash;
    };

    Transaction* head; // points to most recent transaction

    // functions for sha256 hash
    std::string sha256(const std::string hashThis);

    // generates nonce for transaction and returns as string
    std::string nonce(int amount, std::string sender, std::string receiver);

    void printHelper(Transaction* current); // helper function for print()
};

#endif
