

 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct date{
   int d,m,y;
};

struct details
{
 long int acc_no;
 char acc_name[30];
 char gen[10];
 struct date dob; 
 char add[50];
 char u_n[30];
 char pass[30];
 struct date op_acc;
}dt;



struct transcation{
long int acc_no;
 struct date td;
 char type[15];
 long int a;
 long int ta;
}trc;

/*-------------------------------bank auth section to get the information about customer-----------------------------------------------*/


/*----------------------------------------create account-----------------------------------------------------------*/




void create_acc()
{ 
 
 long int acc_no;
 char acc_name[30];
 int d1,m1,y1,d2,m2,y2;
 char add[50];
 char u_n[30];
 char pass[30];
 char gen[10]; 

  int avl;

   FILE *fp,*fp2,*fp3;
   fp = fopen("details.txt", "a");

   printf("\t\nAccount Number:");
   scanf("%lu",&acc_no);
   // check availibility  of account number
   avl=avlacc(acc_no); 
   if (!avl)
  { 
  
   printf("\t\nAccount Holder name:");
   scanf("%s",&acc_name);
   printf("\t\nGender:");
   scanf("%s",&gen);
   printf("\t\nHOlder Address:");
   scanf("%s",&add);
   printf("\t\nDate of Birth(DD-MM-YY):");
   scanf("%d",&d1);printf("\t-"); scanf("%d",&m1);
   printf("\t-");        scanf("%d",&y1);
   printf("\t\nUser Id:");
   scanf("%s",&u_n);
   printf("\t\npassword:");
   scanf("%s",&pass);
   printf("\t\naccount opening date(DD-MM-YY):");
   scanf("%d",&d2);printf("\t-"); scanf("%d",&m2);printf("\t-"); scanf("%d",&y2);

dt.acc_no=acc_no;
strcpy(dt.acc_name,acc_name);
strcpy(dt.gen,gen);
strcpy(dt.add,add);
dt.dob.d=d1;
dt.dob.m=m1;
dt.dob.y=y1;
strcpy(dt.u_n,u_n);
strcpy(dt.pass,pass);
dt.op_acc.d=d2;
dt.op_acc.m=m2;
dt.op_acc.y=y2;

fwrite(&dt, sizeof(dt), 1, fp);
fclose(fp);
}
else{
      printf("\n----this account no already available so give another account number---\n");
}

}



/*----------------------------------------Display customer details-----------------------------------------------------------*/

void disacc()
{
  // all customer details going to print here for bank authorized person only access

 FILE *fp1;
 fp1 = fopen("details.txt","r");

 printf("Account number\tAcc_Holder_Name\tGender\tAddress\tUser Id\tPassword\tDOB\tAccount_opening_date  \n\n");
 while (fread(&dt, sizeof(dt), 1, fp1))
{
printf("\n\t% lu \t %s\t\t %s\t %s\t%s\t%s",dt.acc_no,dt.acc_name,dt.gen,dt.add,dt.u_n,dt.pass);
printf("\t%d",dt.dob.d);
printf("-");printf("%d",dt.dob.m);printf("-");printf("%d",dt.dob.y);
printf("\t%d",dt.op_acc.d);
printf("-");printf("%d",dt.op_acc.m);printf("-");printf("%d",dt.op_acc.y);
}
fclose(fp1);


}

/*----------------------------------------delete account-----------------------------------------------------------*/

void delacc(){
FILE *fpo;
 FILE *fpt;
 int r, s;
 printf("Enter the account number to delete :");
 scanf("%d", &r);
 if (avlacc(r) == 0)
  printf("account %d is not available in the file\n", r);
 else
 {
  fpo = fopen("details.txt", "r");
  fpt = fopen("TempFile", "w");
  while (fread(&dt, sizeof(dt), 1, fpo))
  {
   s = dt.acc_no;
   if (s != r)
    fwrite(&dt, sizeof(dt), 1, fpt);
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("details.txt", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&dt, sizeof(dt), 1, fpt))
   fwrite(&dt, sizeof(dt), 1, fpo);
  printf("\nRECORD DELETED\n");
  fclose(fpo);
  fclose(fpt);
 }}
