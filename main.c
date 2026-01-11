#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GRADE 400
#define MIN_GRADE 0
#define courses_num 4
#define MIN_AGE 17
#define MAX_AGE 25

struct Student{
    int student_id, age;
    char fullname[50];
    float total_marks, average;
    char grade;
};

float calculate_avg(float total_marks){
    float res = total_marks / courses_num;
    return res;
}

char assign_grade(float average){
    char grade;
    

    if (average >= 90)
    {
        grade = 'A';
    }
    else if (average >= 80 && average < 90)
    {
        grade = 'B';
    }
    else if (average >= 70 && average < 80)
    {
        grade = 'C';
    }
    else if (average >= 60 && average < 70)
    {
        grade = 'D';
    }
    else
    {
        grade = 'F';
    }

    return grade;
}

int isDuplicateID(int id, struct Student students[], int count) {
    for (int i = 0; i < count; i++) {
        if (students[i].student_id == id) {
            return 1;  // duplicate found
        }
    }
    return 0;  // no duplicate
}

void getInput(struct Student students[], int n){
    for (int i = 0; i < n; i++)
    {
        // Here will be the inputs needed from user
        printf("\nEnter The Name for student %d : ", i + 1);
        // scanf(" %c" , &students[i].fullname);
        getchar();
        fgets(students[i].fullname, sizeof(students[i].fullname), stdin); 
        students[i].fullname[strcspn(students[i].fullname, "\n")] = '\0'; // REMOVE newline

        duplicated_id:
        printf("Enter The student id for student \" %s \" : ", students[i].fullname);
        scanf("%d", &students[i].student_id);

        if (isDuplicateID(students[i].student_id, students, i)) {
            printf("Duplicated Student ID!\n");
            goto duplicated_id;
        }


        do
        {
            printf("Enter The Age for student \" %s \" : ", students[i].fullname);
            scanf("%d", &students[i].age);
            if(students[i].age < MIN_AGE || students[i].age > MAX_AGE){
                printf("Invalid Range , 17 : 25\n");
            }
        } while (students[i].age < MIN_AGE || students[i].age > MAX_AGE);

        do
        {
            printf("Enter The student total Marks for student \" %s \" : ", students[i].fullname);
            scanf("%f", &students[i].total_marks);
            if(students[i].total_marks > MAX_GRADE || students[i].total_marks < MIN_GRADE){
                printf("Invalid Range , 0 : 400\n");
            }
        } while (students[i].total_marks > MAX_GRADE || students[i].total_marks < MIN_GRADE);

        // Here will be the calculated values (derrived attributes)
        students[i].average = calculate_avg(students[i].total_marks);

        students[i].grade = assign_grade(students[i].average);
    }
}

char* performanceCategory(char grade){
    switch (grade)
    {
    case 'A':
        return "Excellent";
        break;
    case 'B':
        return "Good";
        break; 
    case 'C':
        return "Satisfactory";
        break;
    case 'D':
        return "Needs Improvement";
        break;  
    case 'F':
        return "Needs Improvement";
        break;                
    default:
        return "Unknown";
        break;
    }

}

void printStudents(struct Student students[], int n) {
  

    // Print table header
    printf("+----+-----+----------------------+-------------+------------+-------+------------------+\n");
    printf("| ID | Age | Name                 | Total Marks | Percentage | Grade | Performance      |\n");
    printf("+----+-----+----------------------+-------------+------------+-------+------------------+\n");

    // Print each student
    for (int i = 0; i < n; i++) {
        printf("| %-2d | %-3d | %-20s | %-11.2f | %-10.2f | %-5c | %-16s |\n",
               students[i].student_id,
               students[i].age,
               students[i].fullname,
               students[i].total_marks,
               (students[i].total_marks / MAX_GRADE) * 100,
               students[i].grade,
               performanceCategory(students[i].grade));
    }

    printf("+----+-----+----------------------+-------------+------------+-------+------------------+\n");
}

int searchStudent(int studentId , struct Student students[],int n){
    
    for(int i = 0; i < n ; i++) {
        if(studentId == students[i].student_id){
          return i;
        }  
    }
    return -1;
}

void sortStudents(struct Student students[] , int n){
    for(int i = 0; i < n-1; i++){
        for(int j = i ; j < n; j++){
            if(students[i].total_marks < students[j].total_marks){
            struct Student temp;
            temp = students[i];
            students[i] = students[j];
            students[j] = temp;
            }
        }
    }
}

double calculateClassAverage(struct Student students[] , int n){
    double sum = 0;

        for(int i = 0 ; i < n ; i++){
            sum += students[i].average;
        }

        double average = sum / n;
        return average;
}

