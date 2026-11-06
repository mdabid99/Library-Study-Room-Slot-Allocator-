//CA1 - Library Study-Room Slot Allocator 
#include <iostream>
#include <string>
using namespace std;

class Booking {
    int id, room, slot, day;
    string name;
    static int total;                      // static: counts all bookings
public:
    Booking() { id = room = slot = day = 0; }

    int getId() const { return id; }       // inline function

    void setData(int id, string name, int room, int slot, int day) {
        this->id = id;                     // 'this' pointer
        this->name = name;
        this->room = room;
        this->slot = slot;
        this->day = day;
        total++;
    }

    void show() const {
        cout << "ID " << id << " | " << name << " | Room " << room
             << " | Slot " << slot << " | Day " << day << endl;
    }

    static int getTotal() { return total; }
    friend bool clash(const Booking& b, int room, int slot, int day);
};
int Booking::total = 0;

// friend function: is this room + slot + day already booked?
bool clash(const Booking& b, int room, int slot, int day) {
    return b.room == room && b.slot == slot && b.day == day;
}

// pointer function: returns address of booking, or nullptr
Booking* findById(Booking list[], int count, int id) {
    for (int i = 0; i < count; i++)
        if (list[i].getId() == id) return &list[i];
    return nullptr;
}

int main() {
    Booking list[50];                      // array of objects
    int count = 0, choice;

    do {
        cout << "\n1.Add  2.View all  3.Search  0.Exit : ";
        cin >> choice;

        if (choice == 1) {
            int id, room, slot, day;
            string name;
            cout << "ID: ";           cin >> id;
            cout << "Name: ";         cin >> name;
            cout << "Room (1-5): ";   cin >> room;
            cout << "Slot (1-6): ";   cin >> slot;
            cout << "Day (1-31): ";   cin >> day;

            bool ok = true;
            if (count == 50)                           { cout << "List full.\n"; ok = false; }
            else if (id <= 0 || findById(list, count, id)) { cout << "Bad or duplicate ID.\n"; ok = false; }
            else if (room < 1 || room > 5 || slot < 1 || slot > 6 || day < 1 || day > 31)
                                                       { cout << "Invalid room/slot/day.\n"; ok = false; }
            else for (int i = 0; i < count; i++)
                if (clash(list[i], room, slot, day))   { cout << "Room already booked.\n"; ok = false; }

            if (ok) {
                list[count].setData(id, name, room, slot, day);
                count++;
                cout << "Booking added.\n";
            }
        }
        else if (choice == 2) {
            for (int i = 0; i < count; i++) list[i].show();
            cout << "Total bookings: " << Booking::getTotal() << endl;
        }
        else if (choice == 3) {
            int id;
            cout << "ID to search: ";  cin >> id;
            Booking* p = findById(list, count, id);
            if (p != nullptr) p->show();
            else cout << "Not found.\n";
        }
    } while (choice != 0);

    return 0;
}