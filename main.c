#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_GRADE 400
#define MIN_GRADE 0
#define courses_num 4
#define MIN_AGE 17
#define MAX_AGE 25

struct Student {
    int Student_ID;
    char Full_Name[50];
    int Age;
    float Total_Marks, Average;
    char Grade;
};

float calculateAverage(float Tmark){
    return Tmark/4;
}

float calculateClassAverage(struct Student students[], int n){
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += students[i].Average;
    }
    return (sum / n);
}

char assignGrade(float avg){

    if (avg >= 90)
    {
        return 'A';
    }

    else if (avg >= 80  && avg < 90) 
    {
        return 'B';
    }
    
    else if (avg >= 70 && avg < 80)
    {
        return 'D';
    }

     else if (avg >= 60 && avg < 70)
    {
        return 'C';
    }

    else if (avg < 60)
    {
        return 'F';
    }
    
}

int searchStudent(struct Student students[], int n){
    int SID;
    printf("Enter Student ID : ");
    scanf("%d", &SID);

    for (int i = 0; i < n; i++)
    {
        if (SID == students[i].Student_ID)
        {
            return i;
        }
        
    }
    
    return -1;
    
}

void sortStudents(struct Student students[], int n){

   for(int i = 0; i < n; i++){
                if(students[i].Total_Marks < students[i+1].Total_Marks){
                struct Student temp;
                temp = students[i];
                students[i] = students[i+1];
                students[i+1] = temp;
            }
    }
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
    printf("7. UPDATE STUDENT RECORD\n");
    printf("8. EXIT\n");
    printf("==========================================\n");
    printf("Enter your choice (1-8): ");
}

void print_students(struct Student students[], int n)
{
    printf("\n---------------------------------------------------------------\n");
    printf("| ID   | Name                     | Age | Total Marks | Avgerage  | Grade |\n");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("| %-4d | %-24s | %-3d | %-5.1f | %-4.1f | %-1c |\n",
               students[i].Student_ID,
               students[i].Full_Name,
               students[i].Age,
               students[i].Total_Marks,
               students[i].Average,
               students[i].Grade);
    }

    printf("---------------------------------------------------------------\n");
}

int isValidName(char *name)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ')
            return 0; // invalid
    }
    return 1; // valid
}

int isUniqueID(int id, int index, struct Student students[])
{
    for (int i = 0; i < index; i++)
    {
        if (students[i].Student_ID == id)
            return 0; // not unique
    }
    return 1; // unique
}

void input_Student(struct Student students[], int n){

    for (int i = 0; i < n; i++)
    {
        do{
            printf("\nEnter The Name for student %d : ", i + 1);
            getchar();
            fgets(students[i].Full_Name, sizeof(students[i].Full_Name), stdin);
            students[i].Full_Name[strcspn(students[i].Full_Name, "\n")] = '\0';

        } while (!isValidName(students[i].Full_Name));

        do{
            printf("Enter The student id for student \"%s\" : ", students[i].Full_Name);
            scanf("%d", &students[i].Student_ID);

        } while (!isUniqueID(students[i].Student_ID, i, students));

        do
        {
            printf("Enter The Age for student \" %s \" : ", students[i].Full_Name);
            scanf("%d", &students[i].Age);
        } while (students[i].Age < MIN_AGE || students[i].Age > MAX_AGE);

        do
        {
            printf("Enter The student total Marks for student \" %s \" : ", students[i].Full_Name);
            scanf("%f", &students[i].Total_Marks);
            // if -> 
        } while (students[i].Total_Marks > MAX_GRADE || students[i].Total_Marks < MIN_GRADE);

        // Here will be the calculated values (derrived attributes)
        students[i].Average = calculateAverage(students[i].Total_Marks);

        students[i].Grade = assignGrade(students[i].Average);
        
    }
    

}

void saveToFile(struct Student students[], int n){

    FILE *file_output;
    file_output = fopen("Students.txt","w");

    for(int i = 0; i < n; i++){
        fprintf(file_output,"%d,%d,%s,%.2f,%.2f,%c\n",
            students[i].Student_ID ,
            students[i].Age, 
            students[i].Full_Name , 
            students[i].Total_Marks, 
            students[i].Average,
            students[i].Grade
            );
    }

    fclose(file_output);

    printf("Data Saved Successfully!");

}

void updateStudent(struct Student *students, int n){
    int id;
    printf("Enter Student ID you want to update it : ");
    scanf("%d",&id);

    int index = searchStudent(students , n);

    if(index == -1){
        printf("The Student is not found");
        return;
    }
    // This line creates a pointer refering to the needed student 
    struct Student *st = students + index;


    do {
        printf("Enter new age for \"%s\": ", st->Full_Name);
        scanf("%d", &st->Age);
    }while (st->Age < MIN_AGE || st->Age > MAX_AGE);
    
     do
    {
        printf("Enter new total marks for \"%s\": ", st->Full_Name);
        scanf("%f", &st->Total_Marks);
    } while (st->Total_Marks < MIN_GRADE || st->Total_Marks > MAX_GRADE);

     st->Average = calculateAverage(st->Total_Marks);
     st->Grade = assignGrade(st->Total_Marks);

    printf("Student data updated successfully!\n");
}

int main() 
{
    struct Student students[100];
    int n;
    int choice;
    while (1)
    {
        printMenu();
        scanf("%d", &choice);        
        switch (choice)
        {
            case 1:
                printf("Enter number of students to add: ");
                scanf("%d", &n);
                input_Student(students, n);
                break;
            case 2:
                if (n == 0) {
                    printf("No students available to display.\n");
                } else {
                    print_students(students, n);
                }
                break;
            case 3:
                int index = searchStudent(students, n);
                if (index == -1)
                {
                    printf("Not Found\n");
                }
                else{
                    printf("Student Found\n");
                    print_students(&students[index], 1);
                }
                break;
            case 4:
                sortStudents(students, n);
                printf("Students sorted by total marks (descending).\n");
                break;
            case 5:
                if(n == 0){
                    printf("No students to calculate statistics.\n");
                } else {
                    printf("The Class Average is : %.2f\n",calculateClassAverage(students, n));
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
                if (n == 0) {
                    printf("No students to update.\n");
                } else {
                    updateStudent(students, n);
                }
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    
    
}