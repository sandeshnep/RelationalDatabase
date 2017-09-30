#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define SNAPSIZE 67
#define CSGSIZE 67
#define CPSIZE 67
#define CDHSIZE 67
#define CRSIZE 67

int booleanDelete = 0;
int booleanCPDelete = 0;
int boolean21 = 0;
int Q21aIDcounter=0;
int Q21aID[20];
char *Q22aCourse[30];
int Q22aCoursecounter = 0;
int CDHMatch = 0;
int booleanSNAPFound = 0;
int booleanCSGSelect = 0;
int booleanCRDH = 0;
int boolean22a = 0;

//delcaration of tuples and various data rows

//--------------------------------------------------------------SNAP RELATION------------------------------------------------------------------
//StudentId-Name-Address-Phone Table
typedef struct SNAPTuple *SNAPLIST;
struct SNAPTuple {   //THE TUPLES
    int StudentId;
    char Name[30];
    char Address[50];
    char Phone[8];
    SNAPLIST next;
};
typedef SNAPLIST SNAPTABLE[SNAPSIZE]; //HASHTABLES that store a TUPLELIST // has buckets
SNAPTABLE SNAPTABLE1;
SNAPTABLE SNAPTABLE2;
SNAPTABLE SNAPTABLE3;
SNAPTABLE COPYSNAPTABLE;

struct SNAPTuple temporaryTuple;



//Hash Function
int SNAPhashf(int key){
    return key % SNAPSIZE;
}

//Insert Hashtable for SNAP(1)
int insertSNAP(int Iid, char Iname[30], char Iaddress[50], char Iphone[8]){
    struct SNAPTuple* temp= (struct SNAPTuple*) malloc (sizeof(struct SNAPTuple));
    temp->StudentId = Iid;
    strcpy(temp->Name, Iname);
    strcpy(temp->Address, Iaddress);
    strcpy(temp->Phone, Iphone);
    temp->next = NULL;

    //IMPLEMENTING THE HASH FUNCTION
    //StudentID is the hash domain, used as the key for the hash function
    int index = SNAPhashf(Iid);

    if(SNAPTABLE1[index]!=NULL)temp->next = SNAPTABLE1[index];
    SNAPTABLE1[index] = temp;
}

//Insert Hashtable for SNAP(S)
int insertSNAP2(int Iid, char Iname[30], char Iaddress[50], char Iphone[8]){
    struct SNAPTuple* temp= (struct SNAPTuple*) malloc (sizeof(struct SNAPTuple));
    temp->StudentId = Iid;
    strcpy(temp->Name, Iname);
    strcpy(temp->Address, Iaddress);
    strcpy(temp->Phone, Iphone);
    temp->next = NULL;

    //IMPLEMENTING THE HASH FUNCTION
    //StudentID is the hash domain, used as the key for the hash function
    int index = SNAPhashf(Iid);

    if(SNAPTABLE2[index]!=NULL)temp->next = SNAPTABLE2[index];
    SNAPTABLE2[index] = temp;
}

//Insert Hashtable for SNAP (Result)
int insertSNAP3(int Iid, char Iname[30], char Iaddress[50], char Iphone[8]){
    struct SNAPTuple* temp= (struct SNAPTuple*) malloc (sizeof(struct SNAPTuple));
    temp->StudentId = Iid;
    strcpy(temp->Name, Iname);
    strcpy(temp->Address, Iaddress);
    strcpy(temp->Phone, Iphone);
    temp->next = NULL;

    //IMPLEMENTING THE HASH FUNCTION
    //StudentID is the hash domain, used as the key for the hash function
    int index = SNAPhashf(Iid);

    if(SNAPTABLE3[index]!=NULL)temp->next = SNAPTABLE3[index];
    SNAPTABLE3[index] = temp;
}



int printSNAPTuple(struct SNAPTuple t){
    printf(" StudentID: %d, Name: %s, Address: %s, Phone: %s \n", t.StudentId, t.Name, t.Address, t.Phone);

    booleanSNAPFound = 1;
}


//--THIS delete individual Tupple. The delete function is integrated into the LOOKUP function, it is called from THERE.
int deleteSNAPTuple(SNAPLIST tempTuple, int counter, int Lindex){
    printf("Deleting the Student \n");
    //removing if there is only one item in the list
    if(counter== 1 & tempTuple->next==NULL){
        SNAPTABLE1[Lindex]=NULL;
    }//removing middle item
    else if(tempTuple->next!=NULL){
        tempTuple->StudentId = tempTuple->next->StudentId;
        strcpy(tempTuple->Name, tempTuple->next->Name);
        strcpy(tempTuple->Address, tempTuple->next->Address);
        strcpy(tempTuple->Phone, tempTuple->next->Phone);
        tempTuple->next = tempTuple->next->next;
    }//removing the last tuple that is not the first tuple
    else if (tempTuple->next==NULL) {
        printf("removing the last item-----\n");
        //Step 1: Copy the SnapList before the last entry onto a new List
        struct SNAPTuple* tempTuple2;
        tempTuple2 = SNAPTABLE1[Lindex];

        while(tempTuple2->next!=NULL) {
            struct SNAPTuple* copytemp =  (struct SNAPTuple*) malloc (sizeof(struct SNAPTuple));

            copytemp->StudentId = tempTuple2->StudentId;
            strcpy(copytemp->Name, tempTuple2->Name);
            strcpy(copytemp->Address, tempTuple2->Address);
            strcpy(copytemp->Phone, tempTuple2->Phone);
            copytemp->next = NULL;

            if(COPYSNAPTABLE[0]!=NULL) copytemp->next = COPYSNAPTABLE[0];
            COPYSNAPTABLE[0]= copytemp;
            tempTuple2 = tempTuple2->next;
        }
        SNAPTABLE1[Lindex]= COPYSNAPTABLE[0];
        free(tempTuple2);
        COPYSNAPTABLE[0] = NULL;
    }
}



