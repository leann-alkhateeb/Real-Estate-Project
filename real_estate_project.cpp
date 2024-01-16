#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include <string.h>
#include <iomanip>
#include <math.h>

using namespace std;

class Calender
{
   private:
      int month;
      char cal[31];
   
   public:
      Calender(int month)
      {
         this->month = month;
         for(int i =0;i<31;i++){
            cal[i] = '*';
            }
            }
            string getCalendar(){
               string str = "";
               int count = 0;
               for(int i = 0;i<31;i++){
                  count++;
                  if(i < 30){
                     str = str + cal[i] +" ";
                     }
                     else{
                        str = str + cal[i];
                        }
                        if(count == 7){
                           str = str + "\n";
                           count = 0;
                           }
                           }
                           str = str + "\n\n";
                           return str;
                           }

void displayCalender(){
   int count = 0;
   for(int i = 0;i<31;i++){
      count++;
      if(i < 30){
         cout<<cal[i]<<" ";
         }
         else{
            cout<<cal[i];
            }
            if(count == 7){
               cout<<endl;
               count = 0;
               }
               }
               cout<<endl;
   }

void addBooking(int day){
   char event  = 'B';
   if(day  == 1 || day == 8 || day == 15 || day == 22 || day == 29){
      event = 'D';
      }
      if(day  == 7 || day == 14 || day == 21 || day == 28){
         event = 'D';
         }
         cal[day -1] = event;
         }
         bool ifBooked(){
            for(int i =0;i<31;i++){
               if(cal[i] != '*'){
                  return true;
                  }
                  }
                  return false;
                  }
double getAmount(double rate){
   double amount = 0;
   for(int i =0;i<31;i++){
      if(cal[i] == 'D'){
         amount = amount + 2*rate;
         }
         if(cal[i] == 'B'){
            amount = amount + rate;
            }
            }
            return amount;
            }
            
int getMonth(){
   return month;
   }
   
bool checkIFBooked(int start_day, int end_day){
   for(int i =start_day-1;i<end_day;i++){
      if (cal[i] != '*'){
         return true;
         }
         }
         return false;
         }


string getMonthName(){
   if(month == 1){
      return "January";
      }
      else if(month == 2){
         return "February";
         }
         else if(month == 3){
            return "March";
            }
            else if(month == 4){
               return "April";
               }
               else if(month == 5){
                  return "May";
                  }
                  else if(month == 6){
                     return "June";
                     }
                     else if(month == 7){
                        return "July";
                        }
                        else if(month == 8){
                           return "August";
                           }
                           else if(month == 9){
                              return "September";
                              }
                              else if(month == 10){
                                 return "October";
                                 }
                                 else if(month == 11){
                                    return "November";
                                    }
                                    else{
                                       return "December";
                                       }
                                       }

};

class BookingDate{
   private:
      int start_day;
      int start_month;
      int end_month;
      int end_day;

   public:
      BookingDate(int start_day, int start_month, int end_month, int end_day){
         this->start_day = start_day;
         this->start_month = start_month;
         this->end_day = end_day;
         this->end_month = end_month;
         }    

int getStartMonth(){
   return start_month;
   }


};

class Booking{
   private:
      string address;
      double rate;
      int number_bookings;
      vector<BookingDate> bookings;
      vector<Calender> calender;

   public:
      Booking(string address, int number_bookings, double rate){
         this->address = address;
         this->number_bookings = number_bookings;
         this->rate = rate;
         for(int i =1; i<=12; i++){
            Calender cal(i);
            calender.push_back(cal);
            }
            }

void addBooking(int start_day, int start_month, int end_month, int end_day){
   BookingDate book_date(start_day, start_month, end_month, end_day);
   addEventInCalender(start_month, start_day, end_day);
   bookings.push_back(book_date);
   }

void addEventInCalender(int month, int start_day, int end_day){                                
   for(int i = 0; i<calender.size();i++){
      if(calender.at(i).getMonth() == month){
         for(int j =start_day;j<=end_day;j++){
            calender.at(i).addBooking(j);
            }
            }
            }
            }

bool checkMonth(int month){
   for(int i =0;i<calender.size();i++){
      if(calender.at(i).getMonth() == month){
         return true;
         }
         }
         return false;
         }

string getMoneyTwoDecimal(double amount){
   stringstream obj;
   string str;
   obj << fixed <<setprecision(2) <<amount;
   str = obj.str();
   return str;
   }

string getMonthInformation(){
   string str = "";
   double amount = 0.00;
   for(int i =0;i<calender.size();i++){
      if(calender.at(i).ifBooked()){
         str = str + calender.at(i).getMonthName() +": " + getMoneyTwoDecimal(calender.at(i).getAmount(rate)) +"\n";
         str = str + calender.at(i).getCalendar();
         amount = amount + calender.at(i).getAmount(rate);
         }
         }
         str = str + "Total: $"+getMoneyTwoDecimal(amount)+"\n";
         return str;
         }

string getAddress(){
   return address;
   }

void printMonth(int month){
   for(int i =0;i<calender.size();i++){
      if(calender.at(i).getMonth() == month){
         calender.at(i).displayCalender();
         }
         }
         cout<<endl;
         }

bool doBooking(int start_day, int start_month, int end_day, int end_month){
   int end = end_day;
   if(start_month != end_month){
      end = 31;
      }
      for(int i =0;i<calender.size();i++){
         if(calender.at(i).getMonth() == start_month){
            if(!calender.at(i).checkIFBooked(start_day, end)){
               for(int k =start_day ;k<=end_day; k++){
                  calender.at(i).addBooking(k);
                  }
                  return true;
                  }
                  else{
                     return false;
                     }
                     }
                     }
                     return false;
                     }

     

string getFiledata(){
   string str = "Address: "+address +"\n";
   str = str + getMonthInformation();
   return str;
   }

};

