#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>


using namespace std;

struct Node
{
    string id;
    string name;
    string age;
    string salary;
   struct Node* next;
};

typedef struct Node Node;

class LinkedList{
           
            Node* first;
            Node* last;
            int totalNodes;


    public: LinkedList();
            bool isEmpty();
            Node* createNode(string,string,string,string);
            void addNode(string,string,string,string);
            void updateNode(string);
            void deleteNode(string);
            void display();
};

LinkedList :: LinkedList(){
    first = NULL;
    last = NULL;
    totalNodes = 0;
}

bool LinkedList :: isEmpty(){
    if(totalNodes == 0){
        return true;
    }else{
        return false;
    }
}

Node* LinkedList :: createNode(string id,string name,string age,string salary){
    Node* newNode = new Node;
    newNode -> id = id;
    newNode -> name = name;
    newNode -> age = age;
    newNode -> salary = salary;
    newNode -> next = NULL;
    return newNode;
}

void LinkedList :: addNode(string id, string name, string age, string salary){
    Node* newNode = createNode(id,name,age,salary);
    if(isEmpty()){
        first = newNode;
        last = newNode;
    }else
    {
        last -> next = newNode;
        last = newNode;
    }
    totalNodes++;
}

void LinkedList :: updateNode(string id){
    if(isEmpty()){
        cout<<"No data to delete"<<endl;
        return;
    }
    cout<<"enter the data to update"<<endl;
    string name;
    string age;
    string salary;
    cout<<endl;
    cout<<"Enter new/old employee name\t";
    cin>>name;
    cout<<endl;
    cout<<"Enter new/old employee age\t";
    cin>>age;
    cout<<endl;
    cout<<"Enter new/old employee salary\t";
    cin>>salary;
    cout<<endl;

    Node* temp = first;
    Node* prev;
    Node* newNode = createNode(id,name,age,salary);
    while(temp -> id != id){
        prev = temp;
        temp = temp -> next;
    }
    prev -> next = newNode;
    newNode -> next = temp -> next;
    delete temp;
    ofstream MyFile("EmployeeData.txt");

    Node* updatetemp = first;
    string line;
    while(updatetemp -> next != NULL){
        line = updatetemp -> id +"\t"+updatetemp -> name+"\t"+updatetemp -> age+"\t"+updatetemp -> salary+"\n";
        MyFile << line;
        updatetemp = updatetemp -> next;
    }
    line = updatetemp -> id +"\t"+updatetemp -> name+"\t"+updatetemp -> age+"\t"+updatetemp -> salary+"\n";
    MyFile << line;
    MyFile.close();
}

void LinkedList :: deleteNode(string id){
    if(isEmpty()){
        cout<<"No data to delete"<<endl;
        return;
    }

    Node* temp = first;
    Node* prev;
    if(temp -> id == id){
        prev = temp;
        temp = temp -> next;
        first = temp;
        delete prev;
    }else{
        while(temp -> id != id){
            prev = temp;
            temp = temp -> next;
        }
        prev -> next = temp -> next;
        delete temp;
    }
    totalNodes --;
    ofstream MyFile("EmployeeData.txt");

    Node* deletetemp = first;
    string line;
    while(deletetemp -> next != NULL){
        line = deletetemp -> id +"\t"+deletetemp -> name+"\t"+deletetemp -> age+"\t"+deletetemp -> salary+"\n";
        MyFile << line;
        deletetemp = deletetemp -> next;
    }
    line = deletetemp -> id +"\t"+deletetemp -> name+"\t"+deletetemp -> age+"\t"+deletetemp -> salary+"\n";
    MyFile << line;
    MyFile.close();
    
}

void LinkedList :: display(){
    if(isEmpty()){
        cout<<"No data to display"<<endl;
        return;
    }
    Node* temp = first;
    for(int i = 0; i < totalNodes; i++){
        cout<<temp -> id<<"\t"<<temp -> name<<"\t"<<temp->age<<"\t"<<temp->salary<<endl;
        temp = temp -> next;
    }

}

int main()
{
    LinkedList ll;
    int choice;
    
    ifstream file;
    string filename, word;
    filename = "EmployeeData.txt";
    file.open(filename);

    while (getline(file, word))
    {
        istringstream ss(word);
        string substr;
        int count = 1;
        vector<string> vect;
        while(getline(ss, substr, '\t'))
        {
            if(count < 5){
                count++;
                vect.push_back(substr);
            }            
        }
        ll.addNode(vect[0],vect[1],vect[2],vect[3]);
        count = 1;
        vect.clear();
    }
    while(true){
        cout<<"Enter your choice"<<endl;
        cout<<"----------------------------------------------------"<<endl;
        cout<<"Enter 1 to display the list of employees"<<endl;
        cout<<"Enter 2 to update an employee from the list"<<endl;
        cout<<"Enter 3 to delete an employee from the list"<<endl;
        cout<<"Enter 4 to exit the application"<<endl;
        cout<<"----------------------------------------------------"<<endl;
        cout<<endl;
        cin >> choice;
        cout<<endl;
        
        switch (choice)
        {
        case 1: 
        {       cout<<endl;
                cout<<"----------------------------------------------------"<<endl;
                ll.display();             
                cout<<"----------------------------------------------------"<<endl;
                file.close();
        }
        break;

        case 2: 
        {       
                cout<<"Enter employee id to update"<<endl;
                string id;
                cin >> id;
                cout<<endl;
                ll.updateNode(id);
                cout<<endl;
                cout<<"updated list"<<endl;
                cout<<endl;
                cout<<"----------------------------------------------------"<<endl;
                ll.display();
                cout<<"----------------------------------------------------"<<endl;

        }
        break;

        case 3:
        {
                cout<<"enter the employee id to delete data from list"<<endl;
                string id;
                cin >> id;
                ll.deleteNode(id);
                cout<<"updated list"<<endl;
                cout<<endl;
                cout<<"----------------------------------------------------"<<endl;
                ll.display();
                cout<<"----------------------------------------------------"<<endl;

        }
        break;

        case 4: cout<<"Exiting the application"<<endl;
                _Exit(0);

        default: cout<<"Invalid input"<<endl;
        break;
        }
    }
}