//Look up the tuples based on some specification
int lookupSNAP(int Lid, char Lname[30], char Laddress[50], char Lphone[8]){
    booleanSNAPFound = 0;

    //Case 1: All Values are given as the lookup parameters, returns true or false
    if(Lid!= 42 && strcmp(Lname, "*")!= 0 && strcmp(Laddress, "*")!= 0 && strcmp(Lphone, "*")!= 0 ){
        // printf("Case 1\n");
        //Finding the right tuple with the key as Lid
        //lookup index
        int Lindex = SNAPhashf(Lid);
        SNAPLIST tempTuple = SNAPTABLE1[Lindex];

        int booleanFound = 0; //0 = no and 1= Yes
        int counter = 0;

        while(tempTuple!=NULL){
            counter++;
            int increment = 0;
            if(tempTuple->StudentId==Lid && strcmp(Lname, tempTuple->Name)==0 && strcmp(Laddress, tempTuple->Address)==0 && strcmp(Lphone, tempTuple->Phone)==0){
                booleanFound = 1;
                printf("Student found on Index: %d\n" , Lindex);
                printSNAPTuple(*tempTuple);

                if(booleanDelete==1){
                    deleteSNAPTuple(tempTuple, counter, Lindex);
                    increment = 0;
                }

            }
            if(increment==0){
                tempTuple = tempTuple->next;}
        }
        if(booleanFound==0){
            // printf("Student Not Found \n");
        }


    }
    else
    {
        //Case 2: One Value is given
        //Case 2.1 ID is given
        if(Lid!= 42 ){
            // printf("Case 2.1\n");
            //Finding the right tuple with the key as Lid
            //lookup index
            int Lindex = SNAPhashf(Lid);
            SNAPLIST tempTuple = SNAPTABLE1[Lindex];

            int booleanFound = 0;
            int counter = 0;

            while(tempTuple!=NULL){
                counter++;
                int increment = 0;
                if(tempTuple->StudentId==Lid && (strcmp(Lname, "*")==0 || strcmp(Lname, tempTuple->Name)==0) && (strcmp(Laddress, "*")==0 || strcmp(Laddress, tempTuple->Address)==0) && (strcmp(Lphone, "*")==0 || strcmp(Lphone, tempTuple->Phone)==0) ){
                    booleanFound = 1;
                    printf("Student found on Index: %d\n" , Lindex);
                    printSNAPTuple(*tempTuple);
                    if(booleanDelete==1){
                        deleteSNAPTuple(tempTuple, counter, Lindex);
                        increment = 0;
                    }
                }
                if(increment==0){
                    tempTuple = tempTuple->next;}
            }
            if(booleanFound==0){
                //  printf("Student Not Found \n");
            }


        }
        else if(strcmp(Lname, "*")!= 0 ) { //Student Name is Given, Case 2.2
            // printf("Case 2.2\n");

            for (int i = 0; i < SNAPSIZE; i++) {
                int booleanFound = 0;
                int counter = 0;
                SNAPLIST tempTuple = SNAPTABLE1[i];
                while (tempTuple != NULL) {
                    counter++;
                    int increment = 0;
                    if ((tempTuple->StudentId == Lid || Lid == 42) && (strcmp(Lname, tempTuple->Name) == 0) &&
                        (strcmp(Laddress, "*") == 0 || strcmp(Laddress, tempTuple->Address) == 0) &&
                        (strcmp(Lphone, "*") == 0 || strcmp(Lphone, tempTuple->Phone) == 0)) {
                        booleanFound = 1;
                        printf("Student found on Index: %d\n", i);
                        Q21aID[Q21aIDcounter] = tempTuple->StudentId;
                        Q21aIDcounter++;
                        printSNAPTuple(*tempTuple);
                        if(booleanDelete==1){
                            deleteSNAPTuple(tempTuple, counter, i);
                            increment = 0;
                        }
                    }
                    if(increment==0){
                        tempTuple = tempTuple->next;}
                }
                /*if (booleanFound==0) {
                    printf("Student Not Found on index : %d\n", i);
                }*/

            }
        }
        else if(strcmp(Laddress, "*")!= 0 ){ //Student Address is Given, Case 2.3
            // printf("Case 2.3\n");

            for(int i = 0; i<SNAPSIZE; i++){
                int booleanFound = 0;
                int counter = 0;
                SNAPLIST tempTuple = SNAPTABLE1[i];
                while(tempTuple!=NULL){
                    counter++;
                    int increment = 0;
                    if((tempTuple->StudentId==Lid || Lid==42) && (strcmp(Lname, "*")==0 || strcmp(Lname, tempTuple->Name)==0) && (strcmp(Laddress, tempTuple->Address)==0) && (strcmp(Lphone, "*")==0 || strcmp(Lphone, tempTuple->Phone)==0) ){
                        booleanFound = 1;
                        printf("Student found on Index: %d\n" , i);
                        printSNAPTuple(*tempTuple);
                        if(booleanDelete==1){
                            deleteSNAPTuple(tempTuple, counter, i);
                            increment = 0;
                        }
                    }
                    if(increment==0){
                        tempTuple = tempTuple->next;}
                }
                /*if(booleanFound == 0){
                    printf("Student Not Found on index : %d\n", i);
                }*/

            }


        }
        else if(strcmp(Lphone, "*")!= 0 ){ //Student Phone is Given, Case 2.4
            //  printf("Case 2.4\n");

            for(int i = 0; i<SNAPSIZE; i++){
                int booleanFound = 0;
                int counter = 0;
                SNAPLIST tempTuple = SNAPTABLE1[i];
                while(tempTuple!=NULL){
                    counter++;
                    int increment = 0;
                    if((tempTuple->StudentId==Lid || Lid==42) && (strcmp(Lname, "*")==0 || strcmp(Lname, tempTuple->Name)==0) && (strcmp(Laddress, "*")==0 || strcmp(Laddress, tempTuple->Address)==0) && (strcmp(Lphone, tempTuple->Phone)==0) ){
                        booleanFound = 1;
                        printf("Student found on Index: %d\n" , i);
                        printSNAPTuple(*tempTuple);
                        if(booleanDelete==1){
                            deleteSNAPTuple(tempTuple, counter, i);
                            increment = 0;
                        }
                    }
                    if(increment==0){
                        tempTuple = tempTuple->next;}tempTuple = tempTuple->next;
                }
                /*if(booleanFound == 0 ){
                    printf("Student Not Found on index : %d\n", i);
                }*/

            }

        }
        else{
            //  printf("Student not found. \n");
        }

    }

}

int printSNAPTABLE(){
    printf("-----------------------------------------------------------------------");
    printf("\nPrinting the SNAP table 1: \n");
    for(int i = 0; i<SNAPSIZE; i++){
        SNAPLIST tempTuple = SNAPTABLE1[i];
        while (tempTuple!=NULL){
            //   printf("Index: %d\n", i);
            printf(" StudentID: %d, Name: %s, Address: %s, Phone: %s \n", tempTuple->StudentId, tempTuple->Name, tempTuple->Address, tempTuple->Phone);
            tempTuple=tempTuple->next;
        }
    }
}



int printSNAPTABLE2(){
    printf("-----------------------------------------------------------------------");
    printf("\nPrinting the SNAP table 2: \n");
    for(int i = 0; i<SNAPSIZE; i++){
        SNAPLIST tempTuple = SNAPTABLE2[i];
        while (tempTuple!=NULL){
            //   printf("Index: %d\n", i);
            printf(" StudentID: %d, Name: %s, Address: %s, Phone: %s \n", tempTuple->StudentId, tempTuple->Name, tempTuple->Address, tempTuple->Phone);
            tempTuple=tempTuple->next;
        }
    }
}


int printSNAPTABLE3(){
    printf("-----------------------------------------------------------------------");
    printf("\nPrinting the SNAP table 3: \n");
    for(int i = 0; i<SNAPSIZE; i++){
        SNAPLIST tempTuple = SNAPTABLE3[i];
        while (tempTuple!=NULL){
            //   printf("Index: %d\n", i);
            printf(" StudentID: %d, Name: %s, Address: %s, Phone: %s \n", tempTuple->StudentId, tempTuple->Name, tempTuple->Address, tempTuple->Phone);
            tempTuple=tempTuple->next;
        }
    }
}



//  Deletes based on the specification of the tuples-------------------------------------------------------------------------------------------------------
int deleteSNAP(int Lid, char Lname[30], char Laddress[50], char Lphone[8]){
    booleanDelete = 1;
    lookupSNAP(Lid, Lname, Laddress, Lphone);
    booleanDelete = 0;
}
//----------------------------------------------------------------------END SNAP TABLE----------------------------------------------------------






//---------------------------------------------------------------------COURSE PREREQ TABLE-----------------------------------------------------------

typedef struct CPTuple *CPLIST;
struct CPTuple{
    char Course[30];
    char Prereq[30];
    CPLIST next;
};

typedef CPLIST CPTABLE[CPSIZE]; //HASHTABLES that store a TUPLELIST // has buckets
CPTABLE CPTABLE1;
CPTABLE COPYCPTABLE;

int CPhashf(int key){
    return key % CPSIZE;
}


int insertCP (char Icourse[30], char Iprereq[30]){

    struct CPTuple* temp= (struct CPTuple*) malloc (sizeof(struct CPTuple));

    strcpy(temp->Course,Icourse);
    strcpy(temp->Prereq,Iprereq);

    temp->next = NULL;

    //IMPLEMENTING THE HASH FUNCTION
    //StudentID is the hash domain, used as the key for the hash function
    int CPkey = ((int)Icourse[30] + (int)Iprereq[30]);
    int index = CPhashf( CPkey );

    //printf("index: %d", index);

    if(CPTABLE1[index]!=NULL)temp->next = CPTABLE1[index];
    CPTABLE1[index] = temp;

}


int printCPTuple(struct CPTuple t){
    printf("Course: %s, Prereq: %s \n", t.Course, t.Prereq);
}



//--THIS delete individual Tupple. The delete function is integrated into the LOOKUP function, it is called from THERE.
int deleteCPTuple(CPLIST tempTuple, int counter, int Lindex){
    printf("Deleting the Tuple \n");
    //removing if there is only one item in the list
    if(counter== 1 & tempTuple->next==NULL){
        CPTABLE1[Lindex]=NULL;
    }//removing middle item
    else if(tempTuple->next!=NULL){

        strcpy(tempTuple->Course, tempTuple->next->Course);
        strcpy(tempTuple->Prereq, tempTuple->next->Prereq);
        tempTuple->next = tempTuple->next->next;
    }//removing the last tuple that is not the first tuple
    else if (tempTuple->next==NULL) {
        printf("removing the last item-----\n");
        //Step 1: Copy the CPList before the last entry onto a new List
        struct CPTuple* tempTuple2;
        tempTuple2 = CPTABLE1[Lindex];

        while(tempTuple2->next!=NULL) {
            struct CPTuple* copytemp =  (struct CPTuple*) malloc (sizeof(struct CPTuple));

            strcpy(copytemp->Course, tempTuple2->Course);
            strcpy(copytemp->Prereq, tempTuple2->Prereq);
            copytemp->next = NULL;

            if(COPYCPTABLE[0]!=NULL) copytemp->next = COPYCPTABLE[0];
            COPYCPTABLE[0]= copytemp;
            tempTuple2 = tempTuple2->next;
        }
        CPTABLE1[Lindex]= COPYCPTABLE[0];
        free(tempTuple2);
        COPYCPTABLE[0] = NULL;

    }
}



