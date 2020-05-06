#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int studentID;
    char name[10];
};

int main(){
    int *studentID;


    studentID = (int *)malloc(sizeof(int) * 3); 
    // return type이 void이므로 type casting 필요

    if(studentID == NULL){
	fprintf(stderr, "Out of memory!!\n");
	exit(-1);
    }

    studentID[0] = 12345;
    studentID[1] = 23456;
    studentID[2] = 34567;

    printf("%d\n", studentID[0]);
    printf("%d\n", studentID[1]);
    printf("%d\n", studentID[2]);   

    free(studentID);

    struct student *pStudent;

    pStudent = (struct student *)malloc(sizeof(struct student));

    if(pStudent == NULL){
        fprintf(stderr, "Out of memory!!\n");
        exit(-1);
    }

    pStudent->studentID = 98765;
    (*pStudent).studentID = 98765;

    printf("%d\n", pStudent->studentID);
    printf("%d\n", (*pStudent).studentID);

    strcpy(pStudent->name, "PNU CSE");
    printf("%s\n", pStudent->name);

    free(pStudent);

    struct student *studentlist;

    // looks like struct student studentlist[10]; on the stack fixed size
    // Array on the heap Dynamic size : Why? You can increase / decrease  additional array size using realloc()

    studentlist = (struct student *)malloc(sizeof(struct student) * 10);

    if(studentlist == NULL){
        fprintf(stderr, "Out of memory!!\n");
        exit(-1);
    }

    studentlist[0].studentID = 7897979;
    strcpy(studentlist[0].name, "Jico");

    printf("%d : %s\n", studentlist[0].studentID, studentlist[0].name);

    free(studentlist);

    return 0;
