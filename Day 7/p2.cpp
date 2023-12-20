#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "../utils/utils.hpp"
using namespace std;

const vector<char> ranking = {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};

class Hand {
  public:
    string value;
    int bet;
    int handScore;
    Hand(string data) {
      vector<string> raw = get_strings(data);
      value = raw[0];
      bet = stoi(raw[1]);
      calculateHand();
    }
    void calculateHand();
    void update_j(int s, map<char, int> m);
};

bool compare_hand_values(Hand hand1, Hand hand2) {
  auto c_h1 = hand1.value.c_str();
  auto c_h2 = hand2.value.c_str();


  for(const char *p = c_h1; *p != '\0'; ++p) {
    auto r_1 = find(ranking.begin(), ranking.end(), *p);
    auto r_2 = find(ranking.begin(), ranking.end(), *c_h2);

    if (r_1 != r_2) {
      return r_1 < r_2;
    }
    ++c_h2;
  }
  return true;
}

struct handComparator
{
    bool operator ()(const Hand & hand1, const Hand & hand2)
    {
        if(hand1.handScore != hand2.handScore)
            return hand1.handScore > hand2.handScore;
        return compare_hand_values(hand1, hand2);
    }
};

void Hand::calculateHand() {
  map<char, int> m;
  auto chars = value.c_str();
  bool j_found = false;
  int m_max = 0;

  for (const char *p = chars; *p != '\0'; ++p) {
    if (*p == 'J') {
      j_found =true;
    }
    if (m.find(*p) == m.end()) {
      m[*p] = 0;
    }
    m[*p] += 1;
    m_max = max(m_max, m[*p]);
  }
  
  int m_size = m.size();

  //High Card
  if (m_size == 5) {
    handScore = 1;
  }

  //One pair
  else if (m_size == 4) {
    handScore= 2;
  }

  //Two pair and Three of a kind
  else if (m_size == 3) {
    //Three of a kind
    if (m_max == 3) {
      handScore= 4;
    }
    //Two pair
    else {
      handScore =3;
    }
  }
  //Four of a kind and Full house
  else if (m_size == 2) {
    //four of a kind
    if (m_max == 4) {
      handScore= 6;
    }
    //full house
    else {
      handScore= 5;
    } 
  }
  else {
    handScore= 7;
  }
  
  if (j_found) {
    update_j(handScore, m);
  }
}

void Hand::update_j(int s, map<char,int> m) {
  switch (s)
  {
  case 1: 
    handScore = 2;
  break;
  case 2:
    handScore = 4;
  break;
  case 3:
    if (m['J'] == 1) {
      handScore = 5;
    }
    else {
      handScore = 6;
    }
    break;
  case 4:
    handScore = 6;
    break;
  case 5:
    handScore = 7;
    break;
  case 6:
    handScore = 7;
    break;
  default:
    break;
  }
}

int main() {
  vector<string> lines = readlines("data.txt");
  vector<Hand> hands;
  std::transform(lines.begin(), lines.end(), back_inserter(hands), [](string l) {return Hand(l);});
  sort(hands.begin(), hands.end(), handComparator());

  int sum = 0;
  int len = hands.size();
  for(int i = 0; i < len; i++) {
    sum += (len - i) * hands[i].bet;
  }
  cout << sum << endl;
}