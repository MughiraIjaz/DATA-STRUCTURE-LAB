#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct Student {
    int id;
    string name;
    string dept;
    int sem;
    float cgpa;
    int credits;
    int year;
};

struct Node {
    Student s;
    Node* next;
};



Node* newNode(Student s) {
    Node* n = new Node;
    n->s = s;
    n->next = NULL;
    return n;
}

void insertEnd(Node*& head, Student s) {
    Node* n = newNode(s);
    if (!head) {
        head = n;
        return;
    }
    Node* t = head;
    while (t->next) t = t->next;
    t->next = n;
}

Node* copyList(Node* head) {
    Node* nhead = NULL;
    while (head) {
        insertEnd(nhead, head->s);
        head = head->next;
    }
    return nhead;
}

void freeList(Node*& head) {
    while (head) {
        Node* t = head;
        head = head->next;
        delete t;
    }
}


int isValid(Student s) {
    if (s.cgpa < 0 || s.cgpa > 4) return 0;
    if (s.sem < 1 || s.sem > 8) return 0;
    if (s.credits < s.sem * 12 || s.credits > s.sem * 30) return 0;
    return 1;
}

int idExists(Node* head, int id) {
    while (head) {
        if (head->s.id == id) return 1;
        head = head->next;
    }
    return 0;
}



long long bubbleCmp = 0, bubbleSwap = 0;
long long selectCmp = 0, selectSwap = 0;



void bubbleSortCGPA(Node* head) {
    int swapped;
    do {
        swapped = 0;
        Node* c = head;
        while (c && c->next) {
            bubbleCmp++;
            if (c->s.cgpa < c->next->s.cgpa ||
               (c->s.cgpa == c->next->s.cgpa && c->s.credits < c->next->s.credits)) {
                Student tmp = c->s;
                c->s = c->next->s;
                c->next->s = tmp;
                bubbleSwap++;
                swapped = 1;
            }
            c = c->next;
        }
    } while (swapped);
}

void selectionSortYear(Node* head) {
    for (Node* i = head; i; i = i->next) {
        Node* min = i;
        for (Node* j = i->next; j; j = j->next) {
            selectCmp++;
            if (j->s.year < min->s.year ||
               (j->s.year == min->s.year && j->s.id < min->s.id))
                min = j;
        }
        if (min != i) {
            Student tmp = i->s;
            i->s = min->s;
            min->s = tmp;
            selectSwap++;
        }
    }
}

void bubbleSortDept(Node* head) {
    int swapped;
    do {
        swapped = 0;
        Node* c = head;
        while (c && c->next) {
            if (c->s.dept > c->next->s.dept ||
               (c->s.dept == c->next->s.dept && c->s.sem > c->next->s.sem) ||
               (c->s.dept == c->next->s.dept && c->s.sem == c->next->s.sem && c->s.cgpa < c->next->s.cgpa)) {
                Student t = c->s;
                c->s = c->next->s;
                c->next->s = t;
                swapped = 1;
            }
            c = c->next;
        }
    } while (swapped);
}

void bubbleSortName(Node* head) {
    int swapped;
    do {
        swapped = 0;
        Node* c = head;
        while (c && c->next) {
            if (c->s.name > c->next->s.name) {
                Student t = c->s;
                c->s = c->next->s;
                c->next->s = t;
                swapped = 1;
            }
            c = c->next;
        }
    } while (swapped);
}



void writeRankCGPA(Node* h) {
    ofstream out("ranked_by_cgpa.txt");
    out << "RANKED BY CGPA\n";
    int r = 1;
    while (h) {
        out << r++ << " " << h->s.id << " " << h->s.name << " " << h->s.dept
            << " " << h->s.sem << " " << fixed << setprecision(2)
            << h->s.cgpa << " " << h->s.credits << " " << h->s.year << "\n";
        h = h->next;
    }
}

void writeEnrollment(Node* h) {
    ofstream out("sorted_by_enrollment.txt");
    int y = -1, c = 0;
    float sum = 0;
    while (h) {
        if (h->s.year != y) {
            if (y != -1) out << "Average CGPA: " << sum / c << "\n\n";
            y = h->s.year;
            c = 0; sum = 0;
            out << "Year " << y << "\n";
        }
        out << h->s.id << " " << h->s.name << " " << h->s.cgpa << "\n";
        sum += h->s.cgpa;
        c++;
        h = h->next;
    }
    if (c) out << "Average CGPA: " << sum / c << "\n";
}

