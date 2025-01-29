#include <iostream>
/* A crucial standard library is iostreams, which enables reading from files and the keyboard, 
   as well as writing to files and the display. */

using namespace std; // All Standard C++ libraries are enclosed within the std namespace (short for "standard").

int main() {
    long long int No_of_users;
    int Transactions_perday, Principal_amount, Time_period, Interest_rates, Revenue, Account_number;
    char Name[50], type_of_bank[20], Branches[20], Headquarters[30], IFSC_code[10];

    cout << "Enter the no of users: "; 
    /* The cout object belongs to the output stream class, 
       used to send data to output devices like the screen or disk. */
    
    cin >> No_of_users; 
    /* The cin object belongs to the input stream class, 
       used to read input from devices like the keyboard (also known as the extraction or input operator). */
    
    cout << "The Total Number of Users are: " << No_of_users << endl; 
    /* The cout object is part of the output stream class, 
       allowing data to be displayed on output devices like the screen. */

    cout << "Enter the Account Number: "; 
    /* The cout object is used to display prompts or messages on output devices like the screen. */
    
    cin >> No_of_users; 
    /* The cin object reads input from the user via input devices like the keyboard. */
    
    cout << "The Account Number of the user is: " << No_of_users << endl; 
    /* The cout object is used to print values and messages to the output screen. */

    cout << "Enter the IFSC code: "; 
    /* The cout object displays messages or prompts on the screen to guide user input. */
    
    cin >> IFSC_code; 
    /* The cin object reads user-provided input from the keyboard or other input devices. */
    
    cout << "The IFSC code is: " << IFSC_code << endl; 
    /* The cout object prints the entered IFSC code on the output screen. */
}
