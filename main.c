#include<stdio.h>

#define PATIENT_LIMIT 100

const int specialtyID[4] = {1, 2, 3, 4};

const char specialtyName[4][30] = {
    "General Practice (OPD)",
    "Paediatrics",
    "Cardiology",
    "Neurology"
};

const double consultationFee[4] = {
    1500.00,
    2500.00,
    4500.00,
    5000.00
};

const int consultationTime[4] = {
    15,
    20,
    30,
    30
};

const int dailyPatientCap[4] = {
    30,
    20,
    12,
    10
};

/* Ward Details */
const int wardID[4] = {1, 2, 3, 4};

const char wardName[4][30] = {
    "General Ward",
    "Paediatric Ward",
    "Surgical Ward",
    "ICU(Intensive Care Unit)"
};

const double dailyRate[4] = {
    3000.00,
    6000.00,
    12000.00,
    25000.00
};

const int wardCapacity[4] = {
    20,
    10,
    10,
    5
};

/* Bed Status Tracking */
int bedOccupancy[4][20] = {0};

/* Queue Count */
int queueCount[4] = {0};

/* Patient info */
char patientName[PATIENT_LIMIT][50];
int patientAge[PATIENT_LIMIT];
int patientUrgency[PATIENT_LIMIT];
int patientSpecialty[PATIENT_LIMIT];
int patientAdmission[PATIENT_LIMIT];
int patientWard[PATIENT_LIMIT];
int patientDays[PATIENT_LIMIT];


void registerPatient(int index);
int main(){

int i,j;

printf("Smart Hospital & Resource Allocation System\n");
registerPatient(0);
printf("Bed Status\n");

for(i=0;i<4;i++){
    printf("Ward Number %d :", wardID[i]);

    for(j=0; j< wardCapacity[i]; j++)
    {
        if(bedOccupancy[i][j]==0){
            printf("Available ");
        }
        else{
            printf("Occupied ");
        }
    }
    printf("\n");
}

return 0;

}

/*Patient registration function*/
void registerPatient(int index)
{
   int i;
   int waitingTime;
printf("\nEnter patient name: ");
fgets(patientName[index], 50, stdin);

/* Remove newline from the name */


for(i = 0; patientName[index][i] != '\0'; i++)
{
    if(patientName[index][i] == '\n')
    {
        patientName[index][i] = '\0';
        break;
    }
}

printf("Enter age: ");
scanf("%d", &patientAge[index]);

printf("Enter urgency (1-Normal, 2-Urgent, 3-Critical): ");
scanf("%d", &patientUrgency[index]);

printf("Enter specialty ID (1-4): ");
scanf("%d", &patientSpecialty[index]);

printf("Selected Specialty: %s\n", specialtyName[patientSpecialty[index] - 1]);

waitingTime = queueCount[patientSpecialty[index] - 1]
              * consultationTime[patientSpecialty[index] - 1];

printf("Estimated Waiting Time: %d minutes\n", waitingTime);

queueCount[patientSpecialty[index] - 1]++;

printf("\nDo you want to admit the patient? (1-Yes, 0-No): ");
scanf("%d", &patientAdmission[index]);

if(patientAdmission[index] == 1)
{
    printf("Enter ward ID (1-4): ");
    scanf("%d", &patientWard[index]);

    printf("Enter number of days: ");
    scanf("%d", &patientDays[index]);

for(i = 0; i < wardCapacity[patientWard[index] - 1]; i++)
{
        if(bedOccupancy[patientWard[index] - 1][i] == 0)
        {
            bedOccupancy[patientWard[index] - 1][i] = 1;

            printf("Bed allocated: %d\n", i + 1);

            break;
        }
}

}
else
{
    patientWard[index] = 0;
    patientDays[index] = 0;
}

}


