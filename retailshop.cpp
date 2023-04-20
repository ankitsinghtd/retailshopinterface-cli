#include<iostream>
#include<fstream>
using namespace std;
class shopping{
    private:
        int pcode;
        float price;
        float dis;
        string pname;
    public:
        void menu();
        void administrator();
        void buyer();
        void add();
        void edit();
        void rem();
        void list();
        void receipt();
};

void shopping::menu(){
    m:
    int choice;
    string email;
    string password;

    cout<<"\t\t\t_______________________\n";
    cout<<"\t\t\t                       \n";
    cout<<"\t\t\t  Retail Shop Main Menu  \n";
    cout<<"\t\t\t_______________________\n";
    cout<<"\t\t\t                       \n";

    cout<<"\t\t\t 1> Administrator   \n";
    cout<<"\t\t\t                    \n";
    cout<<"\t\t\t 2> Buyer           \n";
    cout<<"\t\t\t                    \n";
    cout<<"\t\t\t 3> Exit            \n";
    cout<<"\t\t\t Please select an option :";
    cin>>choice;
    switch(choice){
        case 1:
            cout<<"\n\t\t\t Enter your login credentials : ";
            cout<<"\n\t\t\t Email :";
            cin>>email;
            cout<<"\n\t\t\t Password :";
            cin>>password;

            if(email=="admin" && password=="admin"){
                administrator();
            }
            else{
                cout<<"Invalid email or password, please check the credentials !";
            }
            break;

        case 2:
            buyer();
            break;

        case 3:
            exit(0);

        default:
            cout<<"Please select the right option !";
    }
    goto m;
}

void shopping::administrator(){
    m:
    int choice;
    cout<<"\n\t\t\t !! Administrator Menu !!";
    cout<<"\n\t\t\t ************************";
    cout<<"\n\t\t\t 1. Add a new product";
    cout<<"\n\t\t\t                      ";
    cout<<"\n\t\t\t 2. Update a product";
    cout<<"\n\t\t\t                      ";
    cout<<"\n\t\t\t 3. Delete a product";
    cout<<"\n\t\t\t                      ";
    cout<<"\n\t\t\t 4. Go back to main menu";

    cout<<"\n\n\t\t\tEnter your choice :";
    cin>>choice;

    switch(choice){
        case 1:
            add();
            break;
        
        case 2:
            edit();
            break;

        case 3:
            rem();
            break;

        case 4:
            menu();
            break;

        default:
            cout<<"invalid choice";
    }
    goto m;
}

void shopping::buyer(){
    m:
    int choice;
    cout<<"\n\n\t\t\t Welcome to Online Retailers :)";
    cout<<"\t\t\t                        ";
    cout<<"\n\t\t\t 1. Buy something ?";
    cout<<"\t\t\t                        ";
    cout<<"\n\t\t\t 2. Go back ?";
    cout<<"\t\t\t                        ";
    cout<<"\n\t\t\t Enter a choice :";

    cin>>choice;

    switch(choice){
        case 1:
            receipt();
            break;

        case 2:
            menu();
            break;

        default:
            cout<<"\nInvalid choice !";

    }
    goto m;
}

void shopping::add(){
    m:
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout<<"\n\n\t\t\t ! Add New Product !";
    cout<<"\n\n\t\t\t *******************";
    cout<<"\n\n\t\t\t Enter product code :";
    cin>>pcode;
    cout<<"\n\n\t\t\t Enter name of the product :";
    cin>>pname;
    cout<<"\n\n\t\t\t Enter the price of the product :";
    cin>>price;
    cout<<"\n\n\t\t\t Enter discount on the product :";
    cin>>dis; 

    data.open("database.txt",ios::in);
    if(!data){
        data.open("database.txt",ios::app|ios::out);
        data<<" \t\t\t"<<pcode<<"\t\t\t "<<pname<<" \t\t\t"<<price<<"\t\t\t "<<dis<<"\n";
        data.close();
    }
    else{
        data>>c>>n>>p>>d;

        while(!data.eof()){
            if(c==pcode){
                token++;
            }
            data>>c>>n>>p>>d;
        }
        data.close();
    

        if(token == 1){
            cout<<"\n\n\t\t\tProduct already exists !";
            goto m;
        }
        else{
            data.open("database.txt",ios::app|ios::out);
            data<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<"\n";
            data.close();
        }
    }
    cout<<"\n\t\t\tNew product successfully added !";
}

