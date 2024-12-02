# ReadCSV-CPP

## Implemenation details
- the implementation is for a csv file which first column holds the first name, second column the last name, and third column holds the student id.
- for each row of data, a new Student object is created using the Student struct and is saved in a vector container.
- getline() function is used to read each line from the file and also each string.
- for the ease of handing string data, each line of the file is transformed into stringstream from which comma separated details are read using getline() function.
