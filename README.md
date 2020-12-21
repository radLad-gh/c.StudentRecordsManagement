# C-StudentDB-Mgmt
Student/Course records management framework written in C

Includes the following CLI commands for management of records: 
  -search_students
  -search_course
  -add_course
  -count
  -sort
  
The CLI argument structure is as follows:
```
  <search_students> <fname || lname || id || year> <fnameString || lnameString || idInteger || yearInteger>
  <search_course> <cid || cid_semester> <cid_STRING || cid_semester_cid_STRING> <cid_semesterSemester> //ex: search_course c1, search_course cid_semester c1 spring19
  <add_course> <cid_STRING> <course_name_STRING> <course_credit_FLOAT>
  <count> <students || students_course || students_semester> //prints list of either: total students, students per course, or students per semester
  <sort> //This fn lists the students in sequential order, by id, an integer.
``` 
