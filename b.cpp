struct node {
    char key;
    int val;
    node *next, *prev;
    node(char k) : key(k), prev(nullptr), next(nullptr) {}
};

class DLL {

  public:
    node *h, *t;
    DLL() {
        t = new node(0);
        h = new node(0);
        t->prev = h;
        h->next = t;
    }

    string got(node *now) {
        string s;
        node *use = now;
        rep(i, 0, 10) {
            if (use->prev == this->h) break;
            use = use->prev;
            s += (use->key);
        }
        reverse(s.begin(), s.end());
        return s;
    }
};
class TextEditor {
  public:
    DLL l;
    node *cur;
    TextEditor() {
        cur = l.t;
    }

    void addText(string s) {
        for (auto &i : s) {
            auto node = new node(i);
            node->prev = cur->prev;
            node->next = cur;
            cur->prev = node;
        }
        cout << l.got(cur) << endl;
    }

    int deleteText(int n) {
        rep(i, 0, n) {
            auto node = cur->prev;
            if (node == l.h) return i;
            cur->prev = node->prev;
            node->prev->next = node->next;
        }
        return n;
    }

    string cursorLeft(int k) {
        rep(i, 0, k) {
            if (cur->prev == l.h) return "";
            cur = cur->prev;
        }
        return l.got(cur);
    }

    string cursorRight(int k) {
        rep(i, 0, k) {
            if (cur->next == nullptr) break;
            cur = cur->next;
        }
        return l.got(cur);
    }
};
