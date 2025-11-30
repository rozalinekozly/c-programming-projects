/*********************************
submitter : rozaline kozly
reviewer:
worksheet: 8 (serialized structs)
version: 1
date: 30-nov-2025
**********************************/
#include <stdio.h>            /* printf */
#include <string.h>          /* strcpy */
#include <sys/types.h>       /* ssize_t */
#define NAME_LEN 30           /*  max length of a first name / last name */

/* structs */

typedef struct
{
    float humanities;
    float real;
    float sports;
    float math;
    float literature;
    float physics;
} grades_ty;

typedef struct
{
    char first_name[NAME_LEN];
    char last_name[NAME_LEN];
    grades_ty grades;
} student_ty;

/* ----------------------------------------- functions declarations -----------------------------------------------------*/
int WriteGrades(FILE *fp, const grades_ty *g);
int ReadGrades(FILE *fp, grades_ty *g);
int ReadStudent(FILE *fp, student_ty *s);
int SaveStudentToFile(const char *fn, const student_ty *s);
int LoadStudentFromFile(const char *fn, student_ty *s);
/* testing function */
ssize_t CheckIfEqual(student_ty* s1, student_ty* s2);

/* ----------------------------------------- functions definitions -----------------------------------------------------*/
/* ---------------- WRITE FUNCTIONS ---------------- */
int WriteGrades(FILE *fp, const grades_ty *g)
{
    fwrite(&g->humanities, sizeof(float), 1, fp);
    fwrite(&g->real, sizeof(float), 1, fp);
    fwrite(&g->sports, sizeof(float), 1, fp);
    fwrite(&g->math, sizeof(float), 1, fp);
    fwrite(&g->literature, sizeof(float), 1, fp);
    fwrite(&g->physics, sizeof(float), 1, fp);

    return 0;
}

int WriteStudent(FILE *fp, const student_ty *s)
{
    fwrite(s->first_name, NAME_LEN, 1, fp);
    fwrite(s->last_name, NAME_LEN, 1, fp);

    /* serialize nested struct */
    WriteGrades(fp, &s->grades);

    return 0;
}

/* ---------------- READ FUNCTIONS ---------------- */

int ReadGrades(FILE *fp, grades_ty *g)
{
    if(fread(&g->humanities, sizeof(float), 1, fp) == 0) return -1;
    if(fread(&g->real, sizeof(float), 1, fp) == 0) return -1;
    if(fread(&g->sports, sizeof(float), 1, fp) == 0) return -1;
    if(fread(&g->math, sizeof(float), 1, fp) == 0) return -1;
    if(fread(&g->literature, sizeof(float), 1, fp) == 0) return -1;
    if(fread(&g->physics, sizeof(float), 1, fp) == 0) return -1;

return 0;
}

int ReadStudent(FILE *fp, student_ty *s)
{
    if(fread(s->first_name, NAME_LEN, 1, fp) == 0) return -1;
    if(fread(s->last_name, NAME_LEN, 1, fp) == 0) return -1;

    /* deserialize nested struct */
    ReadGrades(fp, &s->grades);
    return 0;
}

/* ---------------- SAVE/LOAD WRAPPERS ---------------- */

int SaveStudentToFile(const char *fn, const student_ty *s)
{
    FILE *fp = fopen(fn, "wb");
    
    if (!fp) return 1;
    WriteStudent(fp, s);
    fclose(fp);
    return 0;
}

int LoadStudentFromFile(const char *fn, student_ty *s)
{
    FILE *fp = fopen(fn, "rb");

    if (!fp) return 1;
    ReadStudent(fp, s);
    fclose(fp);
    return 0;
}

int main(void)
{
    student_ty s1;    /* manually constructed student */
    student_ty s2;      /* to check if correctly loaded and interpreted (the test) */


/* define a setter function ! */
    /* constructing a sample student */
    strcpy(s1.first_name, "Rozaline");   
    strcpy(s1.last_name, "Kozly");

    s1.grades.humanities = 95.5f;
    s1.grades.real = 88.0f;
    s1.grades.sports = 77.2f;
    s1.grades.math = 99.0f;
    s1.grades.literature = 87.4f;
    s1.grades.physics = 91.1f;

    SaveStudentToFile("student.bin", &s1);
    LoadStudentFromFile("student.bin", &s2);
    
    /* testing */
    return CheckIfEqual(&s1, &s2);
}


ssize_t CheckIfEqual(student_ty* s1, student_ty* s2)   /* #include <sys/types.h> */
{
    if(strcmp(s1 -> first_name,s2 -> first_name) != 0 )  printf("FAILED first name s1 = %s s2 = %s\n", s1 -> first_name, s2 -> first_name);
    if(strcmp(s1 -> last_name, s2 -> last_name ) != 0)  printf("FAILED last name\n");
    if( s1 -> grades.humanities != s2 -> grades.humanities )  printf("FAILED human gr\n");
    if( s1 -> grades.real != s2 -> grades.real )  printf("FAILED real grad\n");
    if( s1 -> grades.sports != s2 -> grades.sports )  printf("FAILED sports grade\n");
    if( s1 -> grades.physics != s2 -> grades.physics)  printf("FAILED physics grade\n");
    
    return 0;
}

