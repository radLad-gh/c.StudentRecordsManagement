#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STUDENTS 2000
#define MAX_COURSES 100
#define MAX_ENROLLMENTS 5000
#define MAX_NAME_LEN 50
#define COURSE_ID_LEN 3
#define SEM_LEN 9

/*
Notes about project:
    students.txt(MAX2000): int studentID, char fname, char lname, int dob[d/m/y]
    courses.txt: char courseID, char courseName[50], float credit
    enrollment.txt(MAX5000): int studentID, char courseID, char semester, float creditHours
*/

typedef struct Students{
    int studentID;
    char fname[MAX_NAME_LEN];
    char lname[MAX_NAME_LEN];
    int birthDay;
    int birthMonth;
    int birthYear;
} Students;

typedef struct Courses{
    char courseID[COURSE_ID_LEN];
    char courseName[MAX_NAME_LEN];
    float creditHours;
} Courses;

typedef struct Enrollment{
    int studentID;
    char courseID[COURSE_ID_LEN];
    char semester[MAX_NAME_LEN];
    float score;
} Enrollment;

//file mgmt functions
Students* loadStudents(int size, int* numStudents);
Courses* loadCourses(int size, int* numCourses);
Enrollment* loadEnrollment(int size, int* numEnrollment);

void menu(Students* s, int numStudents, Courses* c, int numCourses, Enrollment* e, int numEnrolled);

void searchStudents(Students* s, int numStudents, Courses* c, int numCourses, Enrollment* e, int numEnrolled, int opTree);
void searchCourses(Students* s, int numStudents, Courses* c, int numCourses, Enrollment* e, int numEnrolled, int opTree);
void addCourse(Courses* c, int* numCourses);
void count(Courses* c, int numCourses, Enrollment* e, int numEnrolled, int opTree);
void sort(Students* s, int numStudents);
void letterGrade(int score);

int main(void)
{
    int numStudents, numCourses, numEnrolled, i;
    Students* students = loadStudents(MAX_STUDENTS, &numStudents);
    Courses* courses = loadCourses(MAX_COURSES, &numCourses);
    Enrollment* enrollment = loadEnrollment(MAX_ENROLLMENTS, &numEnrolled);
/*
    printf("\nPrinting Student Data:\n");
    for(i = 0; i < numStudents; i++)
        printf("Entry #%d {ID: %d, Fname: %s, Lname: %s, DOB: %d/%d/%d}\n", i+1, students[i].studentID, students[i].fname, students[i].lname, students[i].birthDay, students[i].birthMonth, students[i].birthYear);

    printf("\nPrinting Course Data:\n");
    for(i = 0; i < numCourses; i++)
        printf("Entry #%d {Course ID: %s, Course Name: %s, creditHours: %.2f}\n", i+1, courses[i].courseID, courses[i].courseName, courses[i].creditHours);

    printf("\nPrinting Enrollment Data:\n");
    for(i = 0; i < numEnrolled; i++)
        printf("Entry #%d {Student ID: %d, Course ID: %s, Semester: %s, Score: %.2f}\n", i+1, enrollment[i].studentID, enrollment[i].courseID, enrollment[i].semester, enrollment[i].score);
*/
    menu(students, numStudents, courses, numCourses, enrollment, numEnrolled);

    free(students);//free structure mem
    free(courses);
    free(enrollment);

    return 0;
}

//complete
Students* loadStudents(int size, int* numStudents) {
    FILE *fp;
    Students* sp;
    int i;
    size_t n = 0;
    char x;

    if((fp = fopen("students.txt", "r")) == NULL)
    {
        printf("Could not open students.txt file.\n");
        exit(-1);
    }
    else
    {
        //printf("Successfully opened students.txt\n");
        sp = (Students*)malloc(MAX_STUDENTS * sizeof(Students));//Attempt to allocate mem
        if(sp == NULL)//on fail
        {
            printf("Could not allocate memory\n");
            fclose(fp);
            exit(-1);
        }
        else//on pass
        {
            //printf("Memory allocated successfully using malloc.\n");
        }
        //Load data here
        while(!feof(fp))
        {
            fscanf(fp, "%d %s %s %d %d %d", &sp[n].studentID, sp[n].fname, sp[n].lname, &sp[n].birthDay, &sp[n].birthMonth, &sp[n].birthYear);
            n++;
        }
        *numStudents = n; //assigns the number of students for outside function

        fclose(fp);
        return sp;
    }
}

