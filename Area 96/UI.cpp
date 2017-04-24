#include "UI.h"
#include "CSVhelper.h"
#include "user.h"

User_interface::User_interface()
{
    type = -1; 
    account_name = "";
}


void User_interface::Program() {
    string username, password;
    while (1) {
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        if (Login(username,password) == 0) continue;
        Menu(role[type]);
    }
}

int User_interface::Login(string username,string password) {
    if (username == "admin" && password == "admin") {
        type = 1;
        account_name = "admin";
        return true;
    }
    if (username == "httu" && password == "admin") {
        type = 1;
        account_name = "httu"; 
        return true;
    }
    User u;
    CSV_helper csv;
    Md5 md5; 
    md5.pass = password;
    password = md5.Process();
    if (csv.Get_details("user.txt",username,u) && u.password==password) {
        account_name = username;
        type = u.type; // gan gia tri cho type tuong ung voi user ma minh tim dc
        return true;
    }
    cout << "Wrong username or password\n";
    return false;
}

void User_interface::Logout() {
    type = -1;
}

void User_interface::Menu(string role) {
    // Role: "student", "staff", "lecturer"
    string s[] = {"Show menu",                                  // 0
        "Logout",                                               // 1
        "Change password",                                      // 2
        // Academic Staff
        "Add a course",                                         // 3
        "Import courses from csv file",                         // 4
        "View list of course in the console screen",            // 5
        "Assign an existing class to a course",                 // 6
        "Add an existing student to a course",                  // 7
        "Import a list of students in a class from a csv file", // 8
        "Show list of students in a class in the console screen",// 9
        "Show list of students in a course in the console screen",// 10
        // Lecturer
        "Export scores of an exam in a course to a csv file",   // 11
        "Show scores of an exam in a course in the console screen", // 12
        "Import scores of an exam in a course from a csv file", // 13
        "Edit a score of a student in an exam",                 // 14
        // Student
        "Check-in ",                                            // 15
        "View my check in history in a course",                 // 16
        "View my score in a course"                             // 17
    };
    Student_management_service Service;
    string file_name;
    int flag;
    int _width = 100;
    ifstream fi;
    ofstream fo;
    if (role == "student") {
        for (int i=0;i<=2;++i)
            cout << setw(10) << i << setw(_width) << s[i] << '\n';
        for (int i=15;i<=17;++i)
            cout << setw(10) << i-12 << setw(_width) << s[i] << '\n';
        while (cin >> flag) 
        switch(flag)
        {
            case 0:
                for (int i=0;i<=2;++i)
                    cout << setw(10) << i << setw(_width) << s[i] << '\n';
                for (int i=15;i<=17;++i)
                    cout << setw(10) << i-12 << setw(_width) << s[i] << '\n';
                break;
            case 1:
                return;
            case 2:
                Change_password();
                break;
            case 3:
                // Checkin
                Check_in();
                break;
            case 4:
                Service.View_checkin_of_course(account_name);
                break;
            case 5:
                Service.View_score_of(account_name);
                break;
            default:
                cout << "Invalid number\n";
        }
    }
    else if (role == "staff") {
        for (int i=0;i<=2;++i)
            cout << setw(10) << i << setw(_width) << s[i] << '\n';
        for (int i=3;i<=10;++i)
            cout << setw(10) << i << setw(_width) << s[i] << '\n';
        while ((cout << "Enter option\n") && (cin >> flag))
        switch(flag)
        {
            case 0:
                for (int i=0;i<=2;++i)
                    cout << setw(10) << i << setw(_width) << s[i] << '\n';
                for (int i=3;i<=10;++i)
                    cout << setw(10) << i << setw(_width) << s[i] << '\n';
                break;
            case 1:
                return;
            case 2:
                Change_password();
                break;
            case 3:
                Service.Import_course();
                break;
            case 4:
                Service.Import_course_from_file(); 
                break;
            case 5:
                Service.View_list_of_course();
                break;
            case 6:
                Service.Assign_one_class();
                break;
            case 7:
                Service.Assign_one_student();
                break;
            case 8:
                Service.Import_class_from_file(); 
                break;
            case 9:
                Service.Show_list_of_student_in_class();
                break;
            case 10:
                Service.Show_list_of_student_in_course();
                break;
            default:
                cout << "Invalid number\n";
        }
    }
    else {
        for (int i=0;i<=2;++i)
            cout << setw(10) << i << setw(_width) << s[i] << '\n';
        for (int i=11;i<=14;++i)
            cout << setw(10) << i-8 << setw(_width) << s[i] << '\n';
        while (cin >> flag) 
        switch(flag)
        {
            case 0:
                for (int i=0;i<=2;++i)
                    cout << setw(10) << i << setw(_width) << s[i] << '\n';
                for (int i=11;i<=14;++i)
                    cout << setw(10) << i-8 << setw(_width) << s[i] << '\n';
                break;
            case 1:
                return;
            case 2:
                Change_password();
                break;
            case 3:
                cout << "Enter csv file\n";
                cin >> file_name;
                fo.open(file_name.c_str());
                Service.Export_score_of_course(fo);
                fo.close();
                break;
            case 4:
                Service.Export_score_of_course(cout);
                break;
            case 5:
                Service.Import_score_from_file();
                break;
            case 6:
                Service.Edit_score();
                break;
            default:
                cout << "Invalid number\n";
        }
    }
}

// Change password - Van Nam
void User_interface::Change_password() {
    string username = account_name, password;
    if (account_name == "admin" || type == 1) {
        cout << "You cant change password rightnow\n";
        return;
    }
    cout << "Enter password (no space)\n";
    cin >> password;
    filebuf fb, fbnew;
    fb.open ("user.txt",ios::in);
    fbnew.open ("user_new.txt",ios::out);
    istream fin(&fb);
    ostream fnew(&fbnew);
    string S, s;
    while (getline(fin,S)) {
        Next_token(S,s);
        fnew << s << ",";
        if (s != username) {
            fnew << S << endl;
            continue;
        }
        Md5 hsh;
        hsh.pass = password;
        Next_token(S,s);
        fnew << s << ",";
        Next_token(S,s);
        fnew << s << ",";
        Next_token(S,s);
        fnew << s << ",";
        Next_token(S,s);
        fnew << s << ",";
        fnew << hsh.Process() << ",";
        Next_token(S,s);
        fnew << S << endl;
    }
    fb.close();
    fbnew.close();
    system("mv user_new.txt user.txt");
    cout << "Password is changed\n";
}

// Check in - Cong Duc

void User_interface::Check_in()
{
    string course_code, year; int semester;
    cout << "Enter course code\n";
    cin >> course_code;
    cout << "Enter acadeic year\n";
    cin >> year;
    cout << "Enter semester\n";
    cin >> semester;
    Student_management_service Service;
    int week = Service.Is_ok_check_in(account_name,course_code,year,semester);
    if (week == 0) cout << "You cant check-in now\n";
    else {
        ofstream fo("presence.txt",ios::app);
        fo << course_code << ',' << year << ',' << semester << ',' << account_name << ',' << week << '\n';
        fo.close();
    }
}