//Look up the tuples based on some specification
int lookupCP(char Lcourse[30], char Lprereq[30]){

    //Case 1: All Values are given as the lookup parameters, returns true or false
    if(strcmp(Lcourse, "*")!= 0 && strcmp(Lprereq, "*")!= 0 ){
        // printf("Case 1\n");
        //Finding the right tuple with the key as Lid
        //lookup index
        int CPkey = ((int)Lcourse[30] + (int)Lprereq[30]);
        int Lindex = CPhashf( CPkey );

        CPLIST tempTuple = CPTABLE1[Lindex];

        int booleanFound = 0; //0 = no and 1= Yes
        int counter = 0;

        while(tempTuple!=NULL){
            counter++;
            int increment = 0;
            if(strcmp(Lcourse, tempTuple->Course)==0 && strcmp(Lprereq, tempTuple->Prereq)==0){
                booleanFound = 1;
                printf("Student found on Index: %d\n" , Lindex);
                printCPTuple(*tempTuple);
                if(booleanCPDelete==1){
                    deleteCPTuple(tempTuple, counter, Lindex);
                    increment = 0;
                }

            }
            if(increment==0){
                tempTuple = tempTuple->next;}
        }
        if(booleanFound==0){
            //  printf("Student Not Found \n");
        }


    }
    else
    {
        //Case 2: One Value is given
        //Case 2.1 Course is given
        if(strcmp(Lcourse, "*")!= 0  ){
            // printf("Case 2.1\n");
            //Finding the right tuple with the key as Lid
            //lookup index
            for (int i = 0; i < CPSIZE; i++) {
                int booleanFound = 0;
                int counter = 0;
                CPLIST tempTuple = CPTABLE1[i];
                while (tempTuple != NULL) {
                    counter++;
                    int increment = 0;
                    if ((strcmp(Lcourse, tempTuple->Course) == 0) &&
                        (strcmp(Lprereq, "*") == 0 || strcmp(Lprereq, tempTuple->Prereq) == 0)) {
                        booleanFound = 1;
                        //  printf("Item found on Index: %d\n", i);
                        printCPTuple(*tempTuple);
                        if(booleanCPDelete==1){
                            deleteCPTuple(tempTuple, counter, i);
                            increment = 0;
                        }
                    }
                    if(increment==0){
                        tempTuple = tempTuple->next;}
                }
                /* if (booleanFound==0) {
                     printf("Item Not Found on index : %d\n", i);
                 }*/

            }

        }
        else if(strcmp(Lprereq, "*")!= 0 ) { //Prereq is Given, Case 2.2
            //  printf("Case 2.2\n");

            for (int i = 0; i < CPSIZE; i++) {
                int booleanFound = 0;
                int counter = 0;
                CPLIST tempTuple = CPTABLE1[i];
                while (tempTuple != NULL) {
                    counter++;
                    int increment = 0;
                    if ((strcmp(Lprereq, tempTuple->Prereq) == 0) &&
                        (strcmp(Lcourse, "*") == 0 || strcmp(Lcourse, tempTuple->Course) == 0)) {
                        booleanFound = 1;
                        //  printf("Item found on Index: %d\n", i);
                        printCPTuple(*tempTuple);
                        if(booleanCPDelete==1){
                            deleteCPTuple(tempTuple, counter, i);
                            increment = 0;
                        }
                    }
                    if(increment==0){
                        tempTuple = tempTuple->next;}
                }
                /*if (booleanFound==0) {
                    printf("Item Not Found on index : %d\n", i);
                }*/

            }

        }
        else{
            printf("Item not found. \n");
        }

    }

}




int printCPTABLE(){
    printf("Printing the CP Table ------------------------------------------------------\n");
    for(int i = 0; i<CPSIZE; i++){
        CPLIST tempTuple = CPTABLE1[i];
        while (tempTuple!=NULL){
            // printf("Index: %d\n", i);
            printf(" Course: %s, Prereq: %s\n" , tempTuple->Course, tempTuple->Prereq);
            tempTuple=tempTuple->next;
        }
    }
}




//  Deletes based on the specification of the tuples-------------------------------------------------------------------------------------------------------
int deleteCP(char Lcourse[30], char Lprereq[30]){
    booleanCPDelete = 1;
    lookupCP(Lcourse, Lprereq);
    booleanCPDelete = 0;
}

//---------------------------------------------------------------------END COURSE PREREQ TABLE-------------------------





//------------------------------------------------------------------------COURSE-DAY-HOUR---------------------------

typedef struct CDHTuple *CDHLIST;
struct CDHTuple{
    char Course[30];
    char Day[30];
    char Hour[30];
    CDHLIST next;
};

typedef CDHLIST CDHTABLE[CDHSIZE]; //HASHTABLES that store a TUPLELIST // has buckets
CDHTABLE CDHTABLE1;
CDHTABLE COPYCDHTABLE;

unsigned int CDHhashf(unsigned int key){
    return key % CDHSIZE;
}


int insertCDH (char Icourse[30], char Iday[30], char Ihour[30]){

    struct CDHTuple* temp= (struct CDHTuple*) malloc (sizeof(struct CDHTuple));


    strcpy(temp->Course,Icourse);
    strcpy(temp->Day,Iday);
    strcpy(temp->Hour,Ihour);

    temp->next = NULL;

    //IMPLEMENTING THE HASH FUNCTION
    //StudentID is the hash domain, used as the key for the hash function
    unsigned int CDHkey = ((unsigned int) Icourse[30] + (unsigned int) Iday[30] + (unsigned int) Ihour[30]);
    unsigned int index = CDHhashf( CDHkey );
    //printf("index: %d", index);

    if(CDHTABLE1[index]!=NULL)temp->next = CDHTABLE1[index];
    CDHTABLE1[index] = temp;

}

int printCDHTuple(struct CDHTuple t){
    printf("Course: %s, Day: %s, Hour: %s \n", t.Course, t.Day, t.Hour);

}


//--THIS delete individual Tupple. The delete function is integrated into the LOOKUP function, it is called from THERE.
int deleteCDHTuple(CDHLIST tempTuple, int counter, int Lindex){
    printf("Deleting the Tuple \n");
    //removing if there is only one item in the list
    if(counter== 1 & tempTuple->next==NULL){
        CDHTABLE1[Lindex]=NULL;
    }//removing middle item
    else if(tempTuple->next!=NULL){
        strcpy(tempTuple->Course, tempTuple->next->Course);
        strcpy(tempTuple->Day, tempTuple->next->Day);
        strcpy(tempTuple->Hour, tempTuple->next->Hour);
        tempTuple->next = tempTuple->next->next;
    }//removing the last tuple that is not the first tuple
    else if (tempTuple->next==NULL) {
        printf("removing the last item-----\n");
        //Step 1: Copy the CDHList before the last entry onto a new List
        struct CDHTuple* tempTuple2;
        tempTuple2 = CDHTABLE1[Lindex];

        while(tempTuple2->next!=NULL) {
            struct CDHTuple* copytemp =  (struct CDHTuple*) malloc (sizeof(struct CDHTuple));

            strcpy(copytemp->Course, tempTuple2->Course);
            strcpy(copytemp->Day, tempTuple2->Day);
            strcpy(copytemp->Hour, tempTuple2->Hour);
            copytemp->next = NULL;

            if(COPYCDHTABLE[0]!=NULL) copytemp->next = COPYCDHTABLE[0];
            COPYCDHTABLE[0]= copytemp;
            tempTuple2 = tempTuple2->next;
        }
        CDHTABLE1[Lindex]= COPYCDHTABLE[0];
        free(tempTuple2);
        COPYCDHTABLE[0] = NULL;

    }
}