/*----------------------------------------Transcation amount  -----------------------------------------------------------*/
  
  void trans()
{ 
   long int acc_no;
   int ch,avl;
  
  printf("\n\tenter the account number:");
  scanf("%lu",&acc_no);
 avl=avlacc(acc_no); 
   if (avl)
  { 
  do{
     printf("\n\t1. Credit the account");
     printf("\n\t2. Withdraw the account");
     printf("\n\t3. tranction history");
     printf("\n\t4. Stop transcation\n\t");
     scanf("%d",&ch);
     
    switch(ch)
   {
      case 1: 
              credit(acc_no);
               break;
     case 2: 
              withdraw(acc_no);
                break;
     case 3:  
             
              transhis(acc_no);
             
             
               break;
     default:
              printf("\n\tenter the correct choice\n");
    }
    } while(ch!=4);

    }
  else{
         printf("\n\t No such account Exits\n");
        
      }
}
/*----------------------------------------Credit money -----------------------------------------------------------*/

void credit(long int acc_no)
{



 int sum;
 long int a;

 FILE *fp,*fp1;
 

 fp1 = fopen("tranc.txt", "a"); 
 
 
 while( fread(&trc, sizeof(trc), 1, fp1))
  {   
     if ( trc.acc_no==acc_no)
        sum=trc.ta;
  }
  fclose(fp1); 

   
  fp = fopen("tranc.txt", "a");

 
 printf("\n\tenter the amount for credit: ");
 scanf("%lu",&a);
 printf("\n\tToday Date:");
 scanf("%d",&trc.td.d);
 printf("\t-");scanf("%d",&trc.td.m);printf("\t-");scanf("%d",&trc.td.y);
 
 trc.ta=sum+a;
 trc.a=a;
 trc.acc_no=acc_no;
 strcpy(trc.type,"credit");
 fwrite(&trc, sizeof(trc), 1, fp);
 fclose(fp);


}

/*----------------------------------------withdraw money-----------------------------------------------------------*/

void  withdraw(long int acc_no)
{
   
  int sum,wda,d1,m1,y1;
  FILE *fp,*fp1;
 
 
 fp1 = fopen("tranc.txt", "a"); 
 
  while( fread(&trc, sizeof(trc), 1, fp1))
  {   
     if ( acc_no==trc.acc_no)
        sum=trc.ta;
  }
  fclose(fp1);
 fp = fopen("tranc.txt", "a");

 
 printf("\n\tenter the amount for withdraw: ");
 scanf("%lu",&wda);
if (wda>sum)
 {
      printf("no avilable money ! choose lesser than total amount u have %d ",sum);
  }
  else{    
          printf("\n\tToday Date:");
          scanf("%d",&d1);
          printf("\t-");scanf("%d",&m1);printf("\t-");scanf("%d",&y1);
 
  
            
              trc.ta=sum-wda;
              trc.a=wda;
              trc.td.d=d1;
              trc.td.m=m1;
              trc.td.y=y1;
              trc.acc_no=acc_no;
              strcpy(trc.type,"withdraw");
   
        fwrite(&trc, sizeof(trc), 1, fp); 
     }
 
 
   
 fclose(fp);

}

/*----------------------------------------transcation History -----------------------------------------------------------*/
void transhis(long int accno)
{
     
   
   FILE *fp;
   fp = fopen("tranc.txt", "r");
   printf("\n\t-------------Trascation History-------\n");
  
   printf("\tDate\tType\tAmount\tToatal Amount  \n\n");

     while (!feof(fp))
  {   
     fread(&trc, sizeof(trc), 1, fp);

     if ( accno==trc.acc_no)
       {
          printf("\t%d",trc.td.d); printf("-");printf("%d",trc.td.m);printf("-");printf("%d",trc.td.y);
          printf("\t%s\t%lu\t%lu\n",trc.type,trc.a,trc.ta);
          
       } 
  }
  
  fclose(fp);
}
/*----------------------------------------account updation-----------------------------------------------------------*/

