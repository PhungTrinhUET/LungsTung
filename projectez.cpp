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
        if ( Qchckens - Schickens >=quant)
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
        

    
    }
    
    
}