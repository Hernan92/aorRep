//Hernan Andrade, Lec #1001, Lab #1008, Assignment #16                                                                                                                                                                 
//This program first reformats the names of each student so they are correct in the capitalization, and in alphabetical order. It then shows their ID numbers and calculates their test scores based on the provided a\
nswer key. From the second input file, it will test to see if any of those numbers from the file match the ID of any of the students. If they do, the program will print their name, ID number, test score, as well as\
 their answers to the test. If the ID does not match any existing ID, the program will send a message saying so.   .                                                                                                    
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;

const int MAX = 35; //max class size                                                                                                                                                                                  \
                                                                                                                                                                                                                       
const int NAMEINTRO = 40; //max width for name                                                                                                                                                                        \
                                                                                                                                                                                                                       
const int ID = 3; //max width for id number                                                                                                                                                                           \
                                                                                                                                                                                                                       
const int SCORE = 10; //max with for score                                                                                                                                                                            \
                                                                                                                                                                                                                       

struct student
{
  int id; //entry id number                                                                                                                                                                                           \
                                                                                                                                                                                                                       
  string fname, lname; //fname and lname name                                                                                                                                                                         \
                                                                                                                                                                                                                       
  string answer; //entry answer                                                                                                                                                                                       \
                                                                                                                                                                                                                       
  int testscore; //testscore points from the test                                                                                                                                                                     \
                                                                                                                                                                                                                       
};

void read(student[], int&, string&);//reads data and store into array                                                                                                                                                  
void formatname(string&); //format the fname and lname name                                                                                                                                                           \
                                                                                                                                                                                                                       
void formatanswer(string&); //format the entry's answer                                                                                                                                                               \
                                                                                                                                                                                                                       
void bubblesortlname(student[], int); //sorts lname name in alphabetical order                                                                                                                                        \
                                                                                                                                                                                                                       
void bubblesortscore(student[], int); //sorts scores in descending order                                                                                                                                               
void print(student[], int, string, double, double); //prints data                                                                                                                                                      
void idcheck(ofstream&, student[], string&, int);
int  score(student[], string, int); //returns entry's score                                                                                                                                                            
double average(student[], int); //finds the ave of the scores                                                                                                                                                          
double fmedian(student[], int); //finds the median of the scores

int main()
{
  string key; //Holds the answer key                                                                                                                                                                                  \
                                                                                                                                                                                                                       
  student entry[MAX]; //array that holds student info                                                                                                                                                                  
  int n; //how many entrys there are                                                                                                                                                                                  \
                                                                                                                                                                                                                       
  double ave = 0.0; //stores the ave                                                                                                                                                                                   
  double median = 0.0;
  read(entry, n, key); //prompt and read in input file                                                                                                                                                                 
  bubblesortlname(entry, n); //sorts lname name in alphabetical order                                                                                                                                                 \
                                                                                                                                                                                                                       
  ave = average(entry, n); //finds the ave                                                                                                                                                                             
  median = fmedian(entry, n);
  print(entry, n, key, ave, median); //prints out to an output file                                                                                                                                                    
  return 0;
}
void read(student entry[], int& n, string& key)
//This function reads and stores the data in an array.                                                                                                                                                                 
{
  string filename; //name of the input file                                                                                                                                                                           \
                                                                                                                                                                                                                       
  ifstream in; //input variable.                                                                                                                                                                                      \
                                                                                                                                                                                                                       
  cout << "Please enter the name of the input file" << endl;
  cin >> filename;
  in.open(filename.c_str());
  n=0;
  in >> key;
  while (in >> entry[n].id)
    {
      in >> entry[n].fname;
      in >> entry[n].lname;
      in >> entry[n].answer;
      entry[n].testscore = 0;
      formatname(entry[n].fname);
      formatname(entry[n].lname);
      formatanswer(entry[n].answer);
      entry[n].testscore = score(entry, key, n);
      n++;
    }
  in.close();
}

void formatname(string& name)
// Properly capitalizes the first and last names.                                                                                                                                                                      
{
  int l = name.length(); //length of the name                                                                                                                                                                         \
                                                                                                                                                                                                                       
  name[0] = toupper(name[0]); //uppercases the fname letter                                                                                                                                                           \
                                                                                                                                                                                                                       
  for(int i = 1; i < name.length(); i ++)
    {
      name[i] = tolower(name[i]);
    }
}

void formatanswer(string& answer)
// Lowercases all student answers.                                                                                                                                                                                     
{
  for(int i = 0; i < answer.length(); i ++)
   {
      answer[i] = tolower(answer[i]);
   }
}
void bubblesortlname(student entry[], int n)
//Sorts the last names in ascending order.                                                                                                                                                                             
{
  student temp; // temporary place holder until the data is moved.                                                                                                                                                    \
                                                                                                                                                                                                                       
  for(int i=0; i<n-1; i++)
    {
      for(int j=0; j<n-(i+1); j++)
        {
          if(entry[j].lname > entry[j+1].lname)
            {
              temp = entry[j];
              entry[j] = entry[j+1];
              entry[j+1] = temp;
            }
        }
    }
}

