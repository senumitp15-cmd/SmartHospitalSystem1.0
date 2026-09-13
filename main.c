#include<stdio.h>

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

int main(){

int i,j;
printf("Smart Hospital & Resource Allocation System\n");
printf("Bed Status\n");

for(i=0;i<4;i++){
    printf("Ward Number %d :", wardID[i]);

    for(j=0; j< wardCapacity[i]; j++)
    {
        if(bedOccupancy[i][j]==0){
            printf("Available");
        }
        else{
            printf("Occupied");
        }
    }
    printf("\n");
}

return 0;

}