void updateStudent(struct Student *students,int n){

    int id;
    printf("Enter Student ID you want to update it : ");
    scanf("%d",&id);

    int index = searchStudent(id , students , n);

    if(index == -1){
        printf("The Student is not found");
        return;
    }
    // This line creates a pointer refering to the needed student 
    struct Student *st = students + index;


    do {
        printf("Enter new age for \"%s\": ", st->fullname);
        scanf("%d", &st->age);
    }while (st->age < MIN_AGE || st->age > MAX_AGE);
    
     do
    {
        printf("Enter new total marks for \"%s\": ", st->fullname);
        scanf("%f", &st->total_marks);
    } while (st->total_marks < MIN_GRADE || st->total_marks > MAX_GRADE);

     st->average = calculate_avg(st->total_marks);
     st->grade = assign_grade(st->total_marks);

    printf("Student data updated successfully!\n");


}

void printMenu() {
    printf("==========================================\n");
    printf("         STUDENT MANAGEMENT SYSTEM        \n");
    printf("==========================================\n");
    printf("1. ENTER STUDENT DATA\n");
    printf("2. DISPLAY ALL STUDENTS\n");
    printf("3. SEARCH FOR STUDENT\n");
    printf("4. SORT STUDENTS BY MARKS\n");
    printf("5. CALCULATE CLASS STATISTICS\n");
    printf("6. SAVE DATA TO FILE\n");
    printf("7. LOAD DATA FROM FILE\n");
    printf("8. UPDATE STUDENT RECORD\n");
    printf("9. EXIT\n");
    printf("==========================================\n");
    printf("Enter your choice (1-9): ");
}

void saveToFile(struct Student students[] , int n){
    FILE *file_output;

    file_output = fopen("students.txt","w");

    for(int i = 0; i < n; i++){
        fprintf(file_output,"%d,%d,%s,%.2f,%.2f,%c\n",
            students[i].student_id ,
            students[i].age, 
            students[i].fullname , 
            students[i].total_marks, 
            students[i].average,
            students[i].grade
            );
    }

    fclose(file_output);

    printf("Data Saved Successfully!");
}

void readFromFile(){
    FILE *file_input;

    file_input = fopen("students.txt","r");

    if(file_input == NULL){
        printf("\nFile doesn\'t Exist!\n");
        return;
    }

    struct Student students[100];
    int lines = 0;
    char line[200];

    while (fgets(line, sizeof(line), file_input)) {
        struct Student student;
        // remove newline if present
        line[strcspn(line, "\n")] = 0;

        if (sscanf(line, "%d,%d,%49[^,],%f,%f,%c",
                &student.student_id,
                &student.age,
                student.fullname,
                &student.total_marks,
                &student.average,
                &student.grade) == 6) {
            students[lines++] = student;
            if (lines >= 100) break;  // avoid overflow
        }
    }
    fclose(file_input);

    printStudents(students , lines);

    
    
 }


int main() {
    struct Student students[100];
    int n = 0; // number of students currently in the system
    int choice;

    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of students to add: ");
                scanf("%d", &n);
                getInput(students, n);
                break;

            case 2:
                if (n == 0) {
                    printf("No students available to display.\n");
                } else {
                    printStudents(students, n);
                }
                break;

            case 3: {
                int id;
                printf("Enter student ID to search: ");
                scanf("%d", &id);
                int index = searchStudent(id, students, n);
                if (index == -1) {
                    printf("Student not found.\n");
                } else {
                    printf("Student found:\n");
                    printStudents(&students[index], 1);
                }
                break;
            }

            case 4:
                if (n <= 1) {
                    printf("Not enough students to sort.\n");
                } else {
                    sortStudents(students, n);
                    printf("Students sorted by total marks (descending).\n");
                }
                break;

            case 5:
                if (n == 0) {
                    printf("No students to calculate statistics.\n");
                } else {
                    double classAvg = calculateClassAverage(students, n);
                    printf("Class Average: %.2f\n", classAvg);
                }
                break;

            case 6:
                if (n == 0) {
                    printf("No students to save.\n");
                } else {
                    saveToFile(students, n);
                }
                break;

            case 7:
                readFromFile();
                break;

            case 8:
                if (n == 0) {
                    printf("No students to update.\n");
                } else {
                    updateStudent(students, n);
                }
                break;

            case 9:
                printf("Exiting program. Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice! Please enter 1-9.\n");
                break;
        }

        printf("\n"); 
    }

    return 0;
}