//Look up the tuples based on some specification
int lookupCDH(char Lcourse[30], char Lday[30], char Lhour[30]){

    //Case 1: All Values are given as the lookup parameters, returns true or false
    if(strcmp(Lcourse, "*")!= 0 && strcmp(Lday, "*")!= 0 && strcmp(Lhour, "*")!= 0 ){
        //  printf("Case 1\n");
        //Finding the right tuple with the key as Lid
        //lookup index
        int CDHkey = ((int)Lcourse[30] + (int)Lday[30] + (int) Lhour[30]);
        int Lindex = CDHhashf( CDHkey );

        CDHLIST tempTuple = CDHTABLE1[Lindex];

        int booleanFound = 0; //0 = no and 1= Yes
        int counter = 0;

        while(tempTuple!=NULL){
            counter++;
            int increment = 0;
            if(strcmp(Lcourse, tempTuple->Course)==0 && strcmp(Lday, tempTuple->Day)==0 && strcmp(Lhour, tempTuple->Hour)==0){
                booleanFound = 1;
                //  printf("Item found on Index: %d\n" , Lindex);
                CDHMatch = 1;
                printCDHTuple(*tempTuple);
                if(booleanDelete==1){
                    deleteCDHTuple(tempTuple, counter, Lindex);
                    increment = 0;
                }

            }
            if(increment==0){
                tempTuple = tempTuple->next;}
        }
        if(booleanFound==0){
            // printf("Student Not Found \n");
        }


    }
    else
    {
        //Case 2: One Value is given
        //Case 2.1 Course is given
        if(strcmp(Lcourse, "*")!= 0  ){
            //  printf("Case 2.1\n");
            //Finding the right tuple with the key as Lid
            //lookup index
            for (int i = 0; i < CDHSIZE; i++) {
                int booleanFound = 0;
                int counter = 0;
                CDHLIST tempTuple = CDHTABLE1[i];
                while (tempTuple != NULL) {
                    counter++;
                    int increment = 0;
                    if ((strcmp(Lcourse, tempTuple->Course) == 0) &&
                        (strcmp(Lday, "*") == 0 || strcmp(Lday, tempTuple->Day) == 0) && (strcmp(Lhour, "*") == 0 || strcmp(Lhour, tempTuple->Hour) == 0)) {
                        booleanFound = 1;
                        //   printf("Item found on Index: %d\n", i);
                        printCDHTuple(*tempTuple);
                        if(booleanDelete==1){
                            deleteCDHTuple(tempTuple, counter, i);
                            increment = 0;
                        }
                    }
                    if(increment==0){
                        tempTuple = tempTuple->next;}
                }
                /*if (booleanFound==0) {
                    printf("Item Not Found on index : %d\n", i);
                }
*/
            }

        }
        else if(strcmp(Lday, "*")!= 0 ) { //DAY is Given, Case 2.2
            // printf("Case 2.2\n");

            for (int i = 0; i < CDHSIZE; i++) {
                int booleanFound = 0;
                int counter = 0;
                CDHLIST tempTuple = CDHTABLE1[i];
                while (tempTuple != NULL) {
                    counter++;
                    int increment = 0;
                    if ((strcmp(Lday, tempTuple->Day) == 0) &&
                        (strcmp(Lcourse, "*") == 0 || strcmp(Lcourse, tempTuple->Course) == 0)&&(strcmp(Lhour, "*") == 0 || strcmp(Lhour, tempTuple->Hour))) {
                        booleanFound = 1;
                        //   printf("Item found on Index: %d\n", i);
                        printCDHTuple(*tempTuple);
                        if(booleanDelete==1){
                            deleteCDHTuple(tempTuple, counter, i);
                            increment = 0;
                        }
                    }
                    if(increment==0){
                        tempTuple = tempTuple->next;}
                }
                /*  if (booleanFound==0) {
                      printf("Item Not Found on index : %d\n", i);
                  }*/

            }

        }
        else if(strcmp(Lhour, "*")!= 0 ) { //HOUR is Given, Case 2.3
            // printf("Case 2.3\n");

            for (int i = 0; i < CDHSIZE; i++) {
                int booleanFound = 0;
                int counter = 0;
                CDHLIST tempTuple = CDHTABLE1[i];
                while (tempTuple != NULL) {
                    counter++;
                    int increment = 0;
                    if ((strcmp(Lhour, tempTuple->Hour) == 0) &&
                        (strcmp(Lcourse, "*") == 0 || strcmp(Lcourse, tempTuple->Course) == 0)&&(strcmp(Lday, "*") == 0 || strcmp(Lday, tempTuple->Day))) {
                        booleanFound = 1;
                        //   printf("Item found on Index: %d\n", i);
                        printCDHTuple(*tempTuple);
                        if(booleanDelete==1){
                            deleteCDHTuple(tempTuple, counter, i);
                            increment = 0;
                        }
                    }
                    if(increment==0){
                        tempTuple = tempTuple->next;}
                }
                /*if (booleanFound==0) {
                    printf("Item Not Found on index : %d\n", i);
                }*/

            }

        }
        else{
            printf("Item not found. \n");
        }

    }

}

int printCDHTABLE(){
    printf("Printing CDH Table---------------------------------------------------------------------------\n");
    for(int i = 0; i<CDHSIZE; i++){
        CDHLIST tempTuple = CDHTABLE1[i];
        while (tempTuple!=NULL){
            //    printf("Index: %d\n", i);
            printf(" Course: %s, Day: %s, Hour: %s \n" , tempTuple-> Course , tempTuple-> Day, tempTuple -> Hour);
            tempTuple=tempTuple->next;
        }
    }
}


//  Deletes based on the specification of the tuples-------------------------------------------------------------------------------------------------------
int deleteCDH(char Lcourse[30], char Lday[30], char Lhour[30]){
    booleanDelete = 1;
    lookupCDH(Lcourse, Lday, Lhour);
    booleanDelete = 0;
}

//------------------------------------------------------------------------END COURSE-DAY-HOUR-----------------------




//----------------------------------------------------------------------------COURSE ROOM----------------------------

typedef struct CRTuple *CRLIST;
struct CRTuple{
    char Course[30];
    char Room[30];
    CRLIST next;
};

typedef CRLIST CRTABLE[CRSIZE]; //HASHTABLES that store a TUPLELIST // has buckets
CRTABLE CRTABLE1;
CRTABLE COPYCRTABLE;


int CRhashf(int key){
    return key % CRSIZE;
}


int insertCR (char Icourse[30], char Iroom[30]){

    struct CRTuple* temp= (struct CRTuple*) malloc (sizeof(struct CRTuple));

    strcpy(temp->Course,Icourse);
    strcpy(temp->Room,Iroom);

    temp->next = NULL;

    //IMPLEMENTING THE HASH FUNCTION
    //StudentID is the hash domain, used as the key for the hash function

    int CRkey = (int) Icourse[0];

    int index = CRhashf( CRkey );
    //printf("index: %d", index);

    if(CRTABLE1[index]!=NULL)temp->next = CRTABLE1[index];
    CRTABLE1[index] = temp;

}


int printCRTuple(struct CRTuple t){
    printf("Course: %s, Room: %s \n", t.Course, t.Room);
}


//--THIS delete individual Tupple. The delete function is integrated into the LOOKUP function, it is called from THERE.
int deleteCRTuple(CRLIST tempTuple, int counter, int Lindex){
    printf("Deleting the Tuple \n");
    //removing if there is only one item in the list
    if(counter== 1 & tempTuple->next==NULL){
        CRTABLE1[Lindex]=NULL;
    }//removing middle item
    else if(tempTuple->next!=NULL){
        strcpy(tempTuple->Course, tempTuple->next->Course);
        strcpy(tempTuple->Room, tempTuple->next->Room);
        tempTuple->next = tempTuple->next->next;
    }//removing the last tuple that is not the first tuple
    else if (tempTuple->next==NULL) {
        printf("removing the last item-----\n");
        //Step 1: Copy the CRList before the last entry onto a new List
        struct CRTuple* tempTuple2;
        tempTuple2 = CRTABLE1[Lindex];

        while(tempTuple2->next!=NULL) {
            struct CRTuple* copytemp =  (struct CRTuple*) malloc (sizeof(struct CRTuple));

            strcpy(copytemp->Course, tempTuple2->Course);
            strcpy(copytemp->Room, tempTuple2->Room);
            copytemp->next = NULL;

            if(COPYCRTABLE[0]!=NULL) copytemp->next = COPYCRTABLE[0];
            COPYCRTABLE[0]= copytemp;
            tempTuple2 = tempTuple2->next;
        }
        CRTABLE1[Lindex]= COPYCRTABLE[0];
        free(tempTuple2);
        COPYCRTABLE[0] = NULL;
    }
}




//Look up the tuples based on some specification
int lookupCR(char Lcourse[30], char Lroom[30]){

    //Case 1: All Values are given as the lookup parameters, returns true or false
    if(strcmp(Lcourse, "*")!= 0 && strcmp(Lroom, "*")!= 0 ){
        // printf("Case 1\n");
        //Finding the right tuple with the key as Lid
        //lookup index
        int CRkey = ((int)Lcourse[0] + (int)Lroom[0]);
        int Lindex = CRhashf( CRkey );

        CRLIST tempTuple = CRTABLE1[Lindex];

        int booleanFound = 0; //0 = no and 1= Yes
        int counter = 0;

        while(tempTuple!=NULL){
            counter++;
            int increment = 0;
            if(strcmp(Lcourse, tempTuple->Course)==0 && strcmp(Lroom, tempTuple->Room)==0){
                booleanFound = 1;
                printf("Student found on Index: %d\n" , Lindex);
                printCRTuple(*tempTuple);
                if(booleanDelete==1){
                    deleteCRTuple(tempTuple, counter, Lindex);
                    increment = 0;
                }

            }
            if(increment==0){
                tempTuple = tempTuple->next;}
        }
        if(booleanFound==0){
            // printf("Student Not Found \n");
        }


    }
    else
    {
        //Case 2: One Value is given
        //Case 2.1 Course is given
        if(strcmp(Lcourse, "*")!= 0  ){
            //  printf("Case 2.1\n");
            //Finding the right tuple with the key as Lid
            //lookup index
            for (int i = 0; i < CRSIZE; i++) {
                int booleanFound = 0;
                int counter = 0;
                CRLIST tempTuple = CRTABLE1[i];
                while (tempTuple != NULL) {
                    counter++;
                    int increment = 0;
                    if ((strcmp(Lcourse, tempTuple->Course) == 0) &&
                        (strcmp(Lroom, "*") == 0 || strcmp(Lroom, tempTuple->Room) == 0)) {
                        booleanFound = 1;
                        //   printf("Item found on Index: %d\n", i);
                        printCRTuple(*tempTuple);
                        if(booleanDelete==1){
                            deleteCRTuple(tempTuple, counter, i);
                            increment = 0;
                        }
                    }
                    if(increment==0){
                        tempTuple = tempTuple->next;}
                }
                /* if (booleanFound==0) {
                     printf("Item Not Found on index : %d\n", i);
                 }*/

            }

        }
        else if(strcmp(Lroom, "*")!= 0 ) { //ROOM is Given, Case 2.2
            // printf("Case 2.2\n");

            for (int i = 0; i < CRSIZE; i++) {
                int booleanFound = 0;
                int counter = 0;
                CRLIST tempTuple = CRTABLE1[i];
                while (tempTuple != NULL) {
                    counter++;
                    int increment = 0;
                    if ((strcmp(Lroom, tempTuple->Room) == 0) &&
                        (strcmp(Lcourse, "*") == 0 || strcmp(Lcourse, tempTuple->Course) == 0)) {
                        booleanFound = 1;
                        //   printf("Item found on Index: %d\n", i);
                        printCRTuple(*tempTuple);
                        if(booleanDelete==1){
                            deleteCRTuple(tempTuple, counter, i);
                            increment = 0;
                        }
                    }
                    if(increment==0){
                        tempTuple = tempTuple->next;}
                }
                /*if (booleanFound==0) {
                    printf("Item Not Found on index : %d\n", i);
                }*/

            }

        }
        else{
            printf("Item not found. \n");
        }

    }

}