//complete
Courses* loadCourses(int size, int* numCourses) {
    FILE *fp;
    Courses* cp;
    int i;
    size_t n = 0;
    char x;

    if((fp = fopen("courses.txt", "r")) == NULL)
    {
        printf("Could not open courses.txt file.\n");
        exit(-1);
    }
    else
    {
        //printf("Successfully opened courses.txt\n");
        cp = (Courses*)malloc(size * sizeof(Courses));//Attempt to allocate mem
        if(cp == NULL)//on fail
        {
            printf("Could not allocate memory\n");
            fclose(fp);
            exit(-1);
        }
        else//on pass
        {
            //printf("Memory allocated successfully using malloc.\n");
        }
        //Load data here
        while(!feof(fp))
        {
            fscanf(fp, "%s %s %f", cp[n].courseID, cp[n].courseName, &cp[n].creditHours);
            //printf("%.2f\n", cp[n].creditHours);
            n++;
        }
        *numCourses = n; //assigns the number of students for outside function

        fclose(fp);
        return cp;
    }
}

//complete
Enrollment* loadEnrollment(int size, int* numEnrolled) {
    FILE *fp;
    Enrollment* ep;
    int i;
    size_t n = 0;
    char x;

    if((fp = fopen("enrollment.txt", "r")) == NULL) {
        printf("Could not open enrollment.txt file.\n");
        exit(-1);
    }
    else {
        //printf("Successfully opened enrollment.txt\n");
        ep = (Enrollment*)malloc(size * sizeof(Enrollment));//Attempt to allocate mem
        if(ep == NULL) {//on fail
            printf("Could not allocate memory\n");
            fclose(fp);
            exit(-1);
        }
        else {//on pass
            //printf("Memory allocated successfully using malloc.\n");
        }
        //Load data here
        while(!feof(fp)) {
            fscanf(fp, "%d %s%s %f", &ep[n].studentID, ep[n].courseID, ep[n].semester, &ep[n].score);
            n++;
        }
        *numEnrolled = n; //assigns the number of students for outside function

        fclose(fp);
        return ep;
    }
}

//complete
void letterGrade(int score) {
    if (score > 90)
        printf("A\n");
    else if(score >= 80)
        printf("B\n");
    else if(score >= 70)
        printf("C\n");
    else if(score >= 60)
        printf("D\n");
    else
        printf("F\n");
}

//complete
void searchStudents(Students* s, int numStudents, Courses* c, int numCourses, Enrollment* e, int numEnrolled, int opTree) {

    int i, j, k, flag;
    flag = 0;
    //printf("opTree: %d, numStudents: %d\n", opTree, numStudents);

    if(opTree == 0 || opTree == 1) {
        char name[MAX_NAME_LEN];
        scanf("%s", name);


        if(opTree == 0) {
            for(i = 0; i < numStudents; i++)
                if(strcmp(s[i].lname, name) == 0) {
                    printf("------------------\n");
                    printf("%d %s %s %d/%d/%d\n", s[i].studentID, s[i].fname, s[i].lname, s[i].birthMonth, s[i].birthDay, s[i].birthYear);

                    for(j = 0; j < numEnrolled; j++) {
                        if(e[j].studentID == s[i].studentID) {
                            printf("%s ", e[j].courseID);
                                for(k = 0; k < numCourses; k++)
                                    if(strcmp(e[j].courseID, c[k].courseID) == 0) {
                                        printf("%s ", c[k].courseName);
                                        break;
                                    }
                                printf("%s %d ", e[j].semester, (int)e[j].score);
                                letterGrade(e[j].score);
                        }
                    }
                    flag++;
                }
        }
        else if(opTree == 1) {
            for(i = 0; i < numStudents; i++)
                if(strcmp(s[i].fname, name) == 0) {
                    printf("------------------\n");
                    printf("%d %s %s %d/%d/%d\n", s[i].studentID, s[i].fname, s[i].lname, s[i].birthMonth, s[i].birthDay, s[i].birthYear);
                    for(j = 0; j < numEnrolled; j++) {
                        if(e[j].studentID == s[i].studentID) {
                            printf("%s ", e[j].courseID);
                                for(k = 0; k < numCourses; k++)
                                    if(strcmp(e[j].courseID, c[k].courseID) == 0) {
                                        printf("%s ", c[k].courseName);
                                        break;
                                    }
                                printf("%s %d ", e[j].semester, (int)e[j].score);
                                letterGrade(e[j].score);
                        }
                    }
                    flag++;
                }
        }
    }
    else if(opTree == 2 || opTree == 3) {
        int param;
        scanf("%d", &param);

        if(opTree == 2) {
            for(i = 0; i < numStudents; i++)
                if(s[i].studentID == param) {
                    printf("------------------\n");
                    printf("%d %s %s %d/%d/%d\n", s[i].studentID, s[i].fname, s[i].lname, s[i].birthMonth, s[i].birthDay, s[i].birthYear);
                    for(j = 0; j < numEnrolled; j++) {
                        if(e[j].studentID == s[i].studentID) {
                            printf("%s ", e[j].courseID);
                                for(k = 0; k < numCourses; k++)
                                    if(strcmp(e[j].courseID, c[k].courseID) == 0) {
                                        printf("%s ", c[k].courseName);
                                        break;
                                    }
                                printf("%s %d ", e[j].semester, (int)e[j].score);
                                letterGrade(e[j].score);
                        }
                    }
                    flag++;
                }
        }
        else if(opTree == 3) {
            for(i = 0; i < numStudents; i++)
                if(s[i].birthYear == param) {
                    printf("------------------\n");
                    printf("%d %s %s %d/%d/%d\n", s[i].studentID, s[i].fname, s[i].lname, s[i].birthMonth, s[i].birthDay, s[i].birthYear);
                    for(j = 0; j < numEnrolled; j++) {
                        if(e[j].studentID == s[i].studentID) {
                            printf("%s ", e[j].courseID);
                                for(k = 0; k < numCourses; k++)
                                    if(strcmp(e[j].courseID, c[k].courseID) == 0) {
                                        printf("%s ", c[k].courseName);
                                        break;
                                    }
                                printf("%s %d ", e[j].semester, (int)e[j].score);
                                letterGrade(e[j].score);
                        }
                    }
                    flag++;
                }
            }
        }
    //printf("Flag: %d\n", flag);
    if(flag == 0) {
        printf("------------------\n");
        printf("not found\n");
    }
}

