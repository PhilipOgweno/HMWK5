/*
 * Homework 5 Program, Station Channels
 * Goal: Understand how to declare and manipulate a collections of objects
 * using a arrays, enumerators, and structures
 * Author: Luke Philip Ogweno
 * 3 March 2015
 * Github account: https://github.com/PhilipOgweno/HMWK5.git
 */

//External Libraries
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h> 
#include <fstream>
#include <iomanip>
#include <ctype.h>

using namespace std;
// Using enum to declare months 

enum month 
                {
                        January =1, 
                        February, 
		        March, 
		        April, 
		        May, 
		        June, 
		        July, 
                        August, 
		        September, 
		        October, 
		        November, 
		        December
                };

string Band_Type [ 3 ] = {"Long-Period", "Short-Period", "Broadband"};
string Inst_Type [ 3 ] = {"High-Gain", "Low-Gain", "Accelerometer"};

string uppercase (string s) 
{
    string answer = s;
    for (int i=0; i < (int)answer.size(); i++)
        answer[i] = toupper(answer[i]);
    return answer;
}


// Returns TRUE if variable is a boolean, FALSE otherwise

bool IsNetwork_code(string Network_code)
{
    if (Network_code.compare ("CI")          == 0) return true;
    else if (Network_code.compare ("CE") == 0) return true;
    else if (Network_code.compare ("FA") == 0) return true;
    else if (Network_code.compare ("NP") == 0) return true;
    else if (Network_code.compare ("WR") == 0) return true;
    else return false;
}

bool IsStation (string Stn_Code)
{
     
    bool Correct_Stn = false;
    if (Stn_Code.length() == 3 || Stn_Code.length() == 5) 
    {
         if (Stn_Code.length() == 3) 
	{
            for (int i =0; i< 3; i++)
	    {
                if (isalpha(Stn_Code [i]) && isupper (Stn_Code [i])) Correct_Stn = true;
                else return false;
            }
        }
        else if (Stn_Code.length() == 5) 
	{
            for (int i =0; i< 5; i++)
	    {
                if (isdigit (Stn_Code [i])) Correct_Stn = true;
                else return false;
            }
        }
    }
    else return false;
    return Correct_Stn;
}


bool IsBand_Type (string Band_Name)
{
    bool band = false;
    for (int i = 0; i < 3; i++)
    {

        if (uppercase(Band_Type [i]) == uppercase (Band_Name)) 
	{
            band = true;
            return true;
        }

    }
    return band;
}

bool IsInst_Type (string Inst_Name)
{

    bool isint = false;
    for (int i = 0; i < 3; i++)
    {

        if (uppercase(Inst_Type [i]) == uppercase (Inst_Name)) 
	{
            isint = true;
            return true;
        }
    }
    return isint;
}
bool IsOrient_Type (string Orient_Name)
{
    bool isAlphabetic  = false;
    bool isNumeric     = false;
    string orientation    = "ENZ123";
     
    for (int unsigned i = 0 ; i < Orient_Name.length(); i++)
    {
        if (Orient_Name[i]          == orientation[0]) isAlphabetic = true;
        else if (Orient_Name [i] == orientation[1]) isAlphabetic = true;
        else if (Orient_Name [i] == orientation[2]) isAlphabetic = true;
        else if (Orient_Name [i] == orientation[3]) isNumeric    = true;
        else if (Orient_Name [i] == orientation[4]) isNumeric    = true;
        else if (Orient_Name [i] == orientation[5]) isNumeric    = true;
        else return false;
    }

    if ((isAlphabetic) && (isNumeric)) return false;
    else return true;

}
// Function to open input file and checks its validity
void open_input (ifstream& inFile, string inFileName) 
{
    inFile.open (inFileName.c_str ());

    if (inFile.fail ()) 
    {
        cout << "Error reading the file  " << inFileName << endl;
        exit (EXIT_FAILURE);
    }
}

// Function to write the headers to an output file
void Write_header (int Record_Number, string EQID, string date, string time1,
                  string timeZone, string EQKNAME, string lat, string lon, 
                  string magType, string magnitude, string Event_No) 
{
    ofstream outFile;
    string outFileName = "philip.out" ;
    if (Record_Number == 0)
       outFile.open (outFileName.c_str ()); 
    else
       outFile.open (outFileName.c_str (), ofstream::out | ofstream::app);

    outFile << date << " " << time1 << " " << timeZone << " " << magType << "  "
               << magnitude << " " << EQKNAME << " [" <<EQID << "] " << endl;

    outFile << "(" << lat <<" , " <<lon << " " << Event_No << ")" << endl;
}
// Function to write the output to file
void write_to_file(int Record_Number, string Network_code, string Stn_Code, 
                string Inst_Name, string Band_Name, string Orient_Name) 
{
    ofstream outFile;
    string outFileName = "philip.out" ;
    if (Record_Number > 0)
       outFile.open(outFileName.c_str(), ofstream::out | ofstream::app);
    else
       outFile.open(outFileName.c_str()); 

    for (int unsigned i = 0 ; i < Orient_Name.length(); i++)
    {
       outFile << Network_code << "."   << Stn_Code << "." << uppercase(Band_Name)
                  << uppercase(Inst_Name) << Orient_Name[i]   << endl;

    }
}

// Function to write to logfile
// void print_file ( string, ofstream & LogFile );

