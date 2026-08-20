#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 100
#define SUBJECTS 5

struct Student
{

    int roll;
    char name[50];
    char department[50];
    int semester;
    float marks[SUBJECTS];
    float gpa;

};


       float getGradePoint(float marks)
{
    if (marks >= 80 && marks <= 100)
        return 4.00;
    else if (marks >= 75)
        return 3.75;
    else if (marks >= 70)
        return 3.50;
    else if (marks >= 65)
        return 3.25;
    else if (marks >= 60)
        return 3.00;
    else if (marks >= 55)
        return 2.75;
    else if (marks >= 50)
        return 2.50;
    else if (marks >= 45)
        return 2.25;
    else if (marks >= 40)
        return 2.00;
    else
        return 0.00;
}

float calculateGPA(float marks[])
{
    float credits[SUBJECTS] = {1, 3, 1, 3, 2};
    float totalPoint = 0;
    float totalCredit = 0;

    for (int i = 0; i < SUBJECTS; i++)
    {
        float gradePoint = getGradePoint(marks[i]);

        totalPoint += gradePoint * credits[i];
        totalCredit += credits[i];
    }

    return totalPoint / totalCredit;
}

int main()
{
    struct Student
    students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    /* Load Student Data from File */
    FILE *file;

    file = fopen("students.dat", "rb");

    if (file != NULL)
    {
        fread(&studentCount, sizeof(int), 1, file);
        fread(students, sizeof(struct Student), studentCount, file);

        fclose(file);
    }


    while(1)
    {
        printf("\n========================================\n");
        printf("    STUDENT RECORD MANAGEMENT SYSTEM\n");
        printf("========================================\n");
        printf("1. Add New Student\n");
        printf("2. View All Student\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Performance Analytics\n");
        printf("7. Low GPA Warning List\n");
        printf("8. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        /* Exit */
        if (choice == 8)
        {
            printf("\nExiting program...\n");
            break;
        }

        /* Add New Student*/
        if (choice == 1)
        {
            if (studentCount >= MAX_STUDENTS)
            {
                printf("\nStudents limit reached!\n");
            }
            else
            {
                int duplicate = 0;

                printf("\nEnter Student Roll: ");
                scanf("%d", &students[studentCount].roll);

                /* Check Duplicate Roll */
                for (int i = 0; i < studentCount; i++)
                {
                    if (students[i].roll == students[studentCount].roll)
                    {
                        duplicate = 1;
                        break;
                    }
                }

                if (duplicate == 1)
                {
                    printf("\nRoll Number already exists!\n");
                }
                else
                {
                    printf("Enter Student Name: ");
                    scanf("%s", students[studentCount].name);

                    printf("Enter Department: ");
                    scanf("%s", students[studentCount].department);

                    printf("Enter Semester: ");
                    scanf("%d", &students[studentCount].semester);

                    /* Enter Marks */
                    printf("\nEnter Marks for 5 Subjects:\n");

                    for (int i = 0; i < SUBJECTS; i++)
                    {
                        do
                        {
                            printf("Subject %d Marks: ", i + 1);
                            scanf("%f", &students[studentCount].marks[i]);

                            if (students[studentCount].marks[i] < 0 ||
                                students[studentCount].marks[i] > 100)
                            {
                                printf("Invalid marks! ");
                                printf("Please enter marks between 0 and 100.\n");
                            }

                        } while (students[studentCount].marks[i] < 0 ||
                                 students[studentCount].marks[i] > 100);
                    }
                    students[studentCount].gpa=
                    calculateGPA(students[studentCount].marks);

                    studentCount++;
                    /*Save Student Data to File*/

file = fopen("students.dat", "wb");

if (file != NULL)
{
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(struct Student), studentCount, file);

    fclose(file);
}

                    printf("\nStudent Added Successfully!\n");
                    printf("GPA: %.2f\n", students[studentCount - 1].gpa);


                }
            }
        }

        /* ================= VIEW ALL STUDENTS ================= */
        if (choice == 2)
        {
            if (studentCount == 0)
            {
                printf("\nNo student records found!\n");
            }
            else
            {
                printf("\n================ ALL STUDENTS ================\n");

                printf("%-8s %-15s %-12s %-10s\n",
                       "Roll", "Name", "Department", "Semester");

                printf("--------------------------------------------------------\n");

                for (int i = 0; i < studentCount; i++)
                {
                    printf("%-8d %-15s %-12s %-10d\n",

                           students[i].roll,
                           students[i].name,
                           students[i].department,
                           students[i].semester);
                           printf("%.1f %.1f %.1f %.1f %.1f\n",
                                  students[i].marks[0],
                                  students[i].marks[1],
                                  students[i].marks[2],
                                  students[i].marks[3],
                                  students[i].marks[4]);
                                  printf("GPA: %.2f\n",students[i].gpa);

                }
            }
        }
/*search student*/
    if (choice == 3)
    {
        int searchChoice;
        int searchRoll;
        char searchName[50];
        int found = 0;
        printf("\n===== Search Student =====\n");
        printf("1. Search by Roll Number\n");
        printf("2. Search by Name\n");
        printf("Enter your choice: ");
        scanf("%d", &searchChoice);

        if(searchChoice == 1)
        {
            printf("\nEnter Roll Number: ");
            scanf("%d", &searchRoll);
            for(int i=0; i< studentCount; i++)
            {
                if(students[i].roll == searchRoll)
                {
                    printf("\nStudent Found!\n");
                    printf("Roll: %d\n", students[i].roll);
                    printf("Name: %s\n", students[i].name);
                    printf("Department: %s\n", students[i].department);
                    printf("Semester: %d\n", students[i].semester);
                    printf("Marks: ");
                    for(int j = 0; j < SUBJECTS; j++)
                    {
                        printf("%.1f",students[i].marks[j]);
                    }
                    printf("\n");
                    printf("GPA: %.2f\n",students[i].gpa);

                    found = 1;
                    break;
                }


            }
        }
        else if(searchChoice == 2)
        {
            printf("\nEnter Student Name: ");
            scanf("%s",searchName);
            for (int i = 0 ;i < studentCount; i++)
            {
                if(strcmp(students[i].name, searchName) == 0)
                {
                    printf("\nStudent Found!\n");
                    printf("Roll: %d\n", students[i].roll);
                    printf("Name: %s\n", students[i].name);
                    printf("Department: %s\n", students[i].department);
                    printf("Semester: %d\n", students[i].semester);
                    printf("Marks: ");

for(int j = 0; j < SUBJECTS; j++)
{
    printf("%.1f ", students[i].marks[j]);
}

printf("\n");
printf("GPA: %.2f\n", students[i].gpa);

                    found = 1;
                    break;

                }
            }
        }
        else
        {
            printf("\nInvalid Search Choice!\n");
            found = 1;

        }
        if(found == 0)
        {
            printf("\nStudent Not Found!\n");
        }
    }
    /*Update Student */
    if (choice == 4)
    {
        int updateRoll;
        int found = 0;
         printf("\nEnter Roll Number to Update: ");
         scanf("%d", &updateRoll);
         for(int i = 0; i < studentCount; i++)
         {
             if(students[i].roll == updateRoll)
             {
                 printf("\nStudent Found!\n");
                 printf("Enter New Name: ");
                 scanf("%s", students[i].name);
                 printf("Enter New Department: ");
                 scanf("%s",students[i].department);
                 printf("Enter New Semester: ");
                 scanf("%d", &students[i].semester);
                 printf("\nEnter New Marks for 5 Subjects:\n");
                 for (int j = 0; j < SUBJECTS; j++)
{
    do
    {
        printf("Subject %d Marks: ", j + 1);
        scanf("%f", &students[i].marks[j]);

        if (students[i].marks[j] < 0 ||
            students[i].marks[j] > 100)
        {
            printf("Invalid marks! Please enter marks between 0 and 100.\n");
        }

    } while (students[i].marks[j] < 0 ||
             students[i].marks[j] > 100);
}

/* Recalculate GPA */
students[i].gpa = calculateGPA(students[i].marks);

printf("\nStudent Updated Successfully!\n");
printf("New GPA: %.2f\n", students[i].gpa);
                   /* Save Updated Data to File */
file = fopen("students.dat", "wb");

if (file != NULL)
{
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(struct Student), studentCount, file);

    fclose(file);
}


                 found = 1;
                 break;
             }
         }
         if (found == 0)
         {
             printf("\nStudent Not Found!\n");
         }
    }
    /*Delete Student*/

if (choice == 5)
{
    int deleteRoll;
    int found = 0;

    printf("\nEnter Roll Number to Delete: ");
    scanf("%d", &deleteRoll);

    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].roll == deleteRoll)
        {
            int confirm;

            printf("\nStudent Found!\n");
            printf("Roll: %d\n", students[i].roll);
            printf("Name: %s\n", students[i].name);

            printf("\nAre you sure you want to delete this student?\n");
            printf("1. Yes\n");
            printf("2. No\n");
            printf("Enter your choice: ");
            scanf("%d", &confirm);

            if (confirm == 1)
            {
                for (int j = i; j < studentCount - 1; j++)
                {
                    students[j] = students[j + 1];
                }

                studentCount--;

                /* Save Deleted Data to File */
                file = fopen("students.dat", "wb");

                if (file != NULL)
                {
                    fwrite(&studentCount, sizeof(int), 1, file);
                    fwrite(students, sizeof(struct Student), studentCount, file);

                    fclose(file);
                }

                printf("\nStudent Deleted Successfully!\n");
            }
            else if (confirm == 2)
            {
                printf("\nDeletion Cancelled.\n");
            }
            else
            {
                printf("\nInvalid Choice! Deletion Cancelled.\n");
            }

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("\nStudent Not Found!\n");
    }
}


           /* Performance Analytics */
