#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "../utils/utils.hpp"
using namespace std;

const vector<char> ranking = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};

class Hand {
  public:
    string value;
    int bet;
    int handScore;
    Hand(string data) {
      vector<string> raw = get_strings(data);
      value = raw[0];
      bet = stoi(raw[1]);
      handScore = calculateHand();
    }
    int calculateHand();
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

int Hand::calculateHand() {
  map<char, int> m;
  auto chars = value.c_str();

  for (const char *p = chars; *p != '\0'; ++p) {
    if (m.find(*p) == m.end()) {
      m[*p] = 0;
    }
    m[*p] += 1;
  }

  //High Card
  if (m.size() == 5) {
    return 1;
  }

  //One pair
  else if (m.size() == 4) {
    return 2;
  }

  //Two pair and Three of a kind
  else if (m.size() == 3) {
    int m_max = m.begin()->second;
    for (auto &p: m) {
      m_max = max(m_max, p.second);
    }


    //Three of a kind
    if (m_max == 3) {
      return 4;
    }
    //Two pair
    else {
      return 3;
    }
  }
  //Four of a kind and Full house
  else if (m.size() == 2) {
    int m_max = m.begin()->second;
    for (auto &p: m) {
      m_max = max(m_max, p.second);
    }

    //four of a kind
    if (m_max == 4) {
      return 6;
    }
    //full house
    else {
      return 5;
    } 
  }
  else {
    return 7;
  }

}

int main() {
  vector<string> lines = readlines("data.txt");
  vector<Hand> hands;
  std::transform(lines.begin(), lines.end(), back_inserter(hands), [](string l) {return Hand(l);});
  sort(hands.begin(), hands.end(), handComparator());

  int sum = 0;
  int len = hands.size();
  for(int i = 0; i < hands.size(); i++) {
    sum += (len - i) * hands[i].bet;
  }

  int i = 0;
  for (auto hand : hands) {
    i++;
  }

  cout << sum << endl;

}