void displaySubMenu(){
   cout<<"Enter an option:"<<endl;
   cout<<"1. Show the calendar of the property on a given month"<<endl;
   cout<<"2. Book a period of time for a given property"<<endl;
   cout<<"q. Quit"<<endl;
}

void run(vector<Booking> &booking_list, int index){
   string choice;
   while(true){
      displaySubMenu();
      cin >> choice;
      if(choice == "1"){
         int month;
         cout<<"Enter the month number:"<<endl;
         cin >> month;
         if(month >=1 && month <= 12 ){
            booking_list.at(index).printMonth(month);
            }
            else{
               cout<<"Invalid month number"<<endl;
               }
               }
               else if (choice == "2"){
                  int start_day, start_month;
                  int end_day, end_month;
                  cout<<"Enter the start month and day:"<<endl;
                  cin >> start_month >> start_day;
                  cout<<"Enter the end month and day:"<<endl;
                  cin >> end_month >> end_day;
                  if(start_month < 1 || start_month > 12 || end_month < 1|| end_month > 12){
                     cout<<"Invalid month number"<<endl;
                     }
                     else if(start_day < 1 || start_day > 31 || end_day < 1 || end_day > 31){
                        cout<<"Invalid day number"<<endl;
                        }
                        else{
                           bool booked = booking_list.at(index).doBooking(start_day, start_month, end_day, end_month);
                           if(booked){
                              cout<<"Booked!"<<endl;
                              }
                              else{
                                 cout<<"Date range has dates that are already booked!"<<endl;
                                 }
                                 }
                                 }
                                 else if(choice == "q"){
                                    return;
                                    }
                                    else{
                                       cout<<"Invalid option"<<endl;
                                       }
                                       }
                                       }

void displayMenu(vector<Booking> &booking_list){
   string input;
   int found;
   while(true){
      found = 0;
      cout<<"Enter the address of the property you want to book or exit to exit:"<<endl;
      cin.clear();
      getline(cin, input);
      if(input == "exit"){
         break;
         }
         for(int i = 0;i<booking_list.size();i++){
            string address = booking_list.at(i).getAddress();
            address = address.substr(0, address.length()-1);
            if(address == input){
               run(booking_list, i);
               found = 1;
               cin.ignore();
               break;
               }
               }
               if(found == 0){
                  cout<<"Address not found"<<endl;
                  }
                  }
                  }

void writeToFile(vector<Booking> &booking_list){
   ofstream file("yearly.txt");
   for(int i =0;i<booking_list.size(); i++){
      file << booking_list.at(i).getFiledata() <<endl;    
      }
      file.close();
}

int main(){
   ifstream file;
   file.open("properties.txt");
   if(file.is_open()){
      vector<Booking> booking_list;
      string file_data;
      string address;
      double rate;
      int number_bookings;
      int start_day;
      int start_month;
      int end_month;
      int end_day;
      while(true){
         if(file.eof()){
            break;
            }
            file.clear();
            getline(file, file_data);
            address = file_data;
            getline(file, file_data);
            rate = stod(file_data);
            getline(file, file_data);
            number_bookings = stoi(file_data);
            Booking booking(address, number_bookings, rate);
            for(int i = 0;i<number_bookings;i++){
               getline(file, file_data);
               stringstream obj(file_data);
               obj >> start_month >> start_day >> end_month >> end_day;
               booking.addBooking(start_day, start_month, end_month, end_day);
               }
               booking_list.push_back(booking);
               getline(file, file_data);
               }
               file.close();
               displayMenu(booking_list);
               writeToFile(booking_list);
               }
               else{
                  cout<<"Cannot read the file properties.txt"<<endl;
                  }
   return 0;
}