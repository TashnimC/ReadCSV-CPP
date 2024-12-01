/**
 * Sources:
 *      1. https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/ 
 *      2. https://codereview.stackexchange.com/questions/211826/code-to-read-and-write-csv-files
 * 
 * 
 * Note:
 *      1. using shared_ptr instead of unique_ptr since unique_ptr does not allow copying pointers
 *      2. If unique_ptr is used then object has to be created like L#110 - directly inside the push_back function
 */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

struct Student
{
    std::string name;
    int studnetID;

    public:
        Student(std::string firstName, std::string lastName, int id)
        {
            name = firstName + lastName;
            studnetID = id;
        }
};

class StudentFactory
{
    public:
        std::shared_ptr<Student> createStudentObj(std::string firstName, std::string lastName, int id)
        {
            return std::make_shared<Student>(firstName, lastName, id);
        }
};

void readCSV(std::string filename, std::vector< std::shared_ptr<Student> >& listStudents)
{
    // create an input filestream
    std::ifstream fileStream(filename);

    std::string line, colName;

    if(fileStream.good())
    {
        // create a student factory instance to create students
        StudentFactory stdFact;

        std::getline(fileStream, line);
        std::stringstream strStream(line);

        // read the column names
        while( std::getline(strStream, colName, ',') )
        {
            std::cout << colName << "\n";
        }
        
        // read each line
        while( std::getline(fileStream, line) )
        {
            // convert into string stream
            std::stringstream strStream(line);

            // keep track of current column index
            int colIdx = 0;
            std::string val;

            // read each column
            std::string firstName = "";
            std::string lastName = "";
            int id = 0;
            while(std::getline(strStream, line, ',') && colIdx < 3)
            {
                if(colIdx == 0)
                {
                    firstName = line;
                }
                else if(colIdx == 1)
                {
                    lastName = line;
                }
                else if(colIdx == 2)
                {
                    try
                    {
                        id = std::stoi(line); // Throws: no conversion
                    }
                    catch (std::invalid_argument const& ex)
                    {
                        std::cout << "#3: " << ex.what() << '\n';
                    }
                    
                }

                colIdx++;

            }

            // create a studnet based on the extracted info
            auto student = stdFact.createStudentObj(firstName, lastName, id);
            
            // add the created student to the vector list of students
            try 
            {
                
                //listStudents.push_back(stdFact.createStudentObj(firstName, lastName, id));
                listStudents.push_back(student);
            } 
            catch (const std::bad_alloc& e) 
            {
                std::cerr << "Memory allocation error: " << e.what() << std::endl;
            } 
            catch (const std::exception& e) 
            {
                std::cerr << "Other exception: " << e.what() << std::endl;
            }
        }

    }
}

int main()
{
    std::vector< std::shared_ptr<Student> > listOfStudents;
    readCSV("grades.csv", listOfStudents);
    
    for(auto it = listOfStudents.begin(); it != listOfStudents.end(); it++)
    {
        std::cout << (*it)->name << " >> " << (*it)->studnetID << "\n";
    }
    
    return 0;
}