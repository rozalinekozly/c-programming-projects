/*********************************
submitter : rozaline kozly
reviewer: Steve :)
worksheet: 8 (serialized structs)
version: 2
date: 1- dec-2025
**********************************/
#include <stdio.h>                                /*    printf      */
#include <string.h>                               /*    strcpy      */
#include <sys/types.h>                            /*    ssize_t     */
#include <assert.h>                               /*    assert      */

#define NAME_LEN                                          30           /*  max length of a first name / last name */
#define FLOAT_SIZE                                        sizeof(float)
typedef enum 
{
  SUCCESS = 0,
  FAILED_DESERIALIZE = 1,
  FAILED_SERIALIZE = 2,
  FAILED_OPENING_FILE = 3,
  FAILED_CLOSING_FILE = 4
  
}return_status;

/* structs */
/* humanitarian courses grades struct */
typedef struct
{
	float history;
	float literature;
	float geography;
}humanitarian_ty;

/* real courses grades struct */
typedef struct
{
	float math;
	float physics;
	float chemistry;
}real_ty;

/* grades struct */
typedef struct
{
    float sports;
    humanitarian_ty humanities;
    real_ty real;
} grades_ty;

/* student struct */
typedef struct
{
    char first_name[NAME_LEN];
    char last_name[NAME_LEN];
    grades_ty grades;
} student_ty;

/* ------ functions declarations ------*/
/* serialize functions   */
return_status ReadStudent(FILE*, student_ty*); 
return_status ReadGrades(FILE*, grades_ty*);
return_status ReadHumanitarian(FILE*, humanitarian_ty*);
return_status ReadReal(FILE*, real_ty*);

/* deserialize functions */
return_status WriteStudent(FILE*, student_ty*);
return_status WriteGrades(FILE*, grades_ty*);
return_status WriteHumanitarian(FILE*, humanitarian_ty*);
return_status WriteReal(FILE*, real_ty*);

/*---- API ----*/
return_status SaveStudentToFile(char*, student_ty*);
return_status LoadStudentFromFile(char*, student_ty*);

/* testing function */
void TestStudents();
ssize_t CheckIfEqual(student_ty*, student_ty*);

/* implementation */
/* ---------------- WRITE FUNCTIONS ---------------- */
return_status WriteStudent(FILE* file_ptr,  student_ty* student_instance)
{
    if (fwrite(student_instance -> first_name, NAME_LEN, 1, file_ptr) != 1) return FAILED_SERIALIZE;
    if (fwrite(student_instance -> last_name, NAME_LEN, 1, file_ptr) != 1) return FAILED_SERIALIZE;
    return WriteGrades(file_ptr, &student_instance -> grades);
}

return_status WriteGrades(FILE* file_ptr,  grades_ty* grade_instance)
{
     if (fwrite(&grade_instance->sports, FLOAT_SIZE, 1, file_ptr) != 1) return FAILED_SERIALIZE;
     if (WriteHumanitarian(file_ptr, &grade_instance-> humanities) != SUCCESS) return FAILED_SERIALIZE;
     if (WriteReal(file_ptr, &grade_instance-> real) != SUCCESS) return FAILED_SERIALIZE;
     
     return SUCCESS;
}

return_status WriteHumanitarian(FILE* file_ptr, humanitarian_ty* humanitarian_instance)
{
    if (fwrite(&humanitarian_instance -> history, FLOAT_SIZE, 1, file_ptr) != 1) return FAILED_SERIALIZE;
    if (fwrite(&humanitarian_instance -> literature, FLOAT_SIZE, 1, file_ptr) != 1) return FAILED_SERIALIZE;
    if (fwrite(&humanitarian_instance -> geography, FLOAT_SIZE, 1, file_ptr) != 1) return FAILED_SERIALIZE;
    
    return SUCCESS;
}

return_status WriteReal(FILE* file_ptr, real_ty* real_instance)
{
       if (fwrite(&real_instance -> math, FLOAT_SIZE, 1, file_ptr) != 1) return FAILED_SERIALIZE;
       if (fwrite(&real_instance -> physics, FLOAT_SIZE, 1, file_ptr) != 1) return FAILED_SERIALIZE;
       if (fwrite(&real_instance -> chemistry, FLOAT_SIZE, 1, file_ptr) != 1) return FAILED_SERIALIZE;
       
       return SUCCESS;
}

/* ---------------- READ FUNCTIONS ---------------- */

return_status ReadGrades(FILE* file_ptr,  grades_ty* grade_instance)
{
    if (fread(&grade_instance -> sports, FLOAT_SIZE, 1, file_ptr) != 1) return FAILED_DESERIALIZE;
    if (ReadHumanitarian(file_ptr, &grade_instance -> humanities) != SUCCESS) return FAILED_DESERIALIZE;
    if (ReadReal(file_ptr, &grade_instance -> real) != SUCCESS) return FAILED_DESERIALIZE;

    return SUCCESS;
}

