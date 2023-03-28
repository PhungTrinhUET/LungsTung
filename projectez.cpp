#include<iostream>
using namespace std;
int main ()
{
    int quant;
    int choice;
    //Quantity 
    int Qrooms=0 , Qpastas=0, Qburgers =0, Qnoodles =0, Qshakes=0, Qchickens=0;
    //Food items sold
    int Srooms=0, Spastas=0, Sburgers=0, Snoodles=0, Sshakes=0, Schickens=0;
    //Total proce of items
    int Total_rooms=0, Total_pasta=0, Total_burger=0, Total_noodles=0, Total_shake=0, Total_chicken=0;



    cout << "\n\t Quantity of items we have";
    cout << "Rooms avaliabe : ";
    cin >> Qrooms;
    cout << "\n Quantity of pasta : ";
    cin >> Qpastas;
    cout <<"\n Quantity of burger : ";
    cin >> Qburgers;
    cout <<"\n Quantity of noodles : ";
    cin >> Qnoodles;
    cout << "\n Quantity of shake : ";
    cin >> Qshakes;
    cout <<"\n Quantity of chicken : ";
    cin >> Qchickens;
    m : 
    cout << "\n\t\t\t Please select from the menu options ";
    cout << "\n\n1) Rooms ";
    cout <<"\n2) Pasta";
    cout <<"\n3) Burger";
    cout <<"\n4) Noodles";
    cout <<"\n5) shake";
    cout <<"\n6 chicken ";
    cout <<"\n7) Information regarding sales and collection  ";
    cout <<"\n8) Exit ";
    
    cout <<"\n Please Enter your choice ! ";
    cin >> choice;
    switch (choice)
    {
        case 1 :
        cout << "\n\n Enter the number of rooms you want : ";
        cin >>quant;
        if ( Qrooms-Srooms >=quant)
        {
            Srooms = Srooms + quant;
            Total_rooms = Total_rooms + quant*1200;
            cout << "\n\n\t\t" << quant << "room\rooms have been allooted to you !";

        }
        else 
        {
            cout <<"\n\t Only" << Qrooms - Srooms << "Rooms remaining in hotel";
            break;
        }
        case 2 :
        cout << "\n\n Enter Passta Quantity : ";
        cin >>quant;
        if ( Qpastas - Spastas >=quant)
        {
            Spastas = Spastas + quant;
            Total_pasta = Total_pasta + quant*250;
            cout << "\n\n\t\t" << quant << "Pasta is oder!";

        }
        else 
        {
            cout <<"\n\t Only" << Qpastas - Spastas << "Pasta remaining in hotel";
            break;
        }
        case 3 :
        cout << "\n\n Enter burger Quantity : ";
        cin >>quant;
        if ( Qburgers - Sburgers >=quant)
        {
            Sburgers = Sburgers + quant;
            Total_burger = Total_burger + quant*150;
            cout << "\n\n\t\t" << quant << " Burger is oder!";

        }
        else 
        {
            cout <<"\n\t Only" << Qburgers - Sburgers << "Burger remaining in hotel";
            break;
        }
        case 4 :
        cout << "\n\n Enter Noodles Quantity : ";
        cin >>quant;
        if ( Qnoodles - Snoodles >=quant)
        {
            Snoodles = Snoodles + quant;
            Total_noodles = Total_noodles + quant*350;
            cout << "\n\n\t\t" << quant << "Noodles is oder!";

        }
        else 
        {
            cout <<"\n\t Only" << Qnoodles - Snoodles << "Noodles remaining in hotel";
            break;
        }
        case 5 :
        cout << "\n\n Enter Shakes Quantity : ";
        cin >>quant;
        if ( Qshakes - Sshakes >=quant)
        {
            Sshakes = Sshakes + quant;
            Total_shake = Total_shake + quant*500;
            cout << "\n\n\t\t" << quant << "Shakes is oder!";

        }
        else 
        {
            cout <<"\n\t Only" << Qshakes - Sshakes << "Shakes remaining in hotel";
            break;
        }
        case 6 :
        cout << "\n\n Enter Chicken Quantity : ";
        cin >>quant;
        if ( Qchickens - Schickens >=quant)
        {
            Schickens = Schickens + quant;
            Total_chicken = Total_chicken + quant*400;
            cout << "\n\n\t\t" << quant << "Chicken is oder!";

        }
        else 
        {
            cout <<"\n\t Only" << Qchickens - Schickens << "Chicken remaining in hotel";
            break;
        }
        case 7 :
        cout << "\n\t\t Details of sales and collection";
        cout << "\n\n Number of rooms we had : " << Qrooms;
        cout << "\n\n Number of rooms we gave for rent " << Srooms;
        cout << "\n\n Remaining rooms : "<<Qrooms - Srooms;
        cout << "\n\n Total rooms collection for the day :" << Total_rooms;

        cout << "\n\n Number of Pastas we had : " << Qpastas;
        cout << "\n\n Number of Pasta we gave for rent " << Spastas;
        cout << "\n\n Remaining pasta :" << Qpastas - Spastas;
        cout << "\n\n Total rooms collection for the day : " <<Total_pasta;

        cout << "\n\n Number of Burger we had : " << Qburgers;
        cout << "\n\n Number of Burger we gave for rent " << Sburgers;
        cout << "\n\n Remaining Burger : " << Qburgers - Sburgers;
        cout << "\n\n Total buger collection for the day : " << Total_burger;

        cout << "\n\n Number of shake we had :" << Qshakes;
        cout << "\n\n Number of shake we gave for rent " << Qshakes;
        cout << "\n\n Remaining shake : " << Qshakes - Sshakes;
        cout << "\n\n Total shake collection for the day : " << Total_shake;

        cout << "\n\n Number of chicken we had : " << Qchickens;
        cout << "\n\n Number of chicken we gave for rent " << Qchickens;
        cout << "\n\n Remaining chicken : ";
        cout << "\n\n Total chicken collection for the day :" << Total_chicken; 
        case 8 :
        exit (0);
        default : 
        cout << "\n Please select the numbers mentioned aboved!";
    }
    goto m;
}