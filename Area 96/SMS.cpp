#include "SMS.h"

/// Other function

// Gia Bao
int to_int(const string s)
{
    int res=0;
    short i;
    for(i=0;i<s.size();i++) res=res*10+s[i]-48;
    return res;
}

// Gia Bao
double to_double(const string s)
{
    double res=0;
    short i;
    for(i=0;i<s.size();i++)
    if (s[i]!='.') res=res*10+s[i]-48;
    else break;
    if (i<s.size())
    {
        int tmp=1;
        for(i=i+1;i<s.size();i++)
        {
            tmp*=10;
            res+=double(s[i]-48)/tmp;
        }
    }
    return res;
}

// Mai Trinh
int Check_in_date(Date d, Course c) {
    Date s = c.start_at, e = c.end_at;
    if (s.y < d.y && d.y < e.y) {
        return 1;
    }
    else if (s.y == d.y) {
        if (s.m < d.m) return 1;
        else if (s.m == d.m) {
            if (s.d <= d.d) return 1;
            else return 0;
        }
        else return 0;
    }
    else if (e.y == d.y) {
        if (e.m > d.m) return 1;
        else if (e.m == d.m) {
            if (e.d >= d.d) return 1;
            else return 0;
        }
        else return 0;
    }
    return 0;
}

// Mai Trinh
int Check_in_time(Time t, Course c) {
    Time s = c.from, e = c.to;
    if (s.h < t.h && t.h < e.h) {
        return 1;
    }
    else if (s.h == t.h) {
        if (s.m < t.m) return 1;
        else if (s.m == t.m) {
            if (s.s <= t.s) return 1;
            else return 0;
        }
        else return 0;
    }
    else if (e.h == t.h) {
        if (e.m > t.m) return 1;
        else if (e.m == t.m) {
            if (e.s >= t.s) return 1;
            else return 0;
        }
        else return 0;
    }
    return 0;
}

// Mai Trinh
void Take_time(Date &d, Time &t, string &wday) {
    time_t tme;
    time(&tme);
    tm *cur;
    cur = localtime(&tme);
    string S = asctime(cur);
    string s;
    _Next_token(S,s);
    switch (s[2]) {
        case 'n':
            if (s[1] == 'u') wday = "Sunday";
            else wday = "Monday";
            break;
        case 'e':
            wday = "Tuesday";
            break;
        case 'd':
            wday = "Wednesday";
            break;
        case 'u':
            wday = "Thursday";
            break;
        case 'i':
            wday = "Friday";
            break;
        case 't':
            wday = "Saturday";
    }
    _Next_token(S,s);
    switch (s[2]) {
        case 'r':
            if (s[1] == 'a') d.m = 3;
            else d.m = 4;
            break;
        case 'n':
            if (s[1] == 'a') d.m = 1;
            else d.m = 6;
            break;
        case 'b':
            d.m = 2;
            break;
        case 'y':
            d.m = 5;
            break;
        case 'l':
            d.m = 7;
            break;
        case 'g':
            d.m = 8;
            break;
        case 'p':
            d.m = 9;
            break;
        case 't':
            d.m = 10;
            break;
        case 'v':
            d.m = 11;
            break;
        case 'c':
            d.m = 12;
            break;
    }
    _Next_token(S,s);
    d.d = (int(s[0])-48)*10 + s[1] - 48;
    _Next_token(S,s);
    t.h = (int(s[0])-48)*10 + s[1] - 48;
    t.m = (int(s[3])-48)*10 + s[4] - 48;
    t.s = (int(s[6])-48)*10 + s[7] - 48;
    _Next_token(S,s);
    d.y = 0;
    S.erase(S.length()-1,S.length()-1);
    for (string::iterator i=S.begin();i!=S.end();++i)
        d.y = d.y*10 + int(char(*i)) - 48;
}

// Import courses - Cong Duc
void Student_management_service::Import_course() {
    Course_list a;
    cout << "Enter number of course\n";
    int number;
    cin >> number;
    for (;number;number--) 
        a.Add_a_course();
    CSV_helper Helper;
    Helper.Write_file(a,"course.txt");
}

// Import course from file - Cong Duc
void Student_management_service::Import_course_from_file() {
    cout << "Enter file name (name.csv)\n";
    string s;
    cin >> s;
    ifstream fin(s.c_str());
    Course_list a;
    a.Input_line_by_line(fin);
    fin.close();
    CSV_helper Helper;
    Helper.Write_file(a,"course.txt");
}

//Import student list - Cong Duc
void Student_management_service::Import_student_list() {
    Student_list a;
    cout << "Enter number of student\n";
    int number;
    cin >> number;
    for (;number;number--) 
        a.Add_student_to_last();
    CSV_helper Helper;
    Helper.Write_file(a,"user.txt");
}



//Import schedules

//Import scores - Cong Duc
void Student_management_service::Import_score() { 
    Score_list a;
    int number;
    cout << "Enter number of score\n";
    cin >> number;
    for (;number;number--)
        a.Add_score_to_last();
    CSV_helper Helper;
    Helper.Write_file(a,"score.txt");
}