int printCRTABLE(){
    printf("Printing the CR table---------------------------------------------------------------------\n");
    for(int i = 0; i<CRSIZE; i++){
        CRLIST tempTuple = CRTABLE1[i];
        while (tempTuple!=NULL){
            //   printf("Index: %d\n", i);
            printf(" Course: %s, Room: %s \n" , tempTuple -> Course , tempTuple ->Room );
            tempTuple=tempTuple->next;
        }
    }
}


//  Deletes based on the specification of the tuples-------------------------------------------------------------------------------------------------------
int deleteCR(char Lcourse[30], char Lroom[30]){
    booleanDelete = 1;
    lookupCR(Lcourse, Lroom);
    booleanDelete = 0;
}


//---------------------------------------------------------------------------END COURSE ROOM--------------------------------------------------------------------


//--------------------------------------------------------------------------COURSE STUDENT GRADE---------------------------------


typedef struct CSGTuple *CSGLIST;
struct  CSGTuple{
    char Course[30];
    int StudentId;
    char Grade[30];

    CSGLIST next;
};

typedef CSGLIST CSGTABLE[CSGSIZE];
CSGTABLE CSGTABLE1;
CSGTABLE CSGTABLE2;
CSGTABLE COPYCSGTABLE;


int CSGhashf (int key){
    return key % CSGSIZE;
}


int insertCSG (char Icourse[30], int IstudentId, char Igrade[30] ){

    struct CSGTuple* temp= (struct CSGTuple*) malloc (sizeof(struct CSGTuple));

    strcpy(temp->Course,Icourse);
    temp->StudentId=IstudentId;
    strcpy(temp->Grade,Igrade);

    temp->next = NULL;

    //IMPLEMENTING THE HASH FUNCTION
    //StudentID is the hash domain, used as the key for the hash function

    int key = ((int) Icourse[0] + IstudentId );
    int CSGkey = key;

    int index = CSGhashf(CSGkey);

    if(CSGTABLE1[index]!=NULL)temp->next = CSGTABLE1[index];
    CSGTABLE1[index] = temp;

}


int insertCSG2 (char Icourse[30], int IstudentId, char Igrade[30] ){

    struct CSGTuple* temp= (struct CSGTuple*) malloc (sizeof(struct CSGTuple));

    strcpy(temp->Course,Icourse);
    temp->StudentId=IstudentId;
    strcpy(temp->Grade,Igrade);

    temp->next = NULL;

    //IMPLEMENTING THE HASH FUNCTION
    //StudentID is the hash domain, used as the key for the hash function

    int key = ((int) Icourse[0] + IstudentId );
    int CSGkey = key;

    int index = CSGhashf(CSGkey);

    if(CSGTABLE2[index]!=NULL)temp->next = CSGTABLE2[index];
    CSGTABLE2[index] = temp;

}
int printCSGTuple(struct CSGTuple t){
    printf("Course: %s, StudentID: %d, Grade: %s \n", t.Course, t.StudentId, t.Grade);
    if(booleanCSGSelect ==1){
        insertCSG2(t.Course, t.StudentId, t.Grade);
    }
}


//--THIS delete individual Tupple. The delete function is integrated into the LOOKUP function, it is called from THERE.
int deleteCSGTuple(CSGLIST tempTuple, int counter, int Lindex){
    printf("Deleting the Tuple \n");
    //removing if there is only one item in the list
    if(counter== 1 & tempTuple->next==NULL){
        CSGTABLE1[Lindex]=NULL;
    }//removing middle item
    else if(tempTuple->next!=NULL){
        strcpy(tempTuple->Course, tempTuple->next->Course);
        tempTuple->StudentId = tempTuple->next->StudentId;
        strcpy(tempTuple->Grade, tempTuple->next->Grade);
        tempTuple->next = tempTuple->next->next;
    }//removing the last tuple that is not the first tuple
    else if (tempTuple->next==NULL) {
        printf("removing the last item-----\n");
        //Step 1: Copy the CSGList before the last entry onto a new List
        struct CSGTuple* tempTuple2;
        tempTuple2 = CSGTABLE1[Lindex];

        while(tempTuple2->next!=NULL) {
            struct CSGTuple* copytemp =  (struct CSGTuple*) malloc (sizeof(struct CSGTuple));

            strcpy(copytemp->Course, tempTuple2->Course);
            copytemp->StudentId= tempTuple2->StudentId;
            strcpy(copytemp->Grade, tempTuple2->Grade);
            copytemp->next = NULL;

            if(COPYCSGTABLE[0]!=NULL) copytemp->next = COPYCSGTABLE[0];
            COPYCSGTABLE[0]= copytemp;
            tempTuple2 = tempTuple2->next;
        }
        CSGTABLE1[Lindex]= COPYCSGTABLE[0];
        free(tempTuple2);
        COPYCSGTABLE[0] = NULL;

    }
}


//Look up the tuples based on some specification
int lookupCSG(char Lcourse[30], int LstudentId, char Lgrade[30]){

    //Case 1: All Values are given as the lookup parameters, returns true or false
    if(strcmp(Lcourse, "*")!= 0 && LstudentId != 42 && strcmp(Lgrade, "*")!= 0 ){
        //  printf("Case 1\n");
        //Finding the right tuple with the key as Lid
        //lookup index
        int CSGkey = ((int)Lcourse[0] + (int)LstudentId );
        int Lindex = CSGhashf( CSGkey );

        CSGLIST tempTuple = CSGTABLE1[Lindex];

        int booleanFound = 0; //0 = no and 1= Yes
        int counter = 0;

        while(tempTuple!=NULL){
            counter++;
            int increment = 0;
            if(strcmp(Lcourse, tempTuple->Course)==0 && LstudentId== tempTuple->StudentId && strcmp(Lgrade, tempTuple->Grade)==0){
                booleanFound = 1;
                printf("Student found on Index: %d\n" , Lindex);
                printCSGTuple(*tempTuple);
                if(booleanDelete==1){
                    deleteCSGTuple(tempTuple, counter, Lindex);
                    increment = 0;
                }

            }
            if(increment==0){
                tempTuple = tempTuple->next;}
        }
        if(booleanFound==0){
            printf("Student Not Found \n");
        }


    }
    else
    {
        //Case 2: One Value is given
        //Case 2.1 Course is given
        if(strcmp(Lcourse, "*")!= 0  ){
            //  printf("Case 2.1\n");
            //Finding the right tuple with the key as Lid
            //lookup index
            for (int i = 0; i < CSGSIZE; i++) {
                int booleanFound = 0;
                int counter = 0;
                CSGLIST tempTuple = CSGTABLE1[i];
                while (tempTuple != NULL) {
                    counter++;
                    int increment = 0;
                    if ((strcmp(Lcourse, tempTuple->Course) == 0) &&
                        (LstudentId == 42 || LstudentId== tempTuple->StudentId) && (strcmp(Lgrade, "*") == 0 || strcmp(Lgrade, tempTuple->Grade) == 0)) {
                        booleanFound = 1;
                        //  printf("Item found on Index: %d\n", i);
                        printCSGTuple(*tempTuple);
                        if(booleanDelete==1){
                            deleteCSGTuple(tempTuple, counter, i);
                            increment = 0;
                        }
                    }
                    if(increment==0){
                        tempTuple = tempTuple->next;}
                }
                /* if (booleanFound==0) {
                     printf("Item Not Found on index : %d\n", i);
                 }*/

            }

        }
        else if(LstudentId != 42 ) { //STUDENTID is Given, Case 2.2
            //   printf("Case 2.2\n");

            for (int i = 0; i < CSGSIZE; i++) {
                int booleanFound = 0;
                int counter = 0;
                CSGLIST tempTuple = CSGTABLE1[i];
                while (tempTuple != NULL) {
                    counter++;
                    int increment = 0;
                    if (LstudentId == tempTuple->StudentId &&
                        (strcmp(Lcourse, "*") == 0 || strcmp(Lcourse, tempTuple->Course) == 0)&&(strcmp(Lgrade, "*") == 0 || strcmp(Lgrade, tempTuple->Grade))) {
                        booleanFound = 1;
                        //   printf("Item found on Index: %d\n", i);
                        if(boolean22a==1){

                        }
                        Q22aCourse[Q22aCoursecounter] = tempTuple->Course;
                        Q22aCoursecounter++;
                        printCSGTuple(*tempTuple);
                        if(booleanDelete==1){
                            deleteCSGTuple(tempTuple, counter, i);
                            increment = 0;
                        }
                    }
                    if(increment==0){
                        tempTuple = tempTuple->next;}
                }
                /*if (booleanFound==0) {
                    printf("Item Not Found on index : %d\n", i);
                }*/

            }

        }
        else if(strcmp(Lgrade, "*")!= 0 ) { //GRADE is Given, Case 2.3
            //  printf("Case 2.3\n");

            for (int i = 0; i < CSGSIZE; i++) {
                int booleanFound = 0;
                int counter = 0;
                CSGLIST tempTuple = CSGTABLE1[i];
                while (tempTuple != NULL) {
                    counter++;
                    int increment = 0;
                    if ((strcmp(Lgrade, tempTuple->Grade) == 0) &&
                        (strcmp(Lcourse, "*") == 0 || strcmp(Lcourse, tempTuple->Course) == 0)&&(LstudentId == 42 || LstudentId== tempTuple->StudentId)) {
                        booleanFound = 1;
                        //  printf("Item found on Index: %d\n", i);
                        printCSGTuple(*tempTuple);
                        if(booleanDelete==1){
                            deleteCSGTuple(tempTuple, counter, i);
                            increment = 0;
                        }
                    }
                    if(increment==0){
                        tempTuple = tempTuple->next;}
                }
                /*if (booleanFound==0) {
                    printf("Item Not Found on index : %d\n", i);
                }*/

            }

        }
        else{
            printf("Item not found. \n");
        }

    }

}