return_status ReadHumanitarian(FILE* file_ptr, humanitarian_ty* humanitarian_instance)
{
   if (fread(&humanitarian_instance -> history, FLOAT_SIZE, 1, file_ptr) != 1) return FAILED_DESERIALIZE;
   if (fread(&humanitarian_instance -> literature,FLOAT_SIZE, 1, file_ptr) != 1) return FAILED_DESERIALIZE;
   if (fread(&humanitarian_instance -> geography, FLOAT_SIZE, 1, file_ptr) != 1) return FAILED_DESERIALIZE;
    
    return SUCCESS;
}

return_status ReadReal(FILE* file_ptr, real_ty* real_instance)
{
       if (fread(&real_instance -> math, FLOAT_SIZE, 1, file_ptr) != 1) return FAILED_DESERIALIZE;
       if (fread(&real_instance -> physics, FLOAT_SIZE, 1, file_ptr) != 1) return FAILED_DESERIALIZE;
       if (fread(&real_instance -> chemistry, FLOAT_SIZE, 1, file_ptr) != 1) return FAILED_DESERIALIZE;
       
       return SUCCESS;
}


return_status ReadStudent(FILE* file_ptr, student_ty* student_instance)
{
    if(fread(student_instance -> first_name, NAME_LEN, 1, file_ptr) == 0) return FAILED_DESERIALIZE;
    if(fread(student_instance -> last_name, NAME_LEN, 1, file_ptr) == 0) return FAILED_DESERIALIZE;
    if( ReadGrades(file_ptr, &student_instance -> grades) != SUCCESS) return FAILED_DESERIALIZE;
    
    return SUCCESS;
}

/*---------------- SAVE/LOAD WRAPPERS (API implementation) ----------------*/

return_status SaveStudentToFile(char* file_name, student_ty* student_instance)
{
    FILE* file_ptr = fopen(file_name, "wb"); 
    
    if (NULL == file_ptr) return FAILED_OPENING_FILE;
    if (WriteStudent(file_ptr, student_instance) != SUCCESS) return FAILED_SERIALIZE;
    if (fclose(file_ptr) != SUCCESS) return FAILED_CLOSING_FILE;
    
    return SUCCESS;
}

return_status LoadStudentFromFile(char* file_name, student_ty* student_instance)
{
    FILE* file_ptr = fopen(file_name, "rb");

    if (NULL == file_ptr) return FAILED_OPENING_FILE;
    if (ReadStudent(file_ptr, student_instance) != SUCCESS) return FAILED_DESERIALIZE;
    if (fclose(file_ptr) != SUCCESS) return FAILED_CLOSING_FILE;
    
    return SUCCESS;
}

int main(void)
{
    TestStudents();
    return 0;     
}


ssize_t CheckIfEqual(student_ty* s1, student_ty* s2)   /* #include <sys/types.h> */
{
    if(strcmp(s1 -> first_name,s2 -> first_name) != 0 )  printf("FAILED first name s1 = %s s2 = %s\n", s1 -> first_name, s2 -> first_name);
    if(strcmp(s1 -> last_name, s2 -> last_name ) != 0)  printf("FAILED last name\n");
    if( s1 -> grades.humanities.history != s2 -> grades.humanities.history )  printf("FAILED human grade ur %f supposed %f \n",s1 -> grades.humanities.history, 
    s2 -> grades.humanities.history);
    if( s1 -> grades.real.math != s2 -> grades.real.math )  printf("FAILED real grade\n");
    if( s1 -> grades.sports != s2 -> grades.sports )  printf("FAILED sports grade\n");
    
    return 0;
}

void TestStudents()
{
    student_ty s1;        /* manually constructed student */
     student_ty s2;      /* to check if correctly loaded and interpreted (the test) */

    /* constructing a sample student */
    strcpy(s1.first_name, "Rozaline");   
    strcpy(s1.last_name, "Kozly");

    s1.grades.humanities.history = 60.25;
    s1.grades.humanities.literature = 18.3695;
     s1.grades.humanities.geography = 14.3325;
    
    s1.grades.real.math = 88.01;
    s1.grades.real.physics = 88.08;
    s1.grades.real.chemistry = 1.001;
    s1.grades.sports = 100.0;
    
    SaveStudentToFile("student.o", &s1);
    LoadStudentFromFile("student.o", &s2);
    
    /* testing */
    if (CheckIfEqual(&s1, &s2) != SUCCESS) 
    {
        printf("FAILED TEST :(\n");
        return;
    }
    
    printf("PASSED TEST!\n");
    return;
}