// View list of course - Mai Trinh
void Student_management_service::View_list_of_course() {
    string S, s;
    Course c;
    Course_list a;
    filebuf fb;
    fb.open ("course.txt",ios::in);
    istream fin(&fb);
    while (getline(fin,S)) {
        _Next__token(S,s);
        c.course_code = s;
        _Next__token(S,s);
        c.year = s;
        _Next__token(S,s);
        c.semester = int(s[0])-48;
        _Next__token(S,s);
        c.course_name = s;
        _Next__token(S,s);
        c.lecturer_name = s;
        _Next__token(S,s);
        Date_process(s,c.start_at);
        _Next__token(S,s);
        Date_process(s,c.end_at);
        _Next__token(S,s);
        Time_process(s,c.from);
        _Next__token(S,s);
        Time_process(s,c.to);
        c.date_of_week = S;
        a.Add_tail(c);
    }
    a.Print_list(cout);
    fb.close();
}

//Get score of student - Gia Bao
void Student_management_service::Export_scores_of_student(const string username,ostream &fout)
{
    ifstream f;
    f.open("score.txt");
    string s;
    int i,j;
    Score_list _list;
    Score tmp;
    while (getline(f,s))
    {
        i=s.find(',',s.find(',',s.find(',')+1)+1)+1;
        j=s.find(',',i);
        if (s.substr(i,j-i)==username)
        {
            i=s.find(',',++j);
            tmp.midterm=to_double(s.substr(j,i-j)); //Midterm
            j=s.find(',',++i);
            tmp.lab=to_double(s.substr(i,j-i)); //Lab
            i=s.find(',',++j);
            tmp._final=to_double(s.substr(j,i-j)); //Final
            i=s.find(',');
            tmp.course_code=s.substr(0,i); //Course code
            tmp.student_id=username; //Student ID
            j=s.find(',',++i);
            tmp.year=to_int(s.substr(i,j-i)); //Year
            i=s.find(',',++j);
            tmp.semester=to_int(s.substr(j,i-j)); //Semester
            _list.Add_to_last(tmp);
        }
    }
    f.close();
    // Print
    fout << "Score of student " << username << endl;
    _list.Print_list(fout);
}

//Get score of course - Gia Bao
void Student_management_service::Export_scores_of_course(const string course_id,ostream &fout)
{
    ifstream f;
    f.open("score.txt");
    string s;
    int i,j;
    Score_list _list;
    Score tmp;
    while (getline(f,s))
    {
        i=s.find(',');
        if (s.substr(0,i)==course_id)
        {
            tmp.course_code=course_id; //Course code
            j=s.find(',',++i);
            tmp.year=to_int(s.substr(i,j-i)); //Year
            i=s.find(',',++j);
            tmp.semester=to_int(s.substr(j,i-j)); //Semester
            j=s.find(',',++i);
            tmp.student_id=s.substr(i,j-i); //Student ID
            i=s.find(',',++j);
            tmp.midterm=to_double(s.substr(j,i-j)); //Midterm
            j=s.find(',',++i);
            tmp.lab=to_double(s.substr(i,j-i)); //Lab
            i=s.find(',',++j);
            tmp._final=to_double(s.substr(j,i-j)); //Final
            _list.Add_to_last(tmp);
        }
    }
    f.close();
    // Print
    fout << "Score of course: " << course_id << endl;
    _list.Print_list(fout);
}


//Get list of student who was present - Van Nam
void Student_management_service::Print_present (string course_code,ostream &fout)
{
    fout << "   List of student who was present in class " << course_code << endl;
    Student_list list;
    CSV_helper helper;
    
    string line, tmp, week= "1", tmp_week, student_id, tmp_course;
    string number_of_week = "10";
    User guy;
    int swi= 0;
    
    ifstream presence;
    presence.open ("presence.txt");
    
    fout << "Week 1: " << endl << "Attending students: " << endl;
    while (!presence.eof())
    {
        if (swi== 0)
            // swi== 0 means Next_token took in the last data of the line (week data)
            // So we read the next line
            presence >> line;
        swi= Next_token (line, tmp_course);
        if (tmp_course.compare (course_code)== 0)
        {
            swi= Next_token (line, tmp);
            swi= Next_token (line, tmp);
            swi= Next_token (line, student_id);
            swi= Next_token (line, tmp_week);
            if (week== tmp_week)
            {
                // Add the student to the present list and remove them from the asbent list
                if (helper.Get_details("user.txt",student_id,guy))
                {
                    list.Add_to_last (guy);
                }
            }
            else
            {
                // Moving to the next week:
                // Print out the lists of present and absent students
                list.Print_list (fout);
                // Reset the lists
                list.Make_empty ();
                // Handle the empty weeks (if there are some)
                Plus_one_week (week);
                while (tmp_week!= week)
                {
                    fout << endl << "Week " << week << ": " << endl
                    << "No student attending the class." << endl;
                    Plus_one_week (week);
                }
                // Add the first student of the week to the present list
                // and remove them from the absent list
                if (helper.Get_details("user.txt",student_id,guy))
                {
                    list.Add_to_last (guy);
                }
                // Print out the title for the next week
                fout << endl << "Week " << tmp_week << ": " << endl
                << "Attending students: " << endl;
                week= tmp_week;
            }
        }
        else
        {
            swi= Next_token (line, tmp);
            swi= Next_token (line, tmp);
            swi= Next_token (line, tmp);
            swi= Next_token (line, tmp_week);
            if (tmp_week!= week)
            {
                // Moving to the next week
                // Print out the lists
                list.Print_list (fout);
                // And reset them
                list.Make_empty ();
                // Handle the empty weeks (if there are some)
                Plus_one_week (week);
                while (tmp_week!= week)
                {
                    fout << endl << "Week " << week << ": " << endl
                    << "No student attending the class." << endl;
                    Plus_one_week (week);
                }
                // Print out the title for the next week
                fout << endl << "Week " << tmp_week << ": " << endl
                << "Attending students: " << endl;
                week = tmp_week;
            }
        }
    }
    // The last week in the file presence.txt
    // Print out the lists
    list.Print_list (fout);
    // Remove the lists
    list.Make_empty ();
    // Handle the last empty weeks
    while (week!= number_of_week)
    {
        Plus_one_week (week);
        fout << endl << "Week " << week << ": " << endl
        << "No students attending the class." << endl;
    }
}