int printCSGTABLE(){
    printf("Printing CSG Table-----------------------------------------------------\n");
    for(int i = 0; i<CSGSIZE; i++){
        CSGLIST tempTuple = CSGTABLE1[i];
        while (tempTuple!=NULL){
            //   printf("Index: %d\n", i);
            printf(" Course: %s, Student ID: %d, Grade: %s \n" , tempTuple-> Course , tempTuple->StudentId, tempTuple ->Grade);
            tempTuple=tempTuple->next;
        }
    }
}


int printCSGTABLE2(){
    printf("Printing CSG Table-----------------------------------------------------\n");
    for(int i = 0; i<CSGSIZE; i++){
        CSGLIST tempTuple = CSGTABLE2[i];
        while (tempTuple!=NULL){
            //   printf("Index: %d\n", i);
            printf(" Course: %s, Student ID: %d, Grade: %s \n" , tempTuple-> Course , tempTuple->StudentId, tempTuple ->Grade);
            tempTuple=tempTuple->next;
        }
    }
}


//  Deletes based on the specification of the tuples-------------------------------------------------------------------------------------------------------
int deleteCSG(char Lcourse[30], int LstudentId, char Lgrade[30]){
    booleanDelete = 1;
    lookupCSG(Lcourse, LstudentId, Lgrade);
    booleanDelete = 0;
}

//--------------------------------------------------------------------------END COURSE STUDENT GRADE---------------------------------------------------------



//-----------------------------------------------------------------READING FROM THE FILE AND SAVING TO THE FILE---------------------------------------------

void save_to_file() {
    printf("****SAVING TO FILE 'Database.txt' ******\n");

    FILE *fp;
    fp = fopen("./Database.txt", "w+");
    if (fp == NULL) {
        perror("Can't open file");
    } else {

        int i;
        for (i = 0; i < 67; i++) {
            struct SNAPTuple *current = *(SNAPTABLE1 + i);
            while (current) {
                fprintf(fp, "SNAP\t%d\t%s\t%s\t%s\n", current->StudentId, current->Name, current->Address,
                        current->Phone);
                current = current->next;
            }
        }

        for (i = 0; i < 67; i++) {
            struct CSGTuple *current = *(CSGTABLE1 + i);
            while (current) {
                fprintf(fp, "CSG\t%s\t%d\t%s\n", current->Course, current->StudentId, current->Grade);
                current = current->next;
            }
        }

        for (i = 0; i < 67; i++) {
            struct CPTuple *current = *(CPTABLE1 + i);
            while (current) {
                fprintf(fp, "CP\t%s\t%s\n", current->Course, current->Prereq);
                current = current->next;
            }
        }


        for (i = 0; i < 67; i++) {
            struct CDHTuple *current = *(CDHTABLE1 + i);
            while (current) {
                fprintf(fp, "CDH\t%s\t%s\t%s\n", current->Course, current->Day, current->Hour);
                current = current->next;
            }
        }

        for (i = 0; i < 67; i++) {
            struct CRTuple *current = *(CRTABLE1 + i);
            while (current) {
                fprintf(fp, "CR\t%s\t%s\n", current->Course, current->Room);
                current = current->next;
            }
        }
    }
    fclose(fp);
}



//Need to change Code // ***

void insertFromFile(char *filename) {
    printf("****INSERTING FROM FILE****** \n");
    FILE *newfile;
    newfile = fopen(filename, "r");
    if (newfile == NULL) {
        perror("The file can't be opened");
    } else {
        char buffer[100];
        int length;

        while (fgets(buffer, 100, newfile)) {

            int length = strlen(buffer);
            char short_buffer[length];
            strcpy(short_buffer, buffer);
            if (short_buffer[length - 1] != '\0') short_buffer[length - 1] = '\0';


            char *result = strtok(short_buffer, "\t");

            if (strcmp(result, "SNAP") == 0) {

                int studentId = atoi(strtok(NULL, "\t"));
                char *name = strtok(NULL, "\t");
                char *address = strtok(NULL, "\t");
                char *phone = strtok(NULL, "\t");
                insertSNAP(studentId, name, address, phone);

            }else if (strcmp(result, "CSG") == 0){

                char *course = strtok(NULL, "\t");
                int studentId = atoi(strtok(NULL, "\t"));
                char *grade = strtok(NULL, "\t");
                insertCSG(course, studentId, grade);


            } else if(strcmp(result, "CP") == 0){

                char *course = strtok(NULL, "\t");
                char *prereq = strtok(NULL, "\t");
                insertCP(course,prereq);

            } else if(strcmp(result, "CDH") == 0){

                char *course = strtok(NULL, "\t");
                char *day = strtok(NULL, "\t");
                char *hour = strtok(NULL, "\t");
                insertCDH(course, day, hour);

            } else if(strcmp(result, "CR") == 0){

                char *course = strtok(NULL, "\t");
                char *room = strtok(NULL, "\t");
                insertCR(course,room);
            }
        }
    }
}

//----------------------------------------------------------------END OF READING AND SAVING TO FILE------------------------------------------------------------







//------------------------------------------------------------------PART 2 OF THE PROJECT-------------------------------------------------------------------------------------------
int Question21a(int id, char course[30]){

    printf("**Here is the Result of Search form Question 2, part 1: --------------\n");
    lookupCSG(course, id, "*");

}

int Question2one(char name[30], char course[30]){
    printf("Question 2 part 1:--------\n");
    lookupSNAP('*', name, "*", "*");
    int i = 0;
    while(Q21aID[i]!=0){
        Question21a(Q21aID[i], course);
        i++;
    }
    int j = 0;
    while(Q21aID[j]!=0){
        Q21aID[j]=0;
        j++;
    }

    Q21aIDcounter = 0;

}

int Question22c(char course[30]){
    printf("**Here is the Result of the search from Question 2, part 2------------------------------\n");
    lookupCR(course, "*");
}

int Question22b(char course[30], char day[30], char hour[30]){
    lookupCDH(course, day, hour);
    if(CDHMatch==1){
        Question22c(course);
    }
    CDHMatch=0;
}

int Question22a(int studentId, char hour[30], char day[30]){
    boolean22a = 1;
    lookupCSG("*", studentId, "*");
    boolean22a=0;
}

int Question2two(char name[30], char hour[30], char day[30]){
    printf("Question 2 part 2------------------------------------------------------------------------------\n");
    lookupSNAP('*', name, "*","*" );
    int i = 0;
    while(Q21aID[i]!=0){
        Question22a(Q21aID[i], hour, day);
        i++;
    }
    int j = 0;
    while(Q21aID[j]!=0){
        Q21aID[j]=0;
        j++;
    }
    Q21aIDcounter = 0;
}

//-------------------------------------------------------------------End of Part 2--------------------------------------------------------
//-------------------------------------------------------------------End of Part 2--------------------------------------------------------





