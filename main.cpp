#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;


//storing the program running state
bool programRunning;

//storing the logged in state
bool userLogged;



//admin information
string adminUsername = "nethra";
string adminPassword = "n123";

//LOGGED IN USER OPERATIONS

void addBook(){
    string bookName, bookAuthor;
    int bookId, quantity, bookPrice;
    cout << "Add a new book to the database" << endl;
    cout << endl;

    cin.ignore();
    cout << "Enter Book Name: ";
    getline(cin, bookName);

    // cin.ignore();
    cout << "Enter Book Author: ";
    getline(cin, bookAuthor);

    cout << "Enter book Price: Rs. ";
    cin >> bookPrice;

    //access the book details text file(storage)
    fstream bookDetailsFile;

    //get the number of books in the storage
    int bookCount = 0;

    bookDetailsFile.open("book details.txt", ios::in);
    if(bookDetailsFile.is_open()){
        string line;

        while (getline(bookDetailsFile, line)) {
            bookCount++;
        }
        bookDetailsFile.close();

    }

    //storing the new book in the books file
    bookDetailsFile.open("book details.txt", ios::app);
    if(bookDetailsFile.is_open()){

        //book details in the book details file contains like "name, author, price"
        bookDetailsFile << bookCount + 1 << "," << bookName << "," << bookAuthor << "," << bookPrice << endl;
        bookDetailsFile.close();
    }

    cout << "The new book Registered Successfully!" << endl;

}

void viewBooks(){
    //retrieve all the books in the storage
    fstream bookDetailsFile;
    bookDetailsFile.open("book details.txt", ios::in);
    if(bookDetailsFile.is_open()){
        string singleBookDetails;
        while (getline(bookDetailsFile, singleBookDetails)){

            istringstream ss(singleBookDetails);
            string token;

            vector<string> bookDetails;

            //book details in the book details file contains like "name, author, price, quantity"
            //split one single line in book details file from commas
            while(getline(ss, token, ',')){
                bookDetails.push_back(token);
            }

            //print all the details of one book
            cout << endl;
            cout << "Book ID: " << bookDetails[0] << endl;
            cout << "Book Name: " << bookDetails[1] << endl;
            cout << "Book Author: " << bookDetails[2] << endl;
            cout << "Book Price: Rs. " << bookDetails[3] << endl;
            cout << endl;
        }
        bookDetailsFile.close();
    }
}

void searchBook(){
    string searchQuery;
    int foundResultsCount = 0; //to print out "no results" if no match was found
    cout << "Search for a book" << endl;
    cout << endl;

    cout << "Enter Book Name to Search: ";
    cin.ignore();
    getline(cin, searchQuery);


    //retrieve all the books in the storage
    fstream bookDetailsFile;
    bookDetailsFile.open("book details.txt", ios::in);
    if(bookDetailsFile.is_open()){
        string singleBookDetails;
        while (getline(bookDetailsFile, singleBookDetails)){

            istringstream ss(singleBookDetails);
            string token;

            vector<string> bookDetails;

            //split one single line in book details file from commas
            while(getline(ss, token, ',')){
                bookDetails.push_back(token);
            }

            // cout << "comparing " << bookDetails[1] << " ---- "<< searchQuery << endl;
            if(bookDetails[1] == searchQuery){
                //searched book exists in the storage
                foundResultsCount++;

                //print all the details of the found book
                cout << endl;
                cout << "Book ID: " << bookDetails[0] << endl;
                cout << "Book Name: " << bookDetails[1] << endl;
                cout << "Book Author: " << bookDetails[2] << endl;
                cout << "Book Price: Rs. " << bookDetails[3] << endl;
                cout << endl;
            }
        }
        bookDetailsFile.close();
    }

    //no match was found
    if(foundResultsCount==0){
        cout << "No Results!" << endl;
    }
}


void manageBooks(){
    bool managingBooks = true;
    char choiceNum;
    while(managingBooks){
        cout << endl;
        cout << "       MANAGE BOOKS "<<endl;
        cout << "-------------------------"<<endl;
        cout << "1. Add a new book" << endl;
        cout << "2. View available books" << endl;
        cout << "3. Search for a book" << endl;
        cout << "4. Go to Main menu" << endl;
        cout << "Enter Your Choice ---> ";
        cin >>choiceNum;
        cout << endl;

        switch(choiceNum){
            case '1': addBook();
            break;

            case '2': viewBooks();
            break;

            case '3': searchBook();
            break;

            case '4': managingBooks = false;
            break;

            default: cout << "Invalid Choice!" << endl;
            break;
        }
    }
}