if (choice == 6)
{
    if (studentCount == 0)
    {
        printf("\nNo student records found!\n");
    }
    else
    {
        float totalGPA = 0;
        float highestMarks = 0;
        float lowestMarks = 100;
        int passedStudents = 0;
        int failedStudents = 0;

        for (int i = 0; i < studentCount; i++)
        {
            totalGPA = totalGPA + students[i].gpa;

            for (int j = 0; j < SUBJECTS; j++)
            {
                if (students[i].marks[j] > highestMarks)
                {
                    highestMarks = students[i].marks[j];
                }

                if (students[i].marks[j] < lowestMarks)
                {
                    lowestMarks = students[i].marks[j];
                }
            }

            if (students[i].gpa >= 2.00)
            {
                passedStudents++;
            }
            else
            {
                failedStudents++;
            }
        }

        float averageGPA = totalGPA / studentCount;
        float passPercentage =
            ((float)passedStudents / studentCount) * 100;
        float failPercentage =
            ((float)failedStudents / studentCount) * 100;

        printf("\n========== PERFORMANCE ANALYTICS ==========\n");
        printf("Total Students   : %d\n", studentCount);
        printf("Average GPA      : %.2f\n", averageGPA);
        printf("Highest Marks    : %.2f\n", highestMarks);
        printf("Lowest Marks     : %.2f\n", lowestMarks);
        printf("Passed Students  : %d\n", passedStudents);
        printf("Failed Students  : %d\n", failedStudents);
        printf("Pass Percentage  : %.2f%%\n", passPercentage);
        printf("Fail Percentage  : %.2f%%\n", failPercentage);
    }
}
/* Low GPA Warning List */
if (choice == 7)
{
    int warningFound = 0;

    printf("\n========== LOW GPA WARNING LIST ==========\n");

    printf("%-8s %-15s %-10s\n",
           "Roll", "Name", "GPA");

    printf("------------------------------------------\n");

    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].gpa < 2.00)
        {
            printf("%-8d %-15s %-10.2f\n",
                   students[i].roll,
                   students[i].name,
                   students[i].gpa);

            warningFound = 1;
        }
    }

    if (warningFound == 0)
    {
        printf("No student has GPA below 2.00.\n");
         }
}
    }

       return 0;
}




