#include "blockchain.h"
#include <sstream>
#include <iomanip>
#include <cstdlib>


using namespace std;

// constructor creates empty linked list
Blockchain::Blockchain() : head(0) { }

// destructor deletes all transactions
Blockchain::~Blockchain(){
  Transaction* next = head;
  while(next){
    head = head->prev;
    delete next;
    next = head;
  }
}

void Blockchain::add(int amount, string sender, string receiver){
  Transaction* temp = new Transaction;
  temp->amount = amount;
  temp->sender = sender;
  temp->receiver = receiver;
  temp->nonce = nonce(amount, sender, receiver);
  if(head){
    temp->hash = sha256(to_string(head->amount) + head->sender + head->receiver + head->hash
                         + head->nonce);
    temp->prev = head;
    
  }else{
    temp->hash = "NULL";
    temp->prev = NULL;
  }
  head = temp;
}

string Blockchain::nonce(int amount, string sender, string receiver){
  string amountString = to_string(amount);
  string nonce;
  // string noncePerm = amountString + sender + receiver + nonce;
  srand(time(NULL));
  while(sha256(amountString + sender + receiver + nonce).back() != '0'){
    int check = rand() % 100;
    if(check > 50){
      nonce += to_string(rand() % 10);
    }else{
      nonce += char(rand() % 26 + 97);
    }
  }
  return nonce;
}

string Blockchain::sha256(const string hashThis){
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, hashThis.c_str(), hashThis.size());
  SHA256_Final(hash, &sha256);
  stringstream ss;
  for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
    ss << hex << setw(2) << setfill('0') << (int)hash[i];
  }
  return ss.str();
}

int Blockchain::getBalance(string person){
  Transaction* p = head;
  int balance = 50;
  while(p){
    if(p->sender == person){
      balance -= p->amount;
    }
    if(p->receiver == person){
      balance += p->amount;
    }
    p = p->prev;
  }
  return balance;
}

void Blockchain::print(){
  printHelper(head);
}

void Blockchain::printHelper(Transaction* current){
  if(current == NULL){
    return;
  }
  printHelper(current->prev);
  cout << "Amount: " << current->amount << endl;
  cout << "Sender: " << current->sender << endl;
  cout << "Receiver: " << current->receiver << endl;
  cout << "Nonce: " << current->nonce << endl;
  cout << "Hash: " << current->hash << endl;
}