#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ------------------------ Data Structures ------------------------

struct EventNode {
    string eventName;
    EventNode* next;
};

struct AssignmentNode {
    string studentReg;
    string assignmentTitle;
    AssignmentNode* next;
};

struct NoticeNode {
    string noticeText;
    NoticeNode* next;
};

struct Subject {
    string subjectName;
    vector<string> assignments;
    vector<int> quizMarks;
    vector<int> assignmentMarks;
    vector<int> midMarks;
    vector<int> finalMarks;
    vector<int> labMarks;
    vector<int> attendance;

    vector<int>* allMarks[5];

    Subject() {
        allMarks[0] = &quizMarks;
        allMarks[1] = &assignmentMarks;
        allMarks[2] = &midMarks;
        allMarks[3] = &finalMarks;
        allMarks[4] = &labMarks;
    }
};



struct Fee {
    int total;
    int paid;
};

// ------------------------ Classes ------------------------

class EventList {
private:
    EventNode* head;
public:
    EventList() : head(NULL) {}

    void addEvent(string name) {
        EventNode* newNode = new EventNode;
        newNode->eventName = name;
        newNode->next = NULL;

        if (!head) head = newNode;
        else {
            EventNode* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
        cout << "Event added successfully!\n";
    }

    void updateEvent(string oldName, string newName) {
        EventNode* temp = head;
        while (temp) {
            if (temp->eventName == oldName) {
                temp->eventName = newName;
                cout << "Event updated successfully!\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Event not found!\n";
    }

    void deleteEvent(string name) {
        if (!head) return;
        if (head->eventName == name) {
            EventNode* temp = head;
            head = head->next;
            delete temp;
            cout << "Event deleted successfully!\n";
            return;
        }
        EventNode* temp = head;
        while (temp->next && temp->next->eventName != name) temp = temp->next;
        if (temp->next) {
            EventNode* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            cout << "Event deleted successfully!\n";
        } else cout << "Event not found!\n";
    }

    void showEvents() {
        if (!head) { cout << "No events found.\n"; return; }
        cout << "Events:\n";
        EventNode* temp = head;
        while (temp) {
            cout << "- " << temp->eventName << endl;
            temp = temp->next;
        }
    }
};

class AssignmentQueue {
private:
    AssignmentNode* front;
    AssignmentNode* rear;
public:
    AssignmentQueue() : front(NULL), rear(NULL) {}

    void submitAssignment(string reg, string title) {
        AssignmentNode* newNode = new AssignmentNode;
        newNode->studentReg = reg;
        newNode->assignmentTitle = title;
        newNode->next = NULL;

        if (!rear) front = rear = newNode;
        else { rear->next = newNode; rear = newNode; }

        cout << "Assignment submitted successfully!\n";
    }

    void processAssignment() {
        if (!front) { cout << "No assignments to process.\n"; return; }
        AssignmentNode* temp = front;
        cout << "Processing assignment of " << temp->studentReg << " : " << temp->assignmentTitle << endl;
        front = front->next;
        if (!front) rear = NULL;
        delete temp;
    }

    void showAssignments() {
        if (!front) { cout << "No assignments in queue.\n"; return; }
        cout << "Assignments:\n";
        AssignmentNode* temp = front;
        while (temp) {
            cout << "- " << temp->studentReg << " : " << temp->assignmentTitle << endl;
            temp = temp->next;
        }
    }
};

class NoticeStack {
private:
    NoticeNode* top;
public:
    NoticeStack() : top(NULL) {}

    void addNotice(string text) {
        NoticeNode* newNode = new NoticeNode;
        newNode->noticeText = text;
        newNode->next = top;
        top = newNode;
        cout << "Notice added successfully!\n";
    }

    void removeNotice() {
        if (!top) { cout << "No notices to remove.\n"; return; }
        NoticeNode* temp = top;
        cout << "Removed notice: " << temp->noticeText << endl;
        top = top->next;
        delete temp;
    }

    void showNotices() {
        if (!top) { cout << "No notices available.\n"; return; }
        cout << "Notices (latest first):\n";
        NoticeNode* temp = top;
        while (temp) { cout << "- " << temp->noticeText << endl; temp = temp->next; }
    }
};

// ------------------------ Users ------------------------

struct Faculty {
    string username;
    string password;
};

struct Student {
    string regNumber;
    string password;
    vector<Subject> subjects;
    Fee fee;
};

// ------------------------ Database Initialization ------------------------

vector<Faculty> facultyDB;
vector<Student> studentDB;

void initDatabase() {
    Faculty f;
    f.username = "admin";
    f.password = "1234";
    facultyDB.push_back(f);

    Student s;
    s.regNumber = "S1001";
    s.password = "pass";

    Subject sub1;
    sub1.subjectName = "Math";
    Subject sub2;
    sub2.subjectName = "Physics";

    s.subjects.push_back(sub1);
    s.subjects.push_back(sub2);

    s.fee.total = 5000;
    s.fee.paid = 200;

    studentDB.push_back(s);
}

// ------------------------ Helper Functions ------------------------

Faculty* facultyLogin() {
    string user, pass;
    cout << "Enter username: "; cin >> user;
    cout << "Enter password: "; cin >> pass;
    for (int i = 0; i < facultyDB.size(); i++) {
        if (facultyDB[i].username == user && facultyDB[i].password == pass)
            return &facultyDB[i];
    }
    return NULL;
}

Student* studentLogin() {
    string reg, pass;
    cout << "Enter registration number: "; cin >> reg;
    cout << "Enter password: "; cin >> pass;
    for (int i = 0; i < studentDB.size(); i++) {
        if (studentDB[i].regNumber == reg && studentDB[i].password == pass)
            return &studentDB[i];
    }
    return NULL;
}


// ------------------------ Main Program ------------------------

int main() { // {1
    EventList events;
    AssignmentQueue assignments;
    NoticeStack notices;

    initDatabase();

    string marksType[5] = { "Quiz", "Assignment", "Mid", "Final", "Lab" };

    bool running = true;
    while (running) { // Outer loop to return to main menu
        int mainChoice;

        cout << "\n=== Welcome to University Assistant ===\n";
        cout << "Login as:\n1. Faculty Member\n2. Student\n3. Exit\nEnter choice: ";
        cin >> mainChoice; 
        cin.ignore();

        if (mainChoice == 1) { // {2 - Faculty login
            Faculty* f = facultyLogin();
            if (!f) { 
                cout << "Invalid login!\n"; 
                continue; 
            } // }2.1 end login check

            int facChoice;
            do { // {3 - Faculty dashboard loop
                cout << "\n--- Faculty Dashboard ---\n";
                cout << "1. Teacher Console\n2. Management Console\n3. Logout\n4. Back\nEnter choice: ";
                cin >> facChoice; cin.ignore();

                // ------------------- Teacher Console -------------------
                if (facChoice == 1) { // {4 - Teacher console
                    int teachChoice;
                    do { // {5 - Teacher menu loop
                        cout << "\n--- Teacher Console ---\n";
                        cout << "1. Manage Marks\n2. Manage Assignments\n3. Manage Attendance\n4. Back\nChoice: ";
                        cin >> teachChoice; cin.ignore();

                        // ------------------- Manage Marks -------------------
                        if (teachChoice == 1) { // {6
                            cout << "Choose student to update marks:\n";
                            for (int i = 0; i < studentDB.size(); i++)
                                cout << i + 1 << ". " << studentDB[i].regNumber << endl;

                            int sChoice;
                            cin >> sChoice; cin.ignore();
                            if (sChoice <= 0 || sChoice > studentDB.size()) continue;

                            Student &stu = studentDB[sChoice - 1];

                            cout << "Choose subject:\n";
                            for (int i = 0; i < stu.subjects.size(); i++)
                                cout << i + 1 << ". " << stu.subjects[i].subjectName << endl;

                            int subChoice;
                            cin >> subChoice; cin.ignore();
                            if (subChoice <= 0 || subChoice > stu.subjects.size()) continue;

                            Subject &sub = stu.subjects[subChoice - 1];

                            int mChoice;
                            do { // {7
                                cout << "\nSelect marks type to update:\n";
                                cout << "1. Quiz Marks\n2. Assignment Marks\n3. Mid Marks\n4. Final Term Marks\n5. Back\nChoice: ";
                                cin >> mChoice; cin.ignore();

                                if (mChoice == 1) { // Quiz {8
                                    int qCount = sub.quizMarks.size();
                                    if (qCount < 4) {
                                        int mark;
                                        cout << "Enter marks for Quiz " << qCount + 1 << ": ";
                                        cin >> mark; cin.ignore();
                                        sub.quizMarks.push_back(mark);
                                        cout << "Quiz " << qCount + 1 << " marks uploaded!\n";
                                    } else cout << "All 4 quiz marks already uploaded.\n";
                                } // }8

                                else if (mChoice == 2) { // Assignment {9
                                    int aCount = sub.assignmentMarks.size();
                                    if (aCount < 4) {
                                        int mark;
                                        cout << "Enter marks for Assignment " << aCount + 1 << ": ";
                                        cin >> mark; cin.ignore();
                                        sub.assignmentMarks.push_back(mark);
                                        cout << "Assignment " << aCount + 1 << " marks uploaded!\n";
                                    } else cout << "All 4 assignment marks already uploaded.\n";
                                } // }9

                                else if (mChoice == 3) { // Mid {10
                                    int mark;
                                    cout << "Enter Mid term marks: ";
                                    cin >> mark; cin.ignore();
                                    sub.midMarks.push_back(mark);
                                    cout << "Mid marks uploaded!\n";
                                } // }10

                                else if (mChoice == 4) { // Final {11
                                    int mark;
                                    cout << "Enter Final term marks: ";
                                    cin >> mark; cin.ignore();
                                    sub.finalMarks.push_back(mark);
                                    cout << "Final marks uploaded!\n";
                                } // }11

                            } while (mChoice != 5); // }7
                        } // }6

                        // ------------------- Manage Assignments -------------------
                        else if (teachChoice == 2) { // {12
                            cout << "Choose student to manage assignments:\n";
                            for (int i = 0; i < studentDB.size(); i++)
                                cout << i + 1 << ". " << studentDB[i].regNumber << endl;

                            int sChoice;
                            cin >> sChoice; cin.ignore();
                            if (sChoice <= 0 || sChoice > studentDB.size()) continue;

                            Student &stu = studentDB[sChoice - 1];

                            cout << "Choose subject:\n";
                            for (int i = 0; i < stu.subjects.size(); i++)
                                cout << i + 1 << ". " << stu.subjects[i].subjectName << endl;

                            int subChoice;
                            cin >> subChoice; cin.ignore();
                            if (subChoice <= 0 || subChoice > stu.subjects.size()) continue;

                            Subject &sub = stu.subjects[subChoice - 1];

                            int aChoice;
                            do { // {13
                                cout << "\n--- Manage Assignments ---\n";
                                cout << "1. Upload New Assignment\n2. View All Assignments\n3. Delete Assignment\n4. Back\nChoice: ";
                                cin >> aChoice; cin.ignore();

                                if (aChoice == 1) { // Upload new {14
                                    if (sub.assignments.size() < 4) {
                                        string newAssignment;
                                        cout << "Enter assignment title or description: ";
                                        getline(cin, newAssignment);
                                        sub.assignments.push_back(newAssignment);
                                        cout << "Assignment " << sub.assignments.size() << " uploaded successfully!\n";
                                    } else cout << "All 4 assignments already uploaded.\n";
                                } // }14
                                else if (aChoice == 2) { // View {15
                                    cout << "\nAssignments for " << sub.subjectName << ":\n";
                                    if (sub.assignments.empty()) cout << "No assignments uploaded yet.\n";
                                    else for (int i = 0; i < sub.assignments.size(); i++)
                                        cout << "Assignment " << i + 1 << ": " << sub.assignments[i] << endl;
                                } // }15
                                else if (aChoice == 3) { // Delete {16
                                    if (sub.assignments.empty()) cout << "No assignments to delete.\n";
                                    else {
                                        cout << "Choose assignment number to delete:\n";
                                        for (int i = 0; i < sub.assignments.size(); i++)
                                            cout << i + 1 << ". " << sub.assignments[i] << endl;

                                        int delChoice;
                                        cin >> delChoice; cin.ignore();
                                        if (delChoice > 0 && delChoice <= sub.assignments.size()) {
                                            sub.assignments.erase(sub.assignments.begin() + delChoice - 1);
                                            cout << "Assignment deleted successfully!\n";
                                        } else cout << "Invalid choice.\n";
                                    }
                                } // }16
                            } while (aChoice != 4); // }13
                        } // }12

                        // ------------------- Manage Attendance -------------------
                        else if (teachChoice == 3) { // {17
                            cout << "Choose student to manage attendance:\n";
                            for (int i = 0; i < studentDB.size(); i++)
                                cout << i + 1 << ". " << studentDB[i].regNumber << endl;

                            int sChoice;
                            cin >> sChoice; cin.ignore();
                            if (sChoice <= 0 || sChoice > studentDB.size()) continue;

                            Student &stu = studentDB[sChoice - 1];

                            cout << "Choose subject:\n";
                            for (int i = 0; i < stu.subjects.size(); i++)
                                cout << i + 1 << ". " << stu.subjects[i].subjectName << endl;

                            int subChoice;
                            cin >> subChoice; cin.ignore();
                            if (subChoice <= 0 || subChoice > stu.subjects.size()) continue;

                            Subject &sub = stu.subjects[subChoice - 1];

                            int attChoice;
                            do { // {18
                                cout << "\n--- Manage Attendance ---\n";
                                cout << "1. Mark Attendance\n2. View Attendance\n3. Delete Attendance Entry\n4. Back\nChoice: ";
                                cin >> attChoice; cin.ignore();

                                if (attChoice == 1) { // Mark {19
                                    char status;
                                    cout << "Enter attendance (P for Present / A for Absent): ";
                                    cin >> status; cin.ignore();
                                    status = toupper(status);
                                    if (status == 'P' || status == 'A') {
                                        sub.attendance.push_back(status);
                                        cout << "Attendance marked successfully!\n";
                                    } else cout << "Invalid input. Use P or A only.\n";
                                } // }19
                                else if (attChoice == 2) { // View {20
                                    cout << "\nAttendance Record for " << sub.subjectName << ":\n";
                                    if (sub.attendance.empty()) cout << "No attendance records yet.\n";
                                    else for (int i = 0; i < sub.attendance.size(); i++)
                                        cout << "Day " << i + 1 << ": " << sub.attendance[i] << endl;
                                } // }20
                                else if (attChoice == 3) { // Delete {21
                                    if (sub.attendance.empty()) cout << "No attendance records to delete.\n";
                                    else {
                                        cout << "Choose attendance entry to delete:\n";
                                        for (int i = 0; i < sub.attendance.size(); i++)
                                            cout << i + 1 << ". Day " << i + 1 << " - " << sub.attendance[i] << endl;

                                        int delChoice;
                                        cin >> delChoice; cin.ignore();

                                        if (delChoice > 0 && delChoice <= sub.attendance.size()) {
                                            sub.attendance.erase(sub.attendance.begin() + delChoice - 1);
                                            cout << "Attendance entry deleted successfully!\n";
                                        } else cout << "Invalid choice.\n";
                                    }
                                } // }21
                            } while (attChoice != 4); // }18
                        } // }17

                    } while (teachChoice != 4); // }5
                } // }4

                // ------------------- Management Console -------------------
                else if (facChoice == 2) { // {22
                    int manChoice;
                    do { // {23
                        cout << "\n--- Management Console ---\n";
                        cout << "1. Student Details\n2. Event Management\n3. Notice Management\n4. Back\nChoice: ";
                        cin >> manChoice; cin.ignore();

                        if (manChoice == 1) { // {24
                            cout << "\n--- Student Details ---\n";
                            for (int i = 0; i < studentDB.size(); i++) {
                                Student &s = studentDB[i];
                                cout << "Reg: " << s.regNumber << ", Fee Paid: " << s.fee.paid << "/" << s.fee.total << endl;
                                for (int j = 0; j < s.subjects.size(); j++) {
                                    Subject &sub = s.subjects[j];
                                    cout << "Subject: " << sub.subjectName << "\nMarks:\n";
                                    string markNames[4] = { "Quiz Marks", "Assignment Marks", "Mid Marks", "Final Term Marks" };
                                    for (int mt = 0; mt < 4; mt++) {
                                        cout << markNames[mt] << ": ";
                                        for (int k = 0; k < sub.allMarks[mt]->size(); k++)
                                            cout << (*sub.allMarks[mt])[k] << " ";
                                        cout << "\n";
                                    }
                                    cout << "Attendance: ";
                                    for (int k = 0; k < sub.attendance.size(); k++) cout << sub.attendance[k] << " ";
                                    cout << "\nAssignments: ";
                                    for (int k = 0; k < sub.assignments.size(); k++) cout << sub.assignments[k] << ", ";
                                    cout << "\n";
                                }
                            }
                        } // }24
                        else if (manChoice == 2) { // {25
                            int eChoice;
                            do { // {26
                                cout << "\n--- Event Management ---\n1. Add\n2. Update\n3. Delete\n4. Show\n5. Back\nChoice: ";
                                cin >> eChoice; cin.ignore();
                                if (eChoice == 1) { string n; cout << "Event name: "; getline(cin, n); events.addEvent(n); }
                                else if (eChoice == 2) { string oldN,newN; cout << "Old name: "; getline(cin,oldN); cout << "New name: "; getline(cin,newN); events.updateEvent(oldN,newN);}
                                else if (eChoice == 3) { string n; cout << "Event name to delete: "; getline(cin,n); events.deleteEvent(n);}
                                else if (eChoice == 4) events.showEvents();
                            } while (eChoice != 5); // }26
                        } // }25
                        else if (manChoice == 3) { // {27
                            int nChoice;
                            do { // {28
                                cout << "\n--- Notice Management ---\n1. Add\n2. Show\n3. Remove Latest\n4. Back\nChoice: ";
                                cin >> nChoice; cin.ignore();
                                if (nChoice == 1) { string t; cout << "Notice: "; getline(cin,t); notices.addNotice(t); }
                                else if (nChoice == 2) notices.showNotices();
                                else if (nChoice == 3) notices.removeNotice();
                            } while (nChoice != 4); // }28
                        } // }27
                    } while (manChoice != 4); // }23
                } // }22

            } while (facChoice != 3 && facChoice != 4); // }3
        } // }2

        // ------------------- Student Login -------------------
        else if (mainChoice == 2) { // {29
            Student* s = studentLogin();
            if (!s) { cout << "Invalid login!\n"; continue; }

            int stuChoice;
            do { // {30
                cout << "\n--- Student Dashboard ---\n";
                cout << "1. Subjects\n2. Fee Status\n3. Notices\n4. Logout\nChoice: ";
                cin >> stuChoice; cin.ignore();

                if (stuChoice == 1) { // {31
                    int subChoice;
                    cout << "Subjects:\n";
                    for (int i = 0; i < s->subjects.size(); i++)
                        cout << i + 1 << ". " << s->subjects[i].subjectName << endl;

                    cout << "Choose subject number: ";
                    cin >> subChoice; cin.ignore();

                    if (subChoice > 0 && subChoice <= s->subjects.size()) { // {32
                        Subject &sub = s->subjects[subChoice - 1];
                        cout << "\n--- Subject Summary ---\n";
                        cout << "Subject: " << sub.subjectName << "\n";
                        cout << "Attendance: ";
                        for (int i = 0; i < sub.attendance.size(); i++) cout << sub.attendance[i] << " ";
                        cout << "\nQuiz Marks:\n";
                        for (int i = 0; i < sub.quizMarks.size(); i++) cout << "Quiz " << i + 1 << ": " << sub.quizMarks[i] << endl;
                        cout << "Assignment Marks:\n";
                        for (int i = 0; i < sub.assignmentMarks.size(); i++) cout << "Assignment " << i + 1 << ": " << sub.assignmentMarks[i] << endl;
                        cout << "Mid Marks:\n";
                        for (int i = 0; i < sub.midMarks.size(); i++) cout << "Mid " << i + 1 << ": " << sub.midMarks[i] << endl;
                        cout << "Final Term Marks:\n";
                        for (int i = 0; i < sub.finalMarks.size(); i++) cout << "Final " << i + 1 << ": " << sub.finalMarks[i] << endl;
                        cout << "Assignments Uploaded:\n";
                        for (int i = 0; i < sub.assignments.size(); i++) cout << "Assignment " << i + 1 << ": " << sub.assignments[i] << endl;
                    } // }32
                } // }31
                else if (stuChoice == 2) { cout << "Fee Paid: " << s->fee.paid << "/" << s->fee.total << endl; cout << "Remaining: " << s->fee.total - s->fee.paid << endl; }
                else if (stuChoice == 3) notices.showNotices();
            } while (stuChoice != 4); // }30
        } // }29

        else if (mainChoice == 3) {
            cout << "Thank you for coming. Have a Nice Day!\n";
            running = false;
        }

        else cout << "Invalid choice!\n";
    }

    return 0;
} // }1 END OF MAIN