//-----------------------------------Part 3 Relational Algebra------------------------------------------------------------------------
//CURRENT
//UNION
int Union(SNAPTABLE r, SNAPTABLE s){
    for(int i = 0; i<SNAPSIZE; i++){
        SNAPTABLE3[i] = r[i];
    }

    for(int i = 0; i<SNAPSIZE; i++){
        while(s[i]!=NULL) {
            lookupSNAP(s[i]->StudentId, s[i]->Name, s[i]->Address, s[i]->Phone);
            if(booleanSNAPFound==0){
                insertSNAP3(s[i]->StudentId, s[i]->Name, s[i]->Address, s[i]->Phone);
            }
            s[i]=s[i]->next;
        }
    }

}

//INTERSECTION
int Intersection(SNAPTABLE r, SNAPTABLE s){

    for(int i = 0; i<SNAPSIZE; i++){
        while(s[i]!=NULL) {
            lookupSNAP(s[i]->StudentId, s[i]->Name, s[i]->Address, s[i]->Phone);
            if(booleanSNAPFound==1){
                insertSNAP3(s[i]->StudentId, s[i]->Name, s[i]->Address, s[i]->Phone);
            }
            s[i]=s[i]->next;
        }
    }
}

//DIFFERENCE
int Difference(SNAPTABLE r, SNAPTABLE s){


    for(int i = 0; i<SNAPSIZE; i++){
        while(s[i]!=NULL) {
            lookupSNAP(s[i]->StudentId, s[i]->Name, s[i]->Address, s[i]->Phone);
            if(booleanSNAPFound==1){
                deleteSNAP(s[i]->StudentId, s[i]->Name, s[i]->Address, s[i]->Phone);
            }
            s[i]=s[i]->next;
        }
    }

    for(int i = 0; i<SNAPSIZE; i++){
        SNAPTABLE3[i] = r[i];
    }
}




typedef struct CRDHTuple *CRDHLIST;
struct CRDHTuple{
    char Course[30];
    char Room[30];
    char Day[30];
    char Hour[30];
    CRDHLIST next;
};

typedef CRDHLIST CRDHTABLE[CDHSIZE]; //HASHTABLES that store a TUPLELIST // has buckets
CRDHTABLE CRDHTABLE1;
CRDHTABLE CRDHTABLE2;
CRDHTABLE COPYCRDHTABLE;

int CRDHhashf(int key){
    return key % CDHSIZE;
}


int insertCRDH (char Icourse[30], char Iroom[30], char Iday[30], char Ihour[30]){

    struct CRDHTuple* temp= (struct CRDHTuple*) malloc (sizeof(struct CRDHTuple));


    strcpy(temp->Course,Icourse);
    strcpy(temp->Room,Iroom);
    strcpy(temp->Day,Iday);
    strcpy(temp->Hour,Ihour);

    temp->next = NULL;

    //IMPLEMENTING THE HASH FUNCTION
    //StudentID is the hash domain, used as the key for the hash function
    int CRDHkey = ((int) Icourse[0] +(int)Iroom[0]+ (int) Iday[0] + (int) Ihour[0]);
    int index = CRDHhashf( CRDHkey );
    //printf("index: %d", index);

    if(CRDHTABLE1[index]!=NULL)temp->next = CRDHTABLE1[index];
    CRDHTABLE1[index] = temp;

}



int insertCRDH2 (char Icourse[30], char Iroom[30], char Iday[30], char Ihour[30]){

    struct CRDHTuple* temp= (struct CRDHTuple*) malloc (sizeof(struct CRDHTuple));


    strcpy(temp->Course,Icourse);
    strcpy(temp->Room,Iroom);
    strcpy(temp->Day,Iday);
    strcpy(temp->Hour,Ihour);

    temp->next = NULL;

    //IMPLEMENTING THE HASH FUNCTION
    //StudentID is the hash domain, used as the key for the hash function
    int CRDHkey = ((int) Icourse[30] +(int)Iroom[0]+ (int) Iday[30] + (int) Ihour[30]);
    int index = CRDHhashf( CRDHkey );
    //printf("index: %d", index);

    if(CRDHTABLE2[index]!=NULL)temp->next = CRDHTABLE2[index];
    CRDHTABLE2[index] = temp;

}


int printCRDHTABLE(){
    printf("Printing CRDH Table---------------------------------------------------------------------------\n");
    for(int i = 0; i<CDHSIZE; i++){
        CRDHLIST tempTuple = CRDHTABLE1[i];
        while (tempTuple!=NULL){
            //    printf("Index: %d\n", i);
            printf(" Course: %s, Room: %s, Day: %s, Hour: %s \n" , tempTuple-> Course , tempTuple->Room, tempTuple-> Day, tempTuple -> Hour);
            tempTuple=tempTuple->next;
        }
    }
}


int printCRDHTABLE2(){
    printf("Printing CRDH Table2---------------------------------------------------------------------------\n");
    for(int i = 0; i<CDHSIZE; i++){
        CRDHLIST tempTuple = CRDHTABLE2[i];
        while (tempTuple!=NULL){
            //    printf("Index: %d\n", i);
            printf(" Course: %s, Room: %s, Day: %s, Hour: %s \n" , tempTuple-> Course , tempTuple->Room, tempTuple-> Day, tempTuple -> Hour);
            tempTuple=tempTuple->next;
        }
    }
}




//JOIN
int Join(CRTABLE tableCR, CDHTABLE tableCDH, char condition[60]){

    if(strcmp(condition, "Course=Course")==0){
        for(int i = 0; i<CRSIZE; i++){

            for(int j = 0; j<CDHSIZE; j++){

                if(tableCR[i]!=NULL && tableCDH[j]!=NULL) {

                    if (strcmp(tableCR[i]->Course, tableCDH[j]->Course) == 0) {
                        insertCRDH(tableCR[i]->Course, tableCR[i]->Room, tableCDH[j]->Day, tableCDH[j]->Hour);

                    }
                }
            }
        }
    }

}



//SELECTION
int selectMyImp(char *attribute, char *condition, char *table){
    booleanCSGSelect = 1;

    if(strcmp(table, "CSG")==0){
        if(strcmp(attribute, "Course")==0 && (strcmp(condition, "CS101")==0)){
            lookupCSG(condition, '*', "*");
        }
    }
    else if(strcmp(table, "CRjoinCDH")==0){
        if(strcmp(attribute, "Room")==0 && (strcmp(condition, "Turing Aud")==0)){


            for(int i = 0; i<CDHSIZE; i++){
                struct CRDHTuple *tempTuple = CRDHTABLE1[i];

                while(tempTuple!=NULL) {

                    if (strcmp(tempTuple->Room, "Turing Aud") == 0) {
                        insertCRDH2(tempTuple->Course, tempTuple->Room, tempTuple->Day, tempTuple->Hour);

                    }
                    tempTuple = tempTuple->next;
                }
            }
        }
    }


    booleanCSGSelect=0;
}



//PROJECTION
int projection(char attribute1[30], char attribute2[30],  char table[20]){

    if(strcmp(table, "CSG")==0) {

        if (strcmp(attribute1, "StudentId") == 0) {
            for (int i = 0; i < CSGSIZE; i++) {
                while (CSGTABLE1[i] != NULL) {
                    printf("Student Id: %d\n", CSGTABLE1[i]->StudentId);
                    CSGTABLE1[i] = CSGTABLE1[i]->next;
                }

            }
        }
    }
    else if(strcmp(table, "CRjoinCDH-TuringAud")==0) {

        if (strcmp(attribute1, "Day") == 0 && strcmp(attribute2, "Hour") == 0) {
            for (int i = 0; i < CSGSIZE; i++) {
                struct CRDHTuple *temptuple = CRDHTABLE2[i];
                while (temptuple != NULL) {
                    printf("Day: %s , Hour: %s\n", temptuple->Day, temptuple->Hour);
                    temptuple = temptuple->next;
                }
            }
        }
    }


}


//-----------------------------------End of Part 3 Relational Algebra------------------------------------------------------------