void shopping::edit(){
    fstream data, data1;
    int pkey;
    int token;
    int c;
    float p;
    float d;
    string n;

    cout<<"\n\n\t\t\t ! Modify a product !";
    cout<<"\n\n\t\t\t ***************************";
    cout<<"\n\n\t\t\t Enter product code to modify";

    data.open("database.txt",ios::in);
    if(!data){
        cout<<"\nFile doesn't exist !";
    }
    else{
        data1.open("database1.txt",ios::app|ios::out);
        data>>pcode>>pname>>price>>dis;

        while(!data.eof()){
            if(pkey==pcode){
                cout<<"\n\n\t\t\t Enter new product code :";
                cin>>c;
                cout<<"\n\n\t\t\t Enter new name for product :";
                cin>>n;
                cout<<"\n\n\t\t\t Enter new price of product :";
                cin>>p;
                cout<<"\n\n\t\t\t Enter new discount on product :";
                cin>>d;

                data1<<" "<<c<<" "<<n<<" "<<p<<" "<<d<<"\n";
                cout<<"\n\n\t\t\t Product updated !";
                token++;
            }
            else{
                data1<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<"\n";
            }
            data>>pcode>>pname>>price>>dis;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if(token==0){
            cout<<"\n\n\t\t\t Product not found !";
        }
    }
}

void shopping::rem(){
    fstream data, data1;
    int pkey;
    int token=0;
    cout<<"\n\n\t\t\t ! Delete Product !";
    cout<<"\n\n\t\t\t ******************";
    cout<<"\n\n\t\t\t Enter product code to delete :";
    cin>>pkey;

    data.open("database.txt", ios::in);
    if(!data){
        cout<<"File doesn't exist !";
    }
    else{
        data1.open("database1.txt",ios::app|ios::out);
        data>>pcode>>pname>>price>>dis;

        while(!data.eof()){
            if(pcode==pkey){
                cout<<"\n\n\t\t\t Product deleted successfully !";
                token++;
            }
            else{
                data1<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<"\n";
            }
            data>>pcode>>pname>>price>>dis;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt","database.txt");

        if(token==0){
            cout<<"Product not found !";
        }
    }
}

void shopping::list(){
    fstream data;
    data.open("database.txt",ios::in);
    cout<<"\n\n\t\t\t";
    cout<<"Product No\t\tName\t\tPrice\n";
    cout<<"\n\n\t\t\t";
    data>>pcode>>pname>>price>>dis;

    while(!data.eof()){
        cout<<pcode<<"\t\t"<<pname<<"\t\t"<<price<<"\n";
        data>>pcode>>pname>>price>>dis;
    }
    data.close();
}

void shopping::receipt(){
    m:
    fstream data;
    int arrcode[100];
    int arrquantity[100];
    char choice;
    int count=0;
    float amount =0;
    float dis=0;
    float total=0;

    cout<<"\n\n\t\t\t Available Products";
    data.open("database.txt",ios::in);
    if(!data){
        cout<<"\n\n\t\t\tSorry,  we have no products to offer !";
    }
    else{
        data.close();
        list();
        cout<<"\n\n\t\t\t****************";
        cout<<"\n\n\t\t\t Place the order";
        cout<<"\n\n\t\t\t****************";

        do{
            cout<<"\n\t\t\tEnter the product code to purchase :";
            cin>>arrcode[count];
            cout<<"\n\t\t\tEnter the quantity :";
            cin>>arrquantity[count];

            for(int i=0;i<count;i++){
                if(arrcode[count]==arrcode[i]){
                    cout<<"\n\n\t\t Product already in cart !";
                    goto m;
                }
            }
            count++;
            cout<<"\n\n\t\t\t Do you wish to buy another product y/n?";
            cin>>choice;
        }while(choice == 'y');

        cout<<"\n\n\t\t\t __________RECEIPT__________";
        cout<<"\nProduct No\tProduct Name\tQuantity\tPrice\tAmount\tAmount with discount\n";

        for(int i = 0; i<count;i++){
            data.open("database.txt",ios::in);
            data>>pcode>>pname>>price>>dis;
            while(!data.eof()){
                if(pcode == arrcode[i]){
                    amount = price * arrquantity[i];
                    dis = amount - (amount * dis/100);
                    total += dis;
                    cout<<"\n"<<pcode<<"\t"<<pname<<"\t"<<arrquantity[i]<<"\t"<<price<<"\t"<<amount<<"\t"<<dis;
                }
                data>>pcode>>pname>>price>>dis;
            }
        }
        data.close();
    }
    cout<<"\n\n\t\t\t************************************";
    cout<<"\n\t\t\tAmount to be Paid :"<<total;
}

int main(){
    shopping s;
    s.menu();
}