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
int patientCount = 0;
int patientAge[PATIENT_LIMIT];
int patientUrgency[PATIENT_LIMIT];
int patientSpecialty[PATIENT_LIMIT];
int patientAdmission[PATIENT_LIMIT];
int patientWard[PATIENT_LIMIT];
int patientDays[PATIENT_LIMIT];
int patientBed[PATIENT_LIMIT];
int patientWaitingTime[PATIENT_LIMIT];
double patientSurcharge[PATIENT_LIMIT];
double patientWardCost[PATIENT_LIMIT];
double patientGrossBill[PATIENT_LIMIT];
double patientSubsidy[PATIENT_LIMIT];
double patientFinalPayable[PATIENT_LIMIT];


void registerPatient(int index);
int calculateWaitingTime(int specialty);
double calculateSurcharge(int specialty, int urgency);
double calculateWardCost(int ward, int days);
double calculateGrossBill(int specialty, double surcharge, double wardCost);
double calculateSubsidy(int age, double grossBill);
double calculateFinalPayable(double grossBill, double subsidy);
void sortAndDisplayPriorityQueue();
void printBill(int index);

int main(){

int i,j;
int choice;

printf("Smart Hospital & Resource Allocation System\n");

while(patientCount < PATIENT_LIMIT)
{
    registerPatient(patientCount);
    patientCount++;
    printf("\nDo you want to register another patient? (1-Yes, 0-No): ");
    scanf("%d", &choice);

    if(choice == 0)
    {
        break;
    }

}sortAndDisplayPriorityQueue();

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

/* Priority Queue Sorting */
void sortAndDisplayPriorityQueue()
{
    int order[PATIENT_LIMIT];
    int i;
    int j;
    int temp;

    for(i = 0; i < patientCount; i++)
    {
        order[i] = i;
    }

    for(i = 0; i < patientCount - 1; i++)
    {
        for(j = 0; j < patientCount - 1 - i; j++)
        {
            if(patientUrgency[order[j]] < patientUrgency[order[j + 1]])
            {
                temp = order[j];
                order[j] = order[j + 1];
                order[j + 1] = temp;
            }
        }
    }

    printf("\nPriority Queue\n");

    for(i = 0; i < patientCount; i++)
    {
        printf("\nPatient Name: %s\n", patientName[order[i]]);

        if(patientUrgency[order[i]] == 3)
        {
            printf("Urgency: Critical\n");
        }
        else if(patientUrgency[order[i]] == 2)
        {
            printf("Urgency: Urgent\n");
        }
        else
        {
            printf("Urgency: Normal\n");
        }

        printf("Final Payable Amount: %.2f\n",
               patientFinalPayable[order[i]]);
    }
}

/* Display Patient Bill */
void printBill(int index)
{
    int waitingTime;
    double baseFee;
    int surchargePercentage;

    waitingTime = patientWaitingTime[index];
    baseFee = consultationFee[patientSpecialty[index] - 1];

    if(patientUrgency[index] == 1)
    {
        surchargePercentage = 0;
    }
    else if(patientUrgency[index] == 2)
    {
        surchargePercentage = 20;
    }
    else
    {
        surchargePercentage = 50;
    }

    printf("\n====================================================\n");
    printf("          SMART HOSPITAL ADMISSION & BILL\n");
    printf("----------------------------------------------------\n");

    printf("Patient ID             : PAT-%04d\n", index + 1001);
    printf("Patient Name           : %s\n", patientName[index]);

    if(patientAge[index] < 5 || patientAge[index] > 65)
    {
        printf("Age                    : %d Years (15%% Subsidy Eligible)\n",
               patientAge[index]);
    }
    else
    {
        printf("Age                    : %d Years\n", patientAge[index]);
    }

    printf("Specialty              : %s\n",
           specialtyName[patientSpecialty[index] - 1]);

    if(patientAdmission[index] == 1)
    {
        printf("Assigned Ward          : %s (Bed #%02d)\n",
               wardName[patientWard[index] - 1],
               patientBed[index]);
    }
    else
    {
        printf("Assigned Ward          : Outpatient\n");
    }

    if(patientUrgency[index] == 1)
    {
        printf("Urgency Level          : Level 1 (Normal)\n");
    }
    else if(patientUrgency[index] == 2)
    {
        printf("Urgency Level          : Level 2 (Urgent)\n");
    }
    else
    {
        printf("Urgency Level          : Level 3 (Critical)\n");
    }

    printf("----------------------------------------------------\n");

    printf("Base Consultation Fee  : LKR %10.2f\n", baseFee);

    printf("Emergency Surcharge    : LKR %10.2f (%d%%)\n",
           patientSurcharge[index],
           surchargePercentage);

    printf("Ward Stay Cost (%d Days) : LKR %10.2f\n",
           patientDays[index],
           patientWardCost[index]);

    printf("----------------------------------------------------\n");

    printf("Gross Total Bill       : LKR %10.2f\n",
           patientGrossBill[index]);

    if(patientSubsidy[index] > 0)
    {
        printf("Age Subsidy Discount   : LKR -%9.2f (15%%)\n",
               patientSubsidy[index]);
    }
    else
    {
        printf("Age Subsidy Discount   : LKR %10.2f\n",
               patientSubsidy[index]);
    }

    printf("----------------------------------------------------\n");

    printf("Final Payable Amount   : LKR %10.2f\n",
           patientFinalPayable[index]);

    printf("Estimated Waiting Time : %.2f mins\n",
           (double)waitingTime);

    printf("====================================================\n");
}

/*Patient registration function*/

void registerPatient(int index)
{
   int i;
   int waitingTime;
   double surcharge;
   double wardCost;
   double grossBill;
   double subsidy;
   double finalPayable;

printf("\nEnter patient name: ");

if(index > 0)
{
    getchar();
}

fgets(patientName[index], 50, stdin);


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

waitingTime = calculateWaitingTime(patientSpecialty[index]);

patientWaitingTime[index] = waitingTime;

printf("Estimated Waiting Time: %d minutes\n", waitingTime);

queueCount[patientSpecialty[index] - 1]++;

surcharge = calculateSurcharge(patientSpecialty[index], patientUrgency[index]);

patientSurcharge[index] = surcharge;

printf("Emergency Surcharge: %.2f\n", surcharge);

printf("\nDo you want to admit the patient? (1-Yes, 0-No): ");
scanf("%d", &patientAdmission[index]);

if(patientAdmission[index] == 1)
{
    printf("Enter ward ID (1-4): ");
    scanf("%d", &patientWard[index]);

    printf("Enter number of days: ");
    scanf("%d", &patientDays[index]);

wardCost = calculateWardCost(patientWard[index], patientDays[index]);

patientWardCost[index] = wardCost;

printf("Ward Stay Cost: %.2f\n", wardCost);

grossBill = calculateGrossBill(patientSpecialty[index], surcharge, wardCost);

patientGrossBill[index] = grossBill;

printf("Gross Bill: %.2f\n", grossBill);

subsidy = calculateSubsidy(patientAge[index], grossBill);

patientSubsidy[index] = subsidy;

finalPayable = calculateFinalPayable(grossBill, subsidy);

patientFinalPayable[index] = finalPayable;

printf("Age Subsidy: %.2f\n", subsidy);
printf("Final Payable Amount: %.2f\n", finalPayable);


for(i = 0; i < wardCapacity[patientWard[index] - 1]; i++)
{
   if(bedOccupancy[patientWard[index] - 1][i] == 0)
{
    bedOccupancy[patientWard[index] - 1][i] = 1;

    patientBed[index] = i + 1;

    printf("Bed allocated: %d\n", i + 1);

    break;
}
}

}
else
{
    patientWard[index] = 0;
    patientDays[index] = 0;
    patientBed[index] = 0;

    wardCost = calculateWardCost(patientWard[index], patientDays[index]);

    patientWardCost[index] = wardCost;

    grossBill = calculateGrossBill(patientSpecialty[index], surcharge, wardCost);

    patientGrossBill[index] = grossBill;

    printf("Ward Stay Cost: %.2f\n", wardCost);
    printf("Gross Bill: %.2f\n", grossBill);

    subsidy = calculateSubsidy(patientAge[index], grossBill);

    patientSubsidy[index] = subsidy;

    finalPayable = calculateFinalPayable(grossBill, subsidy);

    patientFinalPayable[index] = finalPayable;

printf("Age Subsidy: %.2f\n", subsidy);
printf("Final Payable Amount: %.2f\n", finalPayable);
}
printBill(index);
}
/*waiting time*/
int calculateWaitingTime(int specialty)
{
    return queueCount[specialty - 1] * consultationTime[specialty - 1];
}

/* Emergency Surcharge*/
double calculateSurcharge(int specialty, int urgency)
{
    if(urgency == 1)
    {
        return 0;
    }
    else if(urgency == 2)
    {
        return consultationFee[specialty - 1] * 0.20;
    }
    else
    {
        return consultationFee[specialty - 1] * 0.50;
    }
}

/* ward stay cost*/
double calculateWardCost(int ward, int days)
{
    if(ward == 0)
    {
        return 0;
    }

    return days * dailyRate[ward - 1];
}

/*gross bill*/
double calculateGrossBill(int specialty, double surcharge, double wardCost)
{
    return consultationFee[specialty - 1] + surcharge + wardCost;
}

/*Age subsidy discount*/
double calculateSubsidy(int age, double grossBill)
{
    if(age < 5 || age > 65)
    {
        return grossBill * 0.15;
    }

    return 0;
}
/* final amount payable*/
double calculateFinalPayable(double grossBill, double subsidy)
{
    return grossBill - subsidy;
}