void update()
{
 int avl;
 FILE *fpt;
 FILE *fpo;
 int  ch;
 long int acc_no,s;


 printf("\n\tEnter Account No to update:");
 scanf("%lu", &acc_no);
 avl = avlacc(acc_no);
 if (avl == 0)
 {
  printf("\n\there is not details of %lu  account\n", acc_no);
 }
 else
 {
  fpo = fopen("details.txt", "r");
  fpt = fopen("TempFile1", "w");
  while (fread(&dt, sizeof(dt), 1, fpo))
  {
   s = dt.acc_no;
   if (s !=acc_no)
    fwrite(&dt, sizeof(dt), 1, fpt);
   else
   {
   do{
    printf("\n\t1. Update the name  and address of account holder %lu", acc_no);
    printf("\n\t2. Update the authentication of account holder %lu", acc_no);
    printf("\n\t3. Exit..");
    printf("\n\tEnter your choice:");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
     printf("\n\tEnter Name:");
     scanf("%s", &dt.acc_name);
     printf("\n\tEnter address:");
     scanf("%s",&dt.add);
     break;
    case 2:
          wrong_pass(acc_no);
     break;
    
    default:
     printf("\n\tInvalid Selection");
     break;
    }}while(ch!=3);

    fwrite(&dt, sizeof(dt), 1, fpt);
   }
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("details.txt", "w");
  fpt = fopen("TempFile1", "r");
  while (fread(&dt, sizeof(dt), 1, fpt))
  {
   fwrite(&dt, sizeof(dt), 1, fpo);
  }
  fclose(fpo);
  fclose(fpt);
  printf("RECORD UPDATED");
 }
} 



/*----------------------------------------end bank_auth  Section-----------------------------------------------------------*/


/*----------------------------------------Customer Section-----------------------------------------------------------*/

/*----------------------------------------display my account details-----------------------------------------------------------*/

void dismyacc(long int acc_no)
{
 FILE *fp;
fp = fopen("details.txt", "r");
 while (!feof(fp))
 {
  fread(&dt, sizeof(dt), 1, fp);

  if (acc_no == dt.acc_no)
  {
        printf("\n\tAccount number:");printf("\t\t%lu",dt.acc_no);
        printf("\n\tAccount holder name:");printf("\t%s",dt.acc_name);
        printf("\n\tGender:");printf("\t\t\t%s",dt.gen);
        printf("\n\tAddress:");printf("\t\t%s",dt.add);
        printf("\n\tUser Id:");printf("\t\t%s",dt.u_n);
        printf("\n\tPassword:");printf("\t\t%s",dt.pass);
        printf("\n\tDOB:");printf("\t\t\t%d",dt.dob.d);
        printf("-");printf("%d",dt.dob.m);printf("-");printf("%d",dt.dob.y);
        printf("\n\tAcc_Opening_Date:");printf("\t%d",dt.op_acc.d);
        printf("-");printf("%d",dt.op_acc.m);printf("-");printf("%d\n",dt.op_acc.y);
  }
       
    
}

// transcation.......
 transhis( acc_no);
}








/*----------------------------------------Customer login -----------------------------------------------------------*/
void customer()
{ 
  FILE *fp;
  
  long int acc_no;
  char u_n[10];
  char pass[10];

  int ch,avl;
  char u_n1[30],ch1;
 char pass1[30];

  printf("\t\nAccount Number:");
  scanf("%lu",&acc_no);
    // check availablility this account then go proceed....
   
   avl=avlacc(acc_no);
     if(avl)
  {
  printf("\t\nUser Id:");
  scanf("%s",u_n);
  printf("\t\nPassword:");
  scanf("%s",pass);

     fp=fopen("details.txt","r");
    while (!feof(fp))
 {
  fread(&dt, sizeof(dt), 1, fp);
  
   if (acc_no == dt.acc_no)
{
     strcpy(u_n1,dt.u_n);
     strcpy(pass1,dt.pass);

}}
  fclose(fp);




  if (!strcmp(u_n,u_n1))
  { 
     if (!strcmp(pass,pass1))
  {
 

    do{ 
     
      printf("\t\nselect option");
      printf("\t\n1. your account");
      
      printf("\t\n2. Exit\n");
      scanf("%d",&ch);
      switch(ch)
      {
       case 1: 
             dismyacc(acc_no);
             break;
     
       default:
             printf("\t\nenter correct choice\n");
     }}while(ch!=2);
}
 else
      {
        printf("\t\npassword wrong");
       printf("\n\tforget password\n\n");
       printf("\n\t'Y' for change authentication\n");
       scanf("%c",&ch1);
           if(ch1=='y')
              wrong_pass( acc_no);     
      }}
else
{
 printf("\n\tyou are not allowed\n");
 printf("\n\t-----------------------\n");  
   printf("\n\tforget password\n\n");
       printf("\n\t'Y' for change authentication\n");
       scanf("%c",&ch1);
           if(ch1=='y')
              wrong_pass( acc_no);   
}}
else
{
  printf("\nNO such account details exit...plzz contact your branch manager\n");
}
}

