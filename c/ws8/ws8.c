/*********************************
submitter : rozaline kozly
reviewer: Steve :)
worksheet: 8 (serialized structs)
version: 2
date: 1- dec-2025
**********************************/
#include <stdio.h>            /* printf */
#include <string.h>           /* strcpy */
#include <sys/types.h>        /* ssize_t */
#include <assert.h>            /* assert */


#define NAME_LEN 30           /*  max length of a first name / last name */

/* structs */
typedef struct
{
	float history;
	float literature;
	float geography;
}humanitarian_ty;

typedef struct
{
	float math;
	float physics;
	float chemistry;
}real_ty;

typedef struct
{
    float sports;
    humanitarian_ty humanities;
    real_ty real;
} grades_ty;

typedef struct
{
    char first_name[NAME_LEN];
    char last_name[NAME_LEN];
    grades_ty grades;
} student_ty;

/* ----------------------------------------- functions declarations -----------------------------------------------------*/
int ReadStudent(FILE *fp, student_ty *s);
int WriteStudent(FILE *fp, student_ty *s);

int ReadGrades(FILE *fp, grades_ty *g);
int WriteGrades(FILE *fp, grades_ty *g);

int ReadHumanitarian(FILE *fp, humanitarian_ty *h);
int WriteHumanitarian(FILE *fp, humanitarian_ty *h);

int ReadReal(FILE *fp, real_ty *r);
int WriteReal(FILE *fp, real_ty *r);

/* API */
int SaveStudentToFile( char *fn, student_ty *s);
int LoadStudentFromFile( char *fn, student_ty *s);
/* testing function */
ssize_t CheckIfEqual(student_ty* s1, student_ty* s2);


/* implementation */
int WriteStudent(FILE *fp,  student_ty *s)
{
    fwrite(s->first_name, NAME_LEN, 1, fp) ;
    fwrite(s->last_name, NAME_LEN, 1, fp);

    /* serialize nested struct */
    WriteGrades(fp, &s->grades);

    return 0;
}

int WriteGrades(FILE *fp,  grades_ty *g)
{
    fwrite(&g->sports, sizeof(float), 1, fp);
    /* nested struct */
    WriteHumanitarian(fp, &g-> humanities);
    WriteReal(fp, &g-> real);

    return 0;
}

int WriteHumanitarian(FILE *fp, humanitarian_ty *h)
{
    fwrite(&h->history, sizeof(float), 1, fp);
    fwrite(&h->literature, sizeof(float), 1, fp);
    fwrite(&h->geography, sizeof(float), 1, fp);
    
    return 0;
}

int WriteReal(FILE *fp, real_ty *r)
{
       fwrite(&r->math, sizeof(float), 1, fp);
       fwrite(&r->physics, sizeof(float), 1, fp);
       fwrite(&r->chemistry, sizeof(float), 1, fp);
       return 0;
}



/* ---------------- READ FUNCTIONS ---------------- */

int ReadGrades(FILE *fp,  grades_ty *g)
{
    if (fread(&g->sports, sizeof(float), 1, fp) != 1) return -1;
    /* nested struct */
    if (ReadHumanitarian(fp, &g-> humanities) != 0) return -1;
    if ( ReadReal(fp, &g-> real) != 0) return -1;

    return 0;
}

int ReadHumanitarian(FILE *fp, humanitarian_ty *h)
{
   if (fread(&h->history, sizeof(float), 1, fp) != 1) return -1;
   if (fread(&h->literature, sizeof(float), 1, fp) != 1) return -1;
   if (fread(&h->geography, sizeof(float), 1, fp) != 1) return -1;
    
    return 0;
}

int ReadReal(FILE *fp, real_ty *r)
{
       if (fread(&r->math, sizeof(float), 1, fp) != 1) return -1;
       if (fread(&r->physics, sizeof(float), 1, fp) != 1) return -1;
       if  (fread(&r->chemistry, sizeof(float), 1, fp) != 1) return -1;
       return 0;
}


int ReadStudent(FILE *fp, student_ty *s)
{
    if(fread(s->first_name, NAME_LEN, 1, fp) == 0) return -1;
    if(fread(s->last_name, NAME_LEN, 1, fp) == 0) return -1;

    /* deserialize nested struct */
    if( ReadGrades(fp, &s->grades) != 0) return -1;
    return 0;
}

/* ---------------- SAVE/LOAD WRAPPERS ---------------- */

int SaveStudentToFile( char *fn, student_ty *s)
{
    FILE *fp = fopen(fn, "wb");
    
    if (!fp) return 1;
    WriteStudent(fp, s);
    fclose(fp);
    return 0;
}

int LoadStudentFromFile( char *fn, student_ty *s)
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

    s1.grades.humanities.history = 95.5f;
    s1.grades.humanities.literature = 95.5f;
     s1.grades.humanities.geography = 95.5f;
    
    s1.grades.real.math = 88.0f;
    s1.grades.real.physics = 88.0f;
    s1.grades.real.chemistry = 88.0f;
    s1.grades.sports = 77.2f;
    
    SaveStudentToFile("student.bin", &s1);
    LoadStudentFromFile("student.bin", &s2);
    
    /* testing */
    return CheckIfEqual(&s1, &s2);
}


ssize_t CheckIfEqual(student_ty* s1, student_ty* s2)   /* #include <sys/types.h> */
{
    if (strcmp(s1 -> first_name,s2 -> first_name) != 0 )  printf("FAILED first name s1 = %s s2 = %s\n", s1 -> first_name, s2 -> first_name);
    if (strcmp(s1 -> last_name, s2 -> last_name ) != 0)  printf("FAILED last name\n");
    if ( s1 -> grades.humanities.history != s2 -> grades.humanities.history )  printf("FAILED human grade ur %f supposed %f \n",s1 -> grades.humanities.history, 
    s2 -> grades.humanities.history);
    if ( s1 -> grades.real.math != s2 -> grades.real.math )  printf("FAILED real grade\n");
    if ( s1 -> grades.sports != s2 -> grades.sports )  printf("FAILED sports grade\n");
    
    return 0;
}