int main() {

    //**Welcome to Our project, we have gone to great lengths to explain everything here in the source code and in the writeup. Thank You.**


    //testing the insert function for SNAP
    insertSNAP(12345, "C. Brown", "12 Apple St." , "555-1234" );
    insertSNAP(67890, "L. Van Pelt", "34 Pear Ave." , "555-5678" );
    insertSNAP(22222, "P. Patty", "56 Grape Blvd.", "555-9999");


    //(NOT USED RIGHT NOW) testing the insert function for SNAP2 (This will be used for Intersection, Union and Difference functions later on.
    insertSNAP2(12345, "C. Brown", "12 Apple St." , "555-1234" );
    insertSNAP2(12345, "D. DrowD", "13 Apple St." , "555-123D" );
    insertSNAP2(22222, "P. Patty", "56 Grape Blvd.", "555-9999");

    printf("\n* Testing the Insert Function for SNAP: *\n\n");
    printSNAPTABLE();

    printf("\n* Testing the Lookup Function for SNAP: * \n\n");
    printf("* Looking Up entry with StudentID: 67890 (lookup using primary index) : *\n");
    lookupSNAP(67890, "*", "*", "*");

    printf("\n* Looking Up entry with Name: 'P. Patty' (lookup using secondary index) :*\n");
    lookupSNAP('*', "P. Patty", "*", "*");  //Please note that the first parameter is '*' and NOT "*" (single quoted NOT double quoted)

    printf("\n* Testing the Delete Function for SNAP: * \n\n");
    printf("* Deleting the tuple with '12345' as student id from SNAP *\n\n");
    deleteSNAP(12345, "*", "*", "*");
    printf("*The result after the delete is : * \n\n");
    printSNAPTABLE();

    printf("\n* Inserting the deleted tuple back to SNAP (for later use): *\n");
    insertSNAP(12345, "C. Brown", "12 Apple St." , "555-1234" );
    printSNAPTABLE();



    printf("\n* Inserting all other tables * (not printed to be concise, can be printed with the corresponding print function *\n");

// -----------CP -----------------------------------------------------------------------------
    insertCP("CS101", "CS100");
    insertCP("EE200", "EE005");
    insertCP("EE200", "CS100");
    insertCP("CS120", "CS101");
    insertCP("CS121", "CS120");
    insertCP("CS205", "CS101");
    insertCP("CS206", "CS121");
    insertCP("CS206", "CS205");

    // printCPTABLE();

    insertCDH("CS101", "M",  "9AM");
    insertCDH("CS101", "W",  "9AM");
    insertCDH("CS101", "F",  "9AM");
    insertCDH("EE200", "Tu", "10AM");
    insertCDH("EE200", "W",  "1AM");
    insertCDH("EE200", "Th", "10AM");

    printf("\n");
    // printCDHTABLE();


    //------CR---------------------------------------------

    insertCR("CS101", "Turing Aud");
    insertCR("EE200" , "25 Ohm Hall");
    insertCR("PH100", "Newton Lab");

    printf("\n");
    //  printCRTABLE();

    //-----------CSG----------------------------------------

    insertCSG("CS101", 12345, "A");
    insertCSG("CS101", 67890, "B");
    insertCSG("EE200", 12345, "C");
    insertCSG("EE200", 22222, "B+");
    insertCSG("CS101", 33333, "A-");
    insertCSG("PH100", 67890, "C+");

    // printCSGTABLE();


    printf("\n\n* Testing the Save function. A textfile called 'Database.txt' should be created with all the records *\n");
    save_to_file();

    printf("* Testing the Insert from file function. It reads 'Database.txt' * \n");

    insertFromFile("Database.txt");
    printf("\n* Here is what was done: \n 1) All the tables were stored in Database.txt. \n 2)The same data from Database.txt was inserted back to the program. \n 3) So, You would expect to see double entries of every table if they were to be printed again. Here is SNAP : \n");
    printSNAPTABLE();

    printf("\n* Double entries spotted. Therefore, the save and insert function works.\n");


    printf("\n* Now I deleted all the duplicate entries for SNAP to restore SNAP to its original state. *\n");
    for(int i = 0; i<SNAPSIZE; i++) {
        SNAPTABLE1[i] = NULL;
    }
    for(int i = 0; i<CPSIZE; i++) {
        CPTABLE1[i] = NULL;
    }
    for(int i = 0; i<CSGSIZE; i++) {
        CSGTABLE1[i] = NULL;
    }
    for(int i = 0; i<CRSIZE; i++) {
        CRTABLE1[i] = NULL;
    }
    for(int i = 0; i<CDHSIZE; i++) {
        CDHTABLE1[i] = NULL;
    }
    // insert function for SNAP
    insertSNAP(12345, "C. Brown", "12 Apple St." , "555-1234" );
    insertSNAP(67890, "L. Van Pelt", "34 Pear Ave." , "555-5678" );
    insertSNAP(22222, "P. Patty", "56 Grape Blvd.", "555-9999");
    printSNAPTABLE();

    // -----------CP -----------------------------------------------------------------------------
    insertCP("CS101", "CS100");
    insertCP("EE200", "EE005");
    insertCP("EE200", "CS100");
    insertCP("CS120", "CS101");
    insertCP("CS121", "CS120");
    insertCP("CS205", "CS101");
    insertCP("CS206", "CS121");
    insertCP("CS206", "CS205");

    // printCPTABLE();

    insertCDH("CS101", "M",  "9AM");
    insertCDH("CS101", "W",  "9AM");
    insertCDH("CS101", "F",  "9AM");
    insertCDH("EE200", "Tu", "10AM");
    insertCDH("EE200", "W",  "1AM");
    insertCDH("EE200", "Th", "10AM");

    printf("\n");
    // printCDHTABLE();


    //------CR---------------------------------------------

    insertCR("CS101", "Turing Aud");
    insertCR("EE200" , "25 Ohm Hall");
    insertCR("PH100", "Newton Lab");

    printf("\n");
    //  printCRTABLE();

    //-----------CSG----------------------------------------

    insertCSG("CS101", 12345, "A");
    insertCSG("CS101", 67890, "B");
    insertCSG("EE200", 12345, "C");
    insertCSG("EE200", 22222, "B+");
    insertCSG("CS101", 33333, "A-");
    insertCSG("PH100", 67890, "C+");

    // printCSGTABLE();

    printf("\n\n------------------------END OF PART 1, START OF PART 2-----------------------");

    printf("\n\n* Part 2, no. 1: What grade did L. Van Pelt recieve in CS101?: *\n");
    Question2one("L. Van Pelt", "CS101");

    printf("\n* Part 2, no. 1: What grade did C. Brown recieve in CS101?: *\n");
    Question2one("C. Brown", "CS101");

    printf("\n* Part 2, no. 2: Where is C. Brown at 9AM on Mondays? *\n");
    Question2two("C. Brown", "9AM", "M");

    printf("\n\n------------------------END OF PART 2, START OF PART 3-----------------------");



    printf("\n* Union Functionality Test * \n ");
    printf("Suppose that R = SNAPTable1 (printed below): \n");
    printSNAPTABLE();
    printf("\n\n* Suppose that S = SNAPTable2 (printed below): \n");
    printSNAPTABLE2();

    printf("\n\n* Then, R U S is SNAP Table 3 (see below, when SNAP table 3 is printed, ignore the 'Student Found lines')*\n");
    Union(SNAPTABLE1, SNAPTABLE2);
    printSNAPTABLE3();

    //clearing snaptable3();
    for(int i = 0; i<SNAPSIZE; i++){
        SNAPTABLE3[i]=NULL;
    }


    insertSNAP2(12345, "C. Brown", "12 Apple St." , "555-1234" );
    insertSNAP2(12345, "D. DrowD", "13 Apple St." , "555-123D" );
    insertSNAP2(22222, "P. Patty", "56 Grape Blvd.", "555-9999");



    printf("\n\n* From the same example, R Intersection S is SNAP Table 3 (see below, when SNAP table 3 is printed, ignore the 'Student Found lines')*\n");
    Intersection(SNAPTABLE1, SNAPTABLE2);
    printSNAPTABLE3();

    //clearing snaptable3();
    for(int i = 0; i<SNAPSIZE; i++){
        SNAPTABLE3[i]=NULL;
    }



    //clearing snaptable3();
    for(int i = 0; i<SNAPSIZE; i++){
        SNAPTABLE3[i]=NULL;
    }


    insertSNAP2(12345, "C. Brown", "12 Apple St." , "555-1234" );
    insertSNAP2(12345, "D. DrowD", "13 Apple St." , "555-123D" );
    insertSNAP2(22222, "P. Patty", "56 Grape Blvd.", "555-9999");

    printf("\n\n* From the same example, R - S is SNAP Table 3 (see below when SNAP table 3 is printed, ignore the 'Student Found lines')*\n");
    Difference(SNAPTABLE1, SNAPTABLE2);
    printf("R - S: \n");
    printSNAPTABLE3();

    printf("\n\n* Now demonstrating Selection, Projection and Join ----------*\n");


    printf("\n\n* The following is Selection of Course = CS101 from CSG  (8.12): * \n");
    selectMyImp("Course", "CS101", "CSG"); //First Example
    //  printCSGTABLE2();

    printf("\n\n* The following is Projection of Studentid from the result above  (8.13): * \n");
    projection("StudentId","null", "CSG"); //second example


    printf("\n\n* The following is Join of CR and CDH  (8.14): * \n");
    Join(CRTABLE1, CDHTABLE1, "Course=Course"); //third example
    printCRDHTABLE();


    printf("\n\n* The following is Projection of Day and Hour from the Selection of (CR join CDH) where Room = Turing Aud   (8.15): * \n");
    selectMyImp("Room", "Turing Aud", "CRjoinCDH"); //fourth example
    //printCRDHTABLE2();

    projection("Day", "Hour", "CRjoinCDH-TuringAud");




    return 0;
}