//complete
void searchCourses(Students* s, int numStudents, Courses* c, int numCourses, Enrollment* e, int numEnrolled, int opTree) {

    int i, j, k, flag;
    flag = 0;
    //printf("opTree: %d, numStudents: %d\n", opTree, numStudents);

    char cID[COURSE_ID_LEN];
    scanf("%s", cID);


    if(opTree == 0) {
        for(i = 0; i < numCourses; i++)
            if(strcmp(c[i].courseID, cID) == 0) {
                printf("------------------\n");
                printf("%s %d\n", c[i].courseName, (int)c[i].creditHours);
                for(j = 0; j < numEnrolled; j++)
                    if(strcmp(e[j].courseID, c[i].courseID) == 0) {
                        for(k = 0; k < numStudents; k++)
                            if(s[k].studentID == e[j].studentID)
                                printf("%s %s ", s[k].fname, s[k].lname);
                        printf("%s %d ", e[j].semester, (int)e[j].score);
                        letterGrade(e[j].score);
                    }
            flag++;
            }
    }
    else if(opTree == 1) {
        char sem[9];
        scanf("%s", sem);

        for(i = 0; i < numStudents; i++)
            if(strcmp(c[i].courseID, cID) == 0) {
                printf("------------------\n");
                printf("%s %d\n", c[i].courseName, (int)c[i].creditHours);
                for(j = 0; j < numEnrolled; j++)
                    if((strcmp(e[j].courseID, c[i].courseID) == 0) && (strcmp(e[j].semester, sem) == 0)) {
                        for(k = 0; k < numStudents; k++)
                            if(s[k].studentID == e[j].studentID)
                                printf("%s %s ", s[k].fname, s[k].lname);
                        printf("%s %d ", e[j].semester, (int)e[j].score);
                        letterGrade(e[j].score);
                    }
            flag++;
            }
    }
    if(flag == 0) {
        printf("------------------\n");
        printf("not found\n");
    }
}