/*----------------for updation athentication --------------------------- */
 
void wrong_pass(long int acc_no)
{
 int avl;
 FILE *fpt;
 FILE *fpo;
 int  ch;
  long int s;
   char u_n2[30];
 char pass2[30],pass3[30];
 
  fpo = fopen("details.txt", "r");
  fpt = fopen("TempFile1", "w");
  while (fread(&dt, sizeof(dt), 1, fpo))
  {
   s = dt.acc_no;

   if (s != acc_no)
    fwrite(&dt, sizeof(dt), 1, fpt);
   else
   {   
       printf("\n\tenter User_Id:\n");
                  scanf("%s",u_n2);
                  printf("\n\tenter Password\n");
                  scanf("%s",pass2);
                  printf("\n\tRe-enter Password\n");
                  scanf("%s",pass3);
                   if (!strcmp(pass2,pass3))
                     {
                       strcpy(dt.pass,pass2);
                       strcpy(dt.u_n,u_n2);
                      }
    }
    fwrite(&dt, sizeof(dt), 1, fpt);
   }
  
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("details.txt", "w");
  fpt = fopen("TempFile1", "r");
  while (fread(&dt, sizeof(dt), 1, fpt))
  {
   fwrite(&dt, sizeof(dt), 1, fpo);
  }
  fclose(fpo);
  fclose(fpt);
  printf("RECORD UPDATED");
 }

























/*----------------------------------------End  of customer login-----------------------------------------------------------*/

/*-----------------------------------------bank auth login ---------------------------------------------------*/


void bank_auth()
{
  int u_n[10];
  int pass[10];
  int ch,avl;
  long int accno;

   printf("\t\nUser Id:");
   scanf("%s",u_n);
   printf("\t\npassword:");
   scanf("%s",pass);
   
  if (!strcmp(u_n,"test_user"))
  { 
     if (!strcmp(pass,"12345"))
  {
    do{ 
      printf("\t\n---------------");
      printf("\t\nselect option");
      printf("\t\n1. create an account..");
      printf("\t\n2. details of customers..");
      printf("\t\n3. transcation..");
      printf("\t\n4. transcation History ...");
      printf("\t\n5. delete an account..");
     printf("\t\n6. update the account..");
      printf("\t\n7. Exit\n");
      scanf("%d",&ch);
      switch(ch)
      {
       case 1: create_acc();
             break;
       case 2: disacc();
             break;
       case 3:  trans();
             break;
       case 4:  
              printf("\n\tenter the account Number\n");
              scanf("%lu",&accno);
              avl=avlacc(accno);
              if (avl)
             {
              transhis(accno);
              }
              else
               printf("\n\tNo such account details exits\n");   
               
               break;
   
       case 5 :  delacc();
             break;
       case 6: update();
                break;
       default:
       printf("\t\nenter correct choice\n");
    }}while(ch!=7);
} 

else
{
  printf("\n wrong password....\n");
}
}
else {
   printf("\nYou are not allowed .....\n");
}

}




//    FUNCTION TO CHECK GIVEN Emp_id  IS AVAILABLE //
int avlacc(long int accno)
{
 FILE *fp;
 int c = 0;
 fp = fopen("details.txt", "r");
 while (!feof(fp))
 {
  fread(&dt, sizeof(dt), 1, fp);

  if (accno == dt.acc_no)
  {
   fclose(fp);
   return 1;
  }
 }
 fclose(fp);
 return 0;
}


//FUNCTION TO CHECK THE FILE IS EMPTY OR NOT
int empty()
{
 int c = 0;
 FILE *fp;
 fp = fopen("details.txt", "r");
 while (fread(&dt, sizeof(dt), 1, fp))
  c = 1;
 fclose(fp);
 return c;
}



// MAIN PROGRAM
void main()
{
 int c;
 do
 {
  printf("\n\t---Select your choice---------\n");
  printf("\n\t1.Manger or bank authorized person");
  printf("\n\t2.Customer");
  printf("\n\t3.EXIT");
  printf("\n\n------------------------------------------\n");
  printf("\nEnter your choice:");
  scanf("%d", &c);
  printf("\n");
  switch (c)
  {
  case 1:
    bank_auth();
    break;
  case 2:
    customer();
    break;
  default:
  printf("\nYour choice is wrong\nPlease try again...\n");
  break;

  }
 } while (c != 3);
}

