void writeDept(Node* h) {
    ofstream out("department_analysis.txt");
    string d = "";
    int c = 0, cr = 0;
    float sum = 0, hi = 0, lo = 4;
    while (h) {
        if (h->s.dept != d) {
            if (d != "") {
                out << "Students: " << c << " Avg: " << sum / c
                    << " High: " << hi << " Low: " << lo
                    << " AvgCredits: " << cr / c << "\n\n";
            }
            d = h->s.dept;
            out << "Department " << d << "\n";
            c = cr = 0; sum = 0; hi = 0; lo = 4;
        }
        out << h->s.name << " Sem " << h->s.sem << " CGPA " << h->s.cgpa << "\n";
        sum += h->s.cgpa;
        cr += h->s.credits;
        if (h->s.cgpa > hi) hi = h->s.cgpa;
        if (h->s.cgpa < lo) lo = h->s.cgpa;
        c++;
        h = h->next;
    }
    if (c)
        out << "Students: " << c << " Avg: " << sum / c
            << " High: " << hi << " Low: " << lo
            << " AvgCredits: " << cr / c << "\n";
}

void writeTiers(Node* h) {
    ofstream out("performance_tiers.txt");
    Node* t[5] = {NULL};
    int cnt[5] = {0};
    int total = 0;

    while (h) {
        int i;
        if (h->s.cgpa >= 3.7) i = 0;
        else if (h->s.cgpa >= 3.3) i = 1;
        else if (h->s.cgpa >= 3.0) i = 2;
        else if (h->s.cgpa >= 2.5) i = 3;
        else i = 4;
        insertEnd(t[i], h->s);
        cnt[i]++; total++;
        h = h->next;
    }

    const char* names[5] = {"Elite","High","Good","Satisfactory","Needs Improvement"};
    for (int i = 0; i < 5; i++) {
        bubbleSortName(t[i]);
        out << names[i] << "\n";
        Node* x = t[i];
        while (x) {
            out << x->s.name << " " << x->s.cgpa << "\n";
            x = x->next;
        }
        out << "Count " << cnt[i] << " Percent " << (total ? cnt[i] * 100.0 / total : 0) << "\n\n";
        freeList(t[i]);
    }
}



void searchByID(Node* h, int id) {
    ofstream out("search_results.txt", ios::app);
    while (h) {
        if (h->s.id == id) {
            out << "Found: " << h->s.id << " " << h->s.name << " " << h->s.cgpa << "\n";
            return;
        }
        h = h->next;
    }
    out << "ID " << id << " not found\n";
}

int main() {

    ifstream in("students_data.txt");
    ofstream issues("data_issues.txt");
    ofstream dup("duplicates_report.txt");

    if (!in) {
        cout << "Error opening students_data.txt\n";
        return 0;
    }

    Node* master = NULL;

    int n;
    in >> n;
    in.ignore();

    for (int i = 0; i < n; i++) {

        Student s;

        in >> s.id;
        in.ignore();

        string line;
        getline(in, line);

        stringstream ss(line);
        string word;

        s.name = "";

        while (ss >> word) {
            if (word.size() == 3) {
                s.dept = word;
                break;
            }
            if (!s.name.empty())
                s.name += " ";
            s.name += word;
        }

        ss >> s.sem >> s.cgpa >> s.credits >> s.year;

        if (!isValid(s)) {
            issues << "Invalid data near ID " << s.id << endl;
            continue;
        }

        if (idExists(master, s.id)) {
            dup << "Duplicate ID: " << s.id << endl;
            continue;
        }

        insertEnd(master, s);
    }

    in.close();

    writeRankCGPA(master);
    writeEnrollment(master);
    writeDept(master);
    writeTiers(master);

    searchByID(master, master ? master->s.id : 0);

    ofstream perf("algorithm_performance.txt", ios::out);
    perf << "Bubble comparisons: " << bubbleCmp << " swaps: " << bubbleSwap << "\n";
    perf << "Selection comparisons: " << selectCmp << " swaps: " << selectSwap << "\n";
    perf.close();

    freeList(master);

    issues.close();
    dup.close();

    return 0;
}