void bubblesortscore(student entry[], int n)
// Sorts the student scores in decending order.                                                                                                                                                                        
{
  student temp;
  for(int i=0; i<n-1; i++)
    {
      for(int j=0; j<n-(i+1); j++)
        {
          if(entry[j].testscore < entry[j+1].testscore)
            {
              temp = entry[j];
              entry[j] = entry[j+1];
              entry[j+1] = temp;
            }
        }
    }
}
int score(student entry[], string key, int n)
//This function calculates the students test scores.                                                                                                                                                                   
{
  string answer; //storage for entry's answer                                                                                                                                                                         \
                                                                                                                                                                                                                       
  int temp = 0; // temporary place holder for counting the points correct                                                                                                                                             \
                                                                                                                                                                                                                       
  answer = entry[n].answer;
  for(int i = 0; i < key.length(); i ++)
    {
      if(answer[i] == key[i])
        {
          temp++;
        }
    }
  return temp * 5;
}

double average(student entry[], int n)
// Finds the average score.                                                                                                                                                                                            
{
  double avg = 0.0; //Holds the average.                                                                                                                                                                              \
                                                                                                                                                                                                                       
  double temp = 0.0; //temporary place                                                                                                                                                                                \
                                                                                                                                                                                                                       
  for(int i=0; i<n; i++)
    {
      temp += entry[i].testscore;
    }
  avg = temp / n;
  return avg;
}
double fmedian(student entry[], int n)
// Finds the median score.                                                                                                                                                                                             
{
  double median = 0.0; // stores median                                                                                                                                                                               \
                                                                                                                                                                                                                       
  double temp1 = 0.0; //temporary place holder                                                                                                                                                                        \
                                                                                                                                                                                                                       
  double temp2 = 0.0; //temporary place holder                                                                                                                                                                        \
                                                                                                                                                                                                                       
  for(int i=0; i<n; i++)
    {
      if(n%2==0) //if an even set                                                                                                                                                                                     \
                                                                                                                                                                                                                       
        {
          temp1 = entry[n/2].testscore;
          temp2 = entry[(n/2)+1].testscore;
          median = (temp1 + temp2)/2;
        }
      else
        {
          temp1 = entry[(n/2)+1].testscore;
          median = temp1;
        }
    }
  return median;
}
void print(student entry[], int n, string key, double avg, double median)
// Prints the data derived from the first input file.                                                                                                                                                                  
{
  string outname; //name of output file                                                                                                                                                                               \
                                                                                                                                                                                                                       
  ofstream out; //Filestream output  variable.                                                                                                                                                                         
  int idprint; // Length for formatting the space between the name and id.                                                                                                                                             
  cout << "Enter the name of the output file " << endl;
  cin >> outname;
  out.open(outname.c_str());
  out << "Hernan Andrade, Lec #1001, Lab #1008, Assignment #16" << endl;
  out << endl;
  out <<left << setw(NAMEINTRO) << "NAME" << right << setw(ID) << "ID#" << setw(SCORE) <<  "SCORE" << endl;
  for(int i=0; i<n; i++)
    {
      idprint = NAMEINTRO - entry[i].fname.length() - entry[i].lname.length() + 1;
      out << entry[i].lname << ", " << entry[i].fname << right << setw(idprint) << entry[i].id << setw(SCORE) << entry[i].testscore <<  endl;
    }
  bubblesortscore(entry, n);
  out << endl;
  out << "ClASS STANDINGS" << endl;
  out << setw(ID) << "ID#" << setw(SCORE) << "SCORE" << endl;
  for(int i=0; i<n; i++)
    {
      out << right << setw(ID) << entry[i].id << setw(SCORE) << entry[i].testscore << endl;
    }
  out << endl;
  out << "# of Entrys: " << n << endl;
  out << fixed << setprecision(2);
  out <<  "Class Ave: " << avg << endl;
  out << "Median Score: " << median << endl;
  out << endl;
  out << "BEGIN ENTRY SEARCH FILE PROCESSING" << endl;
 out << endl;
  out << "Test key: " << key << endl;
  out << endl;
  idcheck(out, entry, key, n);
  out.close();
}
void idcheck(ofstream& out, student entry[], string& key, int n)
//Checks if any of th values fromn the second input file match the id's from the first.                                                                                                                                
{
  ifstream insec;//name of the second file stream input variable.                                                                                                                                                      
  string secfilename; //Name of the second input file.                                                                                                                                                                 
  int randomid;//Holds the integers to be read from the second input file.                                                                                                                                             
  int checktemp = 0;
  bool notthree = true; ////Was used to determine if the inputted data matched any existing ID.                                                                                                                        
  cout << "Enter name of 2nd input file" << endl;
  cin >> secfilename;
  insec.open(secfilename.c_str());
  while(insec >> randomid)
    {
      notthree = true;
      for(int i = 0; i < n; i ++)
        {
          if(randomid == entry[i].id)
            {
              out << "#" << randomid << endl;
              out << "Name: " << entry[i].fname << " " << entry[i].lname << endl;
              out << "Score: " << entry[i].testscore << endl;
              out << "Answers: " << entry[i].answer << endl;
              out << endl;
              notthree = false;
            }
        }
      if(notthree == true)
        {
          out << "#" << randomid << " is not valid id." << endl;
          out << endl;
        }
    }
}