//bug that hangs on count students_semester
void count(Courses* c, int numCourses, Enrollment* e, int numEnrolled, int opTree) {
    int i, j;
    printf("------------------\n");
    if(opTree == 0) {
        int* numSpC = calloc(numCourses, sizeof(int));
        for(i = 0; i < numCourses; i++)
            for(j = 0; j < numEnrolled; j++)
                if(strcmp(c[i].courseID, e[j].courseID) == 0)
                    numSpC[i]++;
        for(i = 0; i < numCourses; i++)
            printf("%s %d\n", c[i].courseID, numSpC[i]);
    }
    else if(opTree == 1) {
/*
        char numCpSem[9];
        int i, k;
        i = k = 0;

        strcpy(numCpSem, e[i].semester);
        while(e[i].semester) {
            printf("%s ", e[i].semester);
            while (strcmp(e[i].semester, e[i+1].semester) == 0)
                i++;
            printf("%d\n", (i+1)-k);
            k += (i+1);//grabs current numCourses under that string
            i++;
            if(e[i].semester != NULL)
                strcpy(numCpSem, e[i].semester);
            else {
                printf("------------------\n");
                break;
            }
        }
*/
        char completed_list[8][9];
        int student_num[8] = {0};
        int tracker = 0;
        int flag;
        for(i = 0; i < numEnrolled; i++) {
            for(j = 0; j <= tracker; j++) {
                if(strcmp(completed_list[j], e[i].semester) == 0) {
                    //printf("student_num[%d]: %d\n", j, student_num[j]);
                    student_num[j]++;
                    tracker++;
                    flag++;
                    break;
                }
            }
            if(flag == 0) {
                strcpy(completed_list[tracker], e[j].semester);
                tracker++;
                student_num[tracker]++;
            }
        }
        for(i = 0; i < tracker; i++)
            printf("%s %d\n", completed_list[i], student_num[i]);
    }
}

//complete
void addCourse(Courses* c, int* numCourses) {
    char courseID[3], courseName[21];
    float credit;
    int i;
    printf("------------------\n");
    scanf("%s %s %f", courseID, courseName, &credit);

    for(i = 0; i < *numCourses; i++)
        if(strcmp(c[i].courseID, courseID) == 0) {
            printf("\"violation of course id uniqueness. Cannot add the record.\"\n");
            return;
        }

    FILE* fp = fopen("courses.txt", "a");
    fprintf(fp, "%s %s %d\n", courseID, courseName, (int)credit);
    printf("record added\n");
    fclose(fp);
    free(c);
    c = loadCourses(MAX_COURSES, numCourses);
}

//complete
void sort(Students* s, int numStudents) {
    printf("------------------\n");
    Students temp;
    int minIdx;
    int i, j;

    for(i = 0; i < numStudents; i++) {
        minIdx = i;
        for(j = i; j < numStudents; j++)
            if(s[j].studentID < s[minIdx].studentID)
                minIdx = j;
        temp = s[i];
        s[i] = s[minIdx];
        s[minIdx] = temp;

        printf("%d %s %s %d/%d/%d\n", s[i].studentID, s[i].fname, s[i].lname, s[i].birthMonth, s[i].birthDay, s[i].birthYear);
    }
}

//complete
void menu(Students* s, int numStudents, Courses* c, int numCourses, Enrollment* e, int numEnrolled) {
    while(1) {
        printf("==================\n");
        char cmd1[15];
        int opTree;
        scanf("%s", cmd1);

        if(strcmp("search_students", cmd1) == 0) {
            char cmd2[6];
            scanf("%s", cmd2);

            //options for search_students
            if(strcmp("lname", cmd2) == 0)
                opTree = 0;
            else if(strcmp("fname", cmd2) == 0)
                opTree = 1;
            else if(strcmp("id", cmd2) == 0)
                opTree = 2;
            else if(strcmp("byear", cmd2) == 0)
                opTree = 3;
            //printf("We got here\n");

            searchStudents(s, numStudents, c, numCourses, e, numEnrolled, opTree);
        }

        else if(strcmp("search_course", cmd1) == 0) {
            char cmd2[13];
            scanf("%s", cmd2);

            //options for search_courses
            if(strcmp("cid", cmd2) == 0)
                opTree = 0;
            else if(strcmp("cid_semester", cmd2) == 0)
                opTree = 1;

            searchCourses(s, numStudents, c, numCourses, e, numEnrolled, opTree);
        }

        else if(strcmp("add_course", cmd1) == 0) {
            addCourse(c, &numCourses);
        }

        else if(strcmp("count", cmd1) == 0) {
            char cmd2[18];
            scanf("%s", cmd2);

            //options for count
            if(strcmp("students", cmd2) == 0) {
                printf("------------------\n");
                printf("total students %d\n", numStudents);
                printf("------------------\n");
                continue;
            }
            else if(strcmp("students_course", cmd2) == 0)
                opTree = 0;
            else if(strcmp("students_semester", cmd2) == 0)
                opTree = 1;

            count(c, numCourses, e, numEnrolled, opTree);
        }

        else if(strcmp("sort", cmd1) == 0) {
            sort(s, numStudents);
        }

        else if(strcmp("exit", cmd1) == 0) {
            printf("------------------\n");
            printf("Bye!");
            break;
        }

        else {
            printf("------------------\n");
            printf("Command not understood. Please try another.\n");
        }

        printf("------------------\n");
    }
}

