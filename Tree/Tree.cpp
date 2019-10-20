#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;


struct node {
  struct node* p;
  vector<struct node*> ch;
  string s;
  bool f;
};
struct tree {
  struct node* h;
};
// return
vector<string> rsv;

// clean function
void dn(struct node* n) {
  int i = 0;
  while (i < n->ch.size()) {
    struct node* tc = n->ch[i];
    n->ch[i] = NULL;
    n->ch.erase(n->ch.begin() + i);
    dn(tc);
  }
  n->p = NULL;
  delete n;
}

// traveler
void tr(struct node* n, string s) {
  s.append("/");
  s.append(n->s);
  if (n->f) {
    rsv.push_back(s);
    // ignore child
    /*int i = 0;
    while (i < n->ch.size()) {
      some code here
      dn(n->ch[i], s);
      i++;
    }*/
  }
  else {
    int i = 0;
    while (i < n->ch.size()) {
      tr(n->ch[i], s);
      i++;
    }
  }
}

// main
vector<string> removeSubfolders(vector<string>& folder) {
  struct tree t;
  t.h = new struct node;
  t.h->p = NULL;
  t.h->f = false;
  t.h->s = "";
  int i = 0;
  struct node* n = t.h;
  while (i < folder.size()) {
    stringstream ss;
    ss.str(folder[i]);
    string fs;
    getline(ss, fs, '/');

    // start to loop string
    while (getline(ss, fs, '/')) {// only check child, since the folder here is same as node string
      int j = 0;
      bool found = false;
      while (j < n->ch.size()) {// look for child
        if (n->ch[j]->s.compare(fs) == 0) {
          n = n->ch[j];
          found = true;
          break;
        }
        j++;
      }
      if (!found) { // no child met
        struct node* tn = new struct node;
        tn->p = n;
        tn->s = fs;
        tn->f = false;
        n->ch.push_back(tn);
        n = tn; // assign new child to node for next loop
      }
      else {
        // final folder found
        if (n->f)
          break;
      }
    }
    // parse all folder in string
    n->f = true; // this is the end point
    // delete all children
    /* ignore children
    int j = 0;
    while (j < n->ch.size()) {
      struct node* tc = n->ch[j];
      n->ch[j] = NULL;
      n->ch.erase(n->ch.begin() + j);
      dn(tc);
    }
    */
    n = t.h;
    i++;
  }
  // loop end 
  // travel and return
  int ii = 0;
  while (ii < t.h->ch.size()) {
    tr(t.h->ch[ii], "");
    ii++;
  }


  // delete all
  dn(t.h);
  return rsv;
}

int main() {
    std::cout << "Hello World!\n";
    vector<string> v = {"/a/b", "/a"};
    v = removeSubfolders(v);
    cout << v.size() << endl;
    for (int i = 0; i < v.size(); i++)
    cout << removeSubfolders(v)[i] << endl;
}