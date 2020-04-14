#include<bits/stdc++.h>
#include<user.h>
#include<meeting.h>
using namespace std;

vector<user> users;
vector<meeting> meetings;

int searchForName(int ID)
{
    for(int i = 0; i < users.size(); i++)
    {
        if(users[i].getID() == ID)
        {
            return i;
        }
    }
    return -1;
}
int main()
{
    int num = 0, countmeeting = 0;
    string garp="";
    char symbol;
    cout<<"========== Welcome in FCAI Meetings Manager =========="<<endl;
    cout<<"Please Enter total number of users:"<<endl;
    cin>>num;
    getline(cin,garp);
    cout<<endl;
    for(int i = 0; i < num; i++)
    {
        user User;
        User.addUse();
        users.push_back(User);
    }
    while(true)
    {
        cout<<"========== FCAI Meetings Manager Main Menu =========="<<endl;
        cout<<"[1] Display users"<<endl;
        cout<<"[2] Create meeting"<<endl;
        cout<<"[3] Leave meeting"<<endl;
        cout<<"[4] Display all Meetings"<<endl;
        cout<<"[5] Exit"<<endl;
        cout<<"Enter your choice:"<<endl;
        cin>>num;
        getline(cin,garp);
        cout<<endl;
        if(num==1)
        {
            cout<<"FCAI have "<<users.size()<<" Users:"<<endl<<endl;
            for(int i = 0; i < users.size(); i++)
            {
                users[i].displayInfo();
            }
            while(true)
            {
                cout<<"Press [b] if you want to go back to the main menu"<<endl;
                cout<<"Press [e] if you want to end the program"<<endl;
                cin>>symbol;
                getline(cin,garp);
                if(tolower(symbol)=='b')
                    break;
                else if(tolower(symbol)=='e')
                    return 0;
                cout<<"Wrong Input"<<endl;
            }
            cout<<endl;
        }
        else if(num==2)
        {
            meeting Meeting;
            string input;
            int ID,index;
            cout<<"Enter Meeting Title:"<<endl;
            getline(cin,input);
            Meeting.setTitle(input);
            cout<<"Enter Meeting Description:"<<endl;
            getline(cin,input);
            Meeting.setDescription(input);
            cout<<"Enter Meeting Time:"<<endl;
            getline(cin,input);
            Meeting.setTime(input);
            cout<<"Enter Host (Teacher) ID:"<<endl;
            cin>>num;
            getline(cin,garp);
            index = searchForName(num);
            if(index == -1 || users[index].getRole() != "teacher")
            {
                cout<<"Wrong Teacher ID"<<endl;
                continue;
            }
            Meeting.setTeacherID(num);
            Meeting.setTeacherName(users[index].getName());
            cout<<endl;
            cout<<"Enter Number of Student in the meeting:"<<endl;
            cin>>num;
            getline(cin,garp);
            cout<<"Enter Students IDs:"<<endl;
            for(int i = 0; i < num; i++)
            {
                cin>>ID;
                getline(cin,garp);
                index = searchForName(ID);
                if(index != -1 && users[index].getRole() == "student")
                {
                    Meeting.addStudent(ID,users[index].getName());
                }
                cout<<endl;
            }
            if(Meeting.sizeOfStudent() < 1)
            {
                cout<<"The Meeting Creation Process Failed Because You Do Not Enter a Valid Student ID"<<endl;
                continue;
            }
            cout<<"Meeting with id = "<<Meeting.getID()<<" Created Successfully!"<<endl;
            countmeeting++;
            meetings.push_back(Meeting);
            cout<<endl;
            while(true)
            {
                cout<<"Press [b] if you want to go back to the main menu"<<endl;
                cout<<"Press [e] if you want to end the program"<<endl;
                cin>>symbol;
                getline(cin,garp);
                if(tolower(symbol)=='b')
                    break;
                else if(tolower(symbol)=='e')
                    return 0;
                cout<<"Wrong Input"<<endl;
            }
            cout<<endl;
        }
        else if(num==3)
        {
            int flag = 0,index;
            cout<<"Enter Meeting Id:"<<endl;
            cin>>num;
            getline(cin,garp);
            for(index = 0; index < countmeeting; index++)
            {
                if(meetings[index].getID() == num)
                {
                    flag = 1;
                    break;
                }
            }
            if(flag == 0)
            {
                cout<<"Incorrect Meeting ID"<<endl;
                continue;
            }
            cout<<"Enter User Id:"<<endl;
            cin>>num;
            getline(cin,garp);
            int idIndex = meetings[index].searchForID(num);
            if(num == meetings[index].getTeacherID())
            {
                cout<<"Teacher Left Meeting and Meeting removed successfully!"<<endl;
                countmeeting--;
                meetings[index].setDelete(1);
                meetings[index].removeTeacher();
            }
            else if(-1 != idIndex)
            {
                meetings[index].removeStudent(idIndex);
                if(meetings[index].sizeOfStudent() == 0)
                {
                    cout<<"Student Left Meeting and Meeting removed successfully! (No Students In The Meeting)"<<endl;
                    countmeeting--;
                    meetings[index].setDelete(1);
                    continue;
                }
                cout<<"Student Left Meeting successfully!"<<endl;
            }
            else
            {
                cout<<"You Did Not Enter This Meeting"<<endl;
            }
        }
        else if(num==4)
        {
            cout<<"FCAI have "<<countmeeting<<" meetings:"<<endl<<endl;
            for(int i = 0; i < countmeeting; i++)
            {
                if(!meetings[i].isDeleted())
                {
                    meetings[i].displayInfo();
                }
            }
            while(true)
            {
                cout<<"Press [b] if you want to go back to the main menu"<<endl;
                cout<<"Press [e] if you want to end the program"<<endl;
                cout<<"Press [d] if you want to delete a meeting"<<endl;
                cin>>symbol;
                getline(cin,garp);
                if(tolower(symbol)=='b')
                    break;
                else if(tolower(symbol)=='e')
                    return 0;
                else if(tolower(symbol)=='d')
                {
                    cout<<"Enter Meeting Id:"<<endl;
                    cin>>num;
                    getline(cin,garp);
                    int flag = 0;
                    for(int i = 0; i < countmeeting; i++)
                    {
                        if(meetings[i].getID() == num)
                        {
                            cout<<"Meeting with id = "<<num<<" Deleted successfully!"<<endl;
                            meetings[i].setDelete(1);
                            countmeeting--;
                            flag = 1;
                            break;
                        }
                    }
                    if(flag == 0)
                    {
                        cout<<"There Is No Meeting With ID = "<<num<<endl;
                    }
                    break;
                }
                cout<<"Wrong Input"<<endl;
            }
            cout<<endl;
        }
        else if(num==5)
        {
            break;
        }
        else
        {
            cout<<"Wrong Input"<<endl;
        }
    }
    return 0;
}