//Get list of student who was absent - Van Nam
void Student_management_service::Print_absent(string course_code,ostream &fout) {
    fout << "   List of student absent in class " << course_code << endl;
    Student_list absent;
    absent.List_all_student ();
    CSV_helper helper;
    
    string line, tmp, week= "1", tmp_week, student_id, tmp_course;
    string number_of_week = "10";
    User guy;
    int swi= 0;
    
    ifstream presence;
    presence.open ("presence.txt");
    
    fout << "Week 1: " << endl;
    while (!presence.eof())
    {
        if (swi== 0)
            // swi== 0 means Next_token took in the last data of the line (week data)
            // So we read the next line
            presence >> line;
        swi= Next_token (line, tmp_course);
        if (tmp_course.compare (course_code)== 0)
        {
            swi= Next_token (line, tmp);
            swi= Next_token (line, tmp);
            swi= Next_token (line, student_id);
            swi= Next_token (line, tmp_week);
            if (week== tmp_week)
            {
                // Add the student to the present list and remove them from the asbent list
                if (helper.Get_details("user.txt",student_id,guy))
                {
                    absent.Delete_node (student_id);
                }
            }
            else
            {
                // Moving to the next week:
                // Print out the lists of present and absent students
                fout << endl << "Absent students: " << endl;
                absent.Print_list (fout);
                // Reset the lists
                absent.Make_empty ();
                absent.List_all_student ();
                // Handle the empty weeks (if there are some)
                Plus_one_week (week);
                while (tmp_week!= week)
                {
                    fout << endl << "Week " << week << ": " << endl
                    << "No student attending the class." << endl
                    << "Absent students: " << endl;
                    absent.Print_list (fout);
                    Plus_one_week (week);
                }
                // Add the first student of the week to the present list
                // and remove them from the absent list
                if (helper.Get_details("user.txt",student_id,guy))
                {
                    absent.Delete_node (student_id);
                }
                // Print out the title for the next week
                fout << endl << "Week " << tmp_week << ": " << endl;
                week= tmp_week;
            }
        }
        else
        {
            swi= Next_token (line, tmp);
            swi= Next_token (line, tmp);
            swi= Next_token (line, tmp);
            swi= Next_token (line, tmp_week);
            if (tmp_week!= week)
            {
                // Moving to the next week
                // Print out the lists
                fout << endl << "Absent students: " << endl;
                absent.Print_list (fout);
                // And reset them
                absent.Make_empty ();
                absent.List_all_student ();
                // Handle the empty weeks (if there are some)
                Plus_one_week (week);
                while (tmp_week!= week)
                {
                    fout << endl << "Week " << week << ": " << endl
                    << "No student attending the class." << endl
                    << "Absent students: " << endl;
                    absent.Print_list (fout);
                    Plus_one_week (week);
                }
                // Print out the title for the next week
                week= tmp_week;
            }
        }
    }
    // The last week in the file presence.txt
    // Print out the lists
    fout << endl << "Absent students: " << endl;
    absent.Print_list (fout);
    // Handle the last empty weeks
    absent.Make_empty();
    absent.List_all_student ();
    while (week!= number_of_week)
    {
        Plus_one_week (week);
        fout << endl << "Week " << week << ": " << endl
        << "No students attending the class." << endl
        << "Absent students: " << endl;
        absent.Print_list (fout);
    }
}


//Check-in class
int Student_management_service::Check_in(string username,string course_code,string year,int semester)
{
    CSV_helper csv;
    Course c;
    string file_name = "course.txt";
    if (csv.Get_details(file_name,course_code,year,semester,c)) {
        Date d;
        Time t;
        string wday;
        Take_time(d,t,wday);
        if (wday != c.date_of_week) return 0;
        if (!(Check_in_time(t,c))) return 0;
        if (!(Check_in_date(d,c))) return 0;
        return 1;
    }
    return 0;
}