void write_to_LogFile (int Record_Number, int Valid_Record, int Invalid_Record, int Total_Signal, 
                bool a, bool b, bool c, bool d, bool e)
{
    ofstream LogFile;
    string outFileName = "Logfile" ;
    if (Record_Number > 0)
       LogFile.open (outFileName.c_str (), ofstream::out | ofstream::app);
    else
       LogFile.open (outFileName.c_str ()); 
       LogFile <<  "Opening file: input.in \n" << "Processing input ...\n"<<  "Header read correctly!\n"<< endl;     
    if (a == false) 
       
    {
        LogFile << "Entry # " << Record_Number << " Invalid Network" << endl;
        cout << "Entry # " << Record_Number << " Invalid Network" << endl;
    }
    else if (b == false) 
    {
        LogFile << "Entry # " << Record_Number << " Invalid Station" << endl;
        cout << "Entry # " << Record_Number << " Invalid Station" << endl;
    }
    else if (c == false) 
    {
        LogFile << "Entry # " << Record_Number << " Invalid Band type" << endl;
        cout << "Entry # " << Record_Number << " Invalid Band type" << endl;
    }
    else if (d == false) 
    {
        LogFile << "Entry # " << Record_Number << " Invalid Instrument" << endl;
        cout << "Entry # " << Record_Number << " Invalid Instrument" << endl;
    }
    else if (e == false) 
    {
        LogFile << "Entry # " << Record_Number << " Invalid Orientation" << endl;
        cout << "Entry # " << Record_Number << " Invalid Orientation" << endl;
    }
       
}

// Creating Data Structure

struct header
{

    string EQID;
    string date;
    string time;
    string timeZone;
    string EQKNAME;
    string lat;
    string lon;
    string magType;
    string magnitude;
    string Event_No;
};
// Main program starts here

int main () 
{
    int Record_Number = 0;
    string line, message;
    
    // Reading input from the infile 
    
    string inFileName;
    cout << "Enter Input File  : The input.in "<< endl;
    cin >> inFileName ;
    cout << "Opening Input File  : The input.in "<< endl;
    
    ifstream inFile;
    open_input(inFile, inFileName);
    
    header head;
    getline(inFile, line);
    stringstream HEADER1 (line);
    HEADER1 >> head.EQID;
        
    getline(inFile, line);
    stringstream HEADER2 (line);
    HEADER2 >> head.date;
    HEADER2 >> head.time;
    HEADER2 >> head.timeZone;

    //string date_time = CheckDateTime(head.date, head.time, head.timeZone);

    getline(inFile, line);
    head.EQKNAME = line;

    getline(inFile, line);
    stringstream HEADER4 (line);
    HEADER4 >> head.lat;
    HEADER4 >> head.lon;
    HEADER4 >> head.Event_No;
    HEADER4 >> head.magType;
    HEADER4 >> head.magnitude;
    
    Write_header (Record_Number, head.EQID, head.date, head.time,
                head.timeZone, head.EQKNAME, head.lat, head.lon, 
                head.magType, head.magnitude, head.Event_No);


    cout << "Processing input ...." <<endl;
    cout << "Header read correctly! "<< endl;
    string Network_code;
    string Stn_Code;
    string Band_Name;
    string Inst_Name;
    string Orient_Name;
    
    bool a, b, c, d, e;
    
    // initializing the 
    
    int Valid_Record = 0;
    int Invalid_Record = 0;
    int Total_Signal = 0;
    
    Record_Number = 1;
    while (!inFile.eof()) 
    {
        getline(inFile, line);
        istringstream number (line);
        number >> Network_code;
        number >> Stn_Code;
        number >> Band_Name;
        number >> Inst_Name;
        number >> Orient_Name;

        if (IsNetwork_code (Network_code)) 
	{
            Network_code = uppercase (Network_code);
            a = true;
        }
        else a = false;

        if (IsStation (Stn_Code)) 
	{
            Stn_Code = uppercase(Stn_Code);
            b = true;
        }
        else b = false;

        if (IsBand_Type (Band_Name)) 
	{
            Band_Name = Band_Name[0];
            c = true;
        }
        else c = false;

        if (IsInst_Type (Inst_Name)) 
	{
            Inst_Name = Inst_Name [0];
            d = true;
        }
        else d = false;

        if (IsOrient_Type (Orient_Name)) 
	{
            Orient_Name = uppercase (Orient_Name);
            e = true;
        }
        else e = false;
        
        if ((a) && (b) && (c) && (d) && (e)) 
	{
           write_to_file (Record_Number, Network_code, Stn_Code, Inst_Name, Band_Name, Orient_Name);
           Valid_Record ++;
           Total_Signal += Orient_Name.length ();
        }
        else {
            write_to_LogFile (Record_Number, Valid_Record, Invalid_Record, Total_Signal, 
            a, b, c, d, e);
            Invalid_Record ++;
        }

        Record_Number++;
    }
    
    ofstream LogFile;
    string outFileName = "Logfile" ;
    LogFile.open (outFileName.c_str (), ofstream::out | ofstream::app);

    LogFile << "Valid Records = "   << Valid_Record   << endl;
    LogFile << "Invalid Records = " << Invalid_Record << endl;
    LogFile << "Total Signals = "    << Total_Signal     << endl;

    cout << "Valid Records = "       << Valid_Record   << endl;
    cout << "Invalid Records = "     << Invalid_Record << endl;
    cout << "Total Signals = "         << Total_Signal    << endl;

}
