#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Student
{  
    string phone_no;
    string Branch;
    int year;
protected:
    string name;
    
    int roll_no;
    int merit_rank;

public:
    void input();
    void display();
    void storeAllottedStudent(int, string);
};

void Student::input()
{ cin.ignore();

    cout << "Enter your name:" << endl;
    getline(cin, name);
    cout << "Enter your rank:" << endl;
    cin >> merit_rank;
    cout << "Enter your roll no:" << endl;
    cin >> roll_no;
    cout << "Enter your phone no:" << endl;
    cin >> phone_no;
    cout << "Enter year you study in:" << endl;
    cin >> year;
    cout << "Enter your branch:" << endl;
    cin >> Branch;
}  

void Student::display()
{
    cout << "Name:" << name << endl;
    cout << "Roll no:" << roll_no << endl;
    cout << "Rank:" << merit_rank << endl;
    cout << "Phone no:" << phone_no << endl;
    cout << "Year:" << year << endl;
    cout << "Branch:" << Branch << endl;
}

void Student::storeAllottedStudent(int room_no, string bed)
{
    ofstream fout("Allotted.txt", ios::app);

    fout << name << "            "
         << merit_rank << "   "
         << room_no << "      "
         << bed << endl;

    fout.close();
}

class Room : public Student
{
protected:
    int No_of_available_beds;
    int Room_no;
    // string student1, student2;

public:
    Room()
    {
        No_of_available_beds = 0;
        Room_no = 0;
    }
    void count_available_beds();
    void display_available_rooms();
    void display_room_info();
    bool checkEligibility();
    void generateWaitingList();
   
    void assignRoom();
};

void Room::count_available_beds()
{
    string s1;
    ifstream in("roominfo.txt");
    while (in.eof() == 0)
    {
        in >> s1;
        if (stoi(s1) == 0)
        {
            No_of_available_beds++;
        }
    }
    in.close();
}

void Room::display_available_rooms()
{
    string s1, s2, s3;
    cout << "No of available beds are:" << No_of_available_beds << endl;
    ifstream in("roominfo.txt");
    cout << "Available rooms are:" << endl;
    for (int i = 0; i < 100; i++)
    {
        in >> s1;
        in >> s2;
        in >> s3;
        if (stoi(s2) == 0 || stoi(s3) == 0)
        {
            cout << s1 << endl;
        }
    }
    in.close();
}

bool Room::checkEligibility()
{
    string s1;
    string s2;
    int count = 0;
    ifstream in("waitinglist.txt");
    while (in >> s1 >> s2 && count < No_of_available_beds)
    {
        if (stoi(s2) > merit_rank)
        {
            cout << "Eligible\n";
            return true;
        }
        count++;
    }
    cout << " not eligible\n";
    return false;
}

void Room::generateWaitingList()
{
    ofstream fout("temp.txt");
    ifstream fin("waitinglist.txt");
    string s1;
    string s2;
    bool inserted = false;
    while (fin >> s1 >> s2)
    {
        if (stoi(s2) > merit_rank && !inserted)
        {
            fout << roll_no << "    " << merit_rank << endl;
            inserted = true;
        }
        fout << s1 << "    " << s2 << endl;
    }
    if (!inserted)
    {
        fout << roll_no << "    " << merit_rank << endl;
    }
    fout.close();
    fin.close();
    cout<<"added to waiting list\n";
    remove("waitinglist.txt");
    rename("temp.txt", "waitinglist.txt");
}

void Room::assignRoom()
{

    ifstream fin("roominfo.txt");
    ofstream temp("temp.txt");

    int r, bed1, bed2;
    bool allotted = false;

    while (fin >> r >> bed1 >> bed2)
    {
        if (!allotted && bed1 == 0)
        {
            Room_no = r;
            bed1 = 1;
            allotted = true;

            cout << "Room Allotted: "
                 << Room_no
                 << " Bed 1\n";
            storeAllottedStudent(Room_no, "Bed 1");
        }

        else if (!allotted && bed2 == 0)
        {
            Room_no = r;
            bed2 = 1;
            allotted = true;

            cout << "\nRoom Allotted: "
                 << Room_no
                 << " Bed 2\n";
            storeAllottedStudent(Room_no, "Bed 2");
        }

        temp << r << "  "
             << bed1 << "  " << bed2 << endl;
    }

    fin.close();
    temp.close();
    

    remove("roominfo.txt");
    rename("temp.txt", "roominfo.txt");
}

class Fee : public Student
{
private:
    float messFee = 0;
    float canteenFee = 0;

public:
    void input()
    {
        
       cout << "Enter your roll no:" << endl;
       cin >> roll_no;
       cout << "Enter your Mess fee" << endl;
       cin >> year;
       cout << "Enter your Canteen fee:" << endl;
       cin >> Branch;
    }
    void calcfee()
    {
        ifstream fin("mess.txt");
        string s1;
        string s2;
        string s3;
        while (fin >> s1 >> s2 >> s3)
        {
            if (stoi(s1) == roll_no)
            {
                messFee = stof(s2);
                canteenFee = stof(s3);

                break;
            }
        }
    }

    void showData()
    {
        cout << "Roll No: " << roll_no << endl;
        cout << "Mess Fee: " << messFee << endl;
        cout << "Canteen Fee: " << canteenFee << endl;
        cout << "Total Fee: " << messFee + canteenFee << endl;
        cout << endl
             << endl;
    }

    void writeFile()
    {
        ofstream fout("mess.txt", ios::app);
        fout << endl;
        fout << roll_no << " " << messFee << " " << canteenFee << endl;
        fout.close();
    }

    void readFile()
    {
        ifstream fin("mess.txt");
        int r;
        float m, c;

        while (fin >> r >> m >> c)
        {
            cout << "Roll No: " << r << endl;
            cout << "Mess Fee: " << m << endl;
            cout << "Canteen Fee: " << c << endl;
            cout << "Total Fee: " << m + c << endl;
            cout << endl
                 << endl;
        }

        fin.close();
    }
};

int main()
{

    
    int x;
    Room a;
    Fee f;
    cout<<"Enter 1 for updating student data\n Enter 2 for checking room availability\n Enter 3 for checking eligibiloty and room assigning\n Enter 4 for mess fee details:\n";
    cin>>x;
    switch(x)
    {
        case 1 :  a.input();
                  a.display();
                  break;

        case 2 : a.count_available_beds();
                a.display_available_rooms();
                break;

        case 3: a.input();
                a.count_available_beds();
                if (a.checkEligibility())
                   a.assignRoom();
                else {a.generateWaitingList();}
                break;
       
       case 4: f.calcfee();
       f.showData();
       break;

       default : cout<<"invalid input\n";

    }

    return 0;
}