//ORDER MANAGEMENT
void prepareQs(){
    bool preparingQs = true;
    char choiceNum;
    double discountedPrice;
    string customerName, orderBookName , addDiscountChoice;

    float totalPrice = 0;
    float discountPercentage = 0;

    int ordersCount = 0;

    //find the orders count
    fstream ordersFile;
    ordersFile.open("orders.txt", ios::in);
    if(ordersFile.is_open()){
        string singleOrderDetailsLine;
        while(getline(ordersFile, singleOrderDetailsLine)){
            if(singleOrderDetailsLine == "--------------------"){
                ordersCount++;
            }
        }

        ordersFile.close();
    }


    //get the customer name
    cin.ignore();
    cout << "Customer Name: ";
    getline(cin, customerName);


    while(preparingQs){
        cout << endl;
        cout << "1. Add a book to the quotation" << endl;
        cout << "2. Finalize quotation" << endl;
        cout << "Enter Your Choice ---> ";
        cin >>choiceNum;
        cout << endl;

        if(choiceNum == '1'){
            //add a book to the quotation

            //open orders file
            fstream ordersFile;
            ordersFile.open("orders.txt", ios::app);
            if(ordersFile.is_open()){
                ordersFile << "Order ID: " << ordersCount + 1 << endl;
                ordersFile << "Customer Name: " << customerName << endl;
                cin.ignore();
                cout << "Enter the book name to order: ";
                getline(cin, orderBookName);

                //retrieve all the books in the storage
                fstream bookDetailsFile;
                bookDetailsFile.open("book details.txt", ios::in | ios::out);
                if(bookDetailsFile.is_open()){
                    string singleBookDetails;
                    bool orderBookFound = false;
                    while (getline(bookDetailsFile, singleBookDetails)){

                        istringstream ss(singleBookDetails);
                        string token;

                        vector<string> bookDetails;

                        //split one single line in book details file from commas
                        while(getline(ss, token, ',')){
                            bookDetails.push_back(token);
                        }

                        if(bookDetails[1] == orderBookName){
                            //order book exists in the storage
                            orderBookFound = true;

                                //get the order quantity
                                int orderQuantity;
                                cout << "Order Quantity: ";
                                cin >> orderQuantity;
                                cout << endl;

                                //add ordered book price to the total
                                totalPrice += (stoi(bookDetails[3]) * orderQuantity);
                                //write ordered book details to the orders file
                                ordersFile << "Book Title: " << bookDetails[1] << endl;
                                ordersFile << "Author: " << bookDetails[2] << endl;
                                ordersFile << "Price: Rs. " << bookDetails[3] << endl;
                                ordersFile << "Ordered Quantity: " << orderQuantity << endl;
                                ordersFile << "-------------------------" << endl;
                                cout << endl;
                        }

                    }
                    if(orderBookFound == false){
                        cout << "Invalid Book! Please Try Again." << endl;
                    }

                    bookDetailsFile.close();
                }

                ordersFile.close();
            }

        }else if (choiceNum == '2'){
            //finish adding books

            //open orders file
            fstream ordersFile;
            ordersFile.open("orders.txt", ios::app);
            if(ordersFile.is_open()){
                ordersFile << "Total Price: Rs. " << totalPrice << endl;
                cout << endl;
                cout << "Do you want to add a discount?(y/n): ";
                cin >> addDiscountChoice;

                if(addDiscountChoice == "y"){
                    //add a discount
                    cout << "Discount percentage from total price(%): ";
                    cin >> discountPercentage;
                }
                //add the discount
                discountedPrice = totalPrice - (totalPrice * (discountPercentage * 0.01));

                cout << "Discount: " << discountPercentage << "%" << endl;
                cout << "Discounted Price: Rs. " << discountedPrice << endl;
                cout << endl;

                ordersFile << "Added Discount: " << discountPercentage << endl;
                ordersFile << "Discounted Price: Rs. " << discountedPrice << endl;
                ordersFile << "-------------------------" << endl;
                cout << endl;

                ordersFile.close();
            }
            preparingQs = false;
        } else{
            //invalid choice
            cout << "Invalid Choice!";
        }

    }
}

void viewBookOrders(){
    //retrieve all the book orders in the storage
    fstream bookOrderDetailsFile;
    bookOrderDetailsFile.open("orders.txt", ios::in);
    if(bookOrderDetailsFile.is_open()){
        string singleBookOrderDetails;
        while (getline(bookOrderDetailsFile, singleBookOrderDetails)){

            cout << singleBookOrderDetails << endl;
            cout << endl;
        }
        bookOrderDetailsFile.close();
    }
}

void printQs(){
    string orderId;
    bool gatheringOrderInfo = false;
    vector<string> orderDetails;

    cout << "Enter order Id: ";
    cin >> orderId;

    cout << endl;
    cout << "  -------------  QUOTATION  -------------  " << endl;
    cout << endl;

    fstream bookOrderDetailsFile;
    bookOrderDetailsFile.open("orders.txt", ios::in);
    if(bookOrderDetailsFile.is_open()){
        string singleBookOrderDetails;
        while (getline(bookOrderDetailsFile, singleBookOrderDetails)){
            string checkString = "Order ID: " + orderId;

            if(singleBookOrderDetails == checkString){
                //found the order id that needs to be printed
                gatheringOrderInfo = true;
            } else if (singleBookOrderDetails == "--------------------"){
                gatheringOrderInfo = false;
            }

            if(gatheringOrderInfo == true){
                cout << singleBookOrderDetails << endl;
            }
        }
        bookOrderDetailsFile.close();
    }
}

void manageOrders(){

    bool managingOrders = true;
    char choiceNum;
    while(managingOrders){
        cout << endl;
        cout << "       MANAGE ORDERS" << endl;
        cout << "----------------------------"<<endl;
        cout << endl;
        cout << "1. Prepare Quotations" << endl;
        cout << "2. View Book Orders" << endl;
        cout << "3. Print Quotations" << endl;
        cout << "4. Go to Main Menu" << endl;
        cout << "Enter Your Choice ---> ";
        cin >>choiceNum;
        cout << endl;

        switch(choiceNum){
            case '1': prepareQs();
            break;

            case '2': viewBookOrders();
            break;

            case '3': printQs();
            break;

            case '4': managingOrders = false;
            break;

            default: cout << "Invalid Choice!" << endl;
            break;
        }
    }

}



//success logging handle
void loggedUser(){
    userLogged = true;
    char choiceNum;
    while(userLogged){
        cout << "        MAIN MENU " << endl;
        cout << "--------------------------"<<endl;
        cout << endl;
        cout << "1. Manage Books" << endl;
        cout << "2. Manage Orders" << endl;
        cout << "3. Print quotations with Discount" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter Your Choice ---> ";
        cin >> choiceNum;
        cout << endl;

        switch(choiceNum){
            case '1': manageBooks();
            break;

            case '2': manageOrders();
            break;

            case '3': printQs();
            break;

            case '4': userLogged = false;
            break;

            default:
            cout << "Invalid Choice!" << endl;
            // return;
            break;
        }
    }

}


//LOGGED IN USER OPERATIONS
void loginUser(){
    cout << "\n LOGIN USER" << endl;

    string username,password;
    cout<<" Enter Username: ";
    cin>>username;
    cout<<" Enter Password: ";
    cin>>password;

    if(username == adminUsername && password == adminPassword){
        //entered username and password is correct
        //proceed to login to the system
        cout<<"Login Successful!"<<endl;
        cout<<endl;
        cout<<"Welcome to Nethra Book Shop"<<endl;
        cout<<endl;

        loggedUser();
    }else if(username != adminUsername){
        //entered username is incorrect
        cout << "Username is incorrect!" << endl;
        cout <<endl;
        return;
    }else if(password != adminPassword){
        //entered password is incorrect
        cout << "Password is incorrect!" << endl;
        cout <<endl;
        return;
    }
}


//exit the program
void exitProgram(){
    cout << "Exiting the program..." << endl;
    programRunning = false;
    return;
}

int main() {
    programRunning = true;
    userLogged = false;
    char choiceNum;

    while(programRunning){
        cout<<endl;
        cout<<"   ***   ***  *******  *******  **   **  ******      *** "<<endl;
        cout<<"   ****  ***  ***        ***    **   **  **   **    ** ** "<<endl;
        cout<<"   *** * ***  *******    ***    *******  *****     ******* "<<endl;
        cout<<"   ***  ****  ***        ***    **   **  *****    **     ** "<<endl;
        cout<<"   ***   ***  *******    ***    **   **  **  **  **       ** "<<endl;
        cout<<"                          BOOK SHOP                  "<<endl;
        cout<<endl;
        cout<<endl;
        cout << "1. Admin Login" << endl;
        cout << "2. Exit the program" << endl;
        cout << "Enter Your Choice ---> ";
        cin >> choiceNum;

        switch(choiceNum){
            case '1': loginUser();
            break;

            case '2': exitProgram();
            return 0;
            break;

            default: cout << "Invalid Choice!" << endl;
            break;
        }
    }
    return 0;
}
