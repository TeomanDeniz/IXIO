// IXIO.exe
// By: Teoman Deniz
// 25.02.2022

#include <windows.h>
#include <stdio.h>
#ifdef _WIN32
#include <string.h>
#define strcasecmp _stricmp // defines strcasecmp()
#else
#include <strings.h>
#endif

int checkIfFileExists(const char *filename); // defines the function at the bottom

char* RELPACE(const char* s,const char* oldW,const char* newW){
// Replaces words from the strings
// Useage as:
// char NEW_VAR=RELPACE(OLDVAR,"OLD WORD","NEW WORD");
char* result;
int i,cnt=0;
int newWlen=strlen(newW);
int oldWlen=strlen(oldW);
for(i=0;s[i]!='\0';i++){
if(strstr(&s[i],oldW)==&s[i]){
cnt++;
i+=oldWlen-1;
}}
result=(char*)malloc(i+cnt*(newWlen-oldWlen)+1);
i=0;
while(*s){
if(strstr(s,oldW)==s){
strcpy(&result[i],newW);
i+=newWlen;s+=oldWlen;
} else {
result[i++]=*s++;
}}
result[i]='\0';
return result;
}

int main(int argc,char* argv[]){

//GETTING THE PROGRAM'S PATH + SELF NAME

char FULL[1024];
GetModuleFileName(NULL,FULL,1024-1); //PROGRAM'S PATH + SELF NAME
char e1WORD[10000];
char e2WORD[10000];
char *NAME=strrchr(FULL,'\\')+1; //#PROGRAM'S SELF NAME#//
sprintf(e1WORD,"%s####%s",FULL,NAME); //LOCKING THE LAST WORD (SELF NAME) ON THE PATH
sprintf(e2WORD,"\\%s####%s",NAME,NAME); //LOCKING THE SELF NAME
char *PATH=RELPACE(e1WORD,e2WORD,""); //#PROGRAM'S PATH#//

char BATCH[10000]; // CREATING VARIABLES FOR USING THEM ON "sprintf()"
char A1[10];
char A2[10000];
char A3[10000];
char A4[10000];
char A5[10000];

if(argc<=2){
printf("\n\n%s {COMMAND} \"{INPUT}\" \"{USERNAME}\" \"{PASSWORD}\" \"{ID}\"\nBy: Teoman Deniz [maximum-tension.com]\n\nUse IX.IO server easily with this program\nYou can create, edit or delete a page in IX.IO\n\n [COMMANDS]\n/C /CREATE -C -CREATE C CREATE  --> Create page with string or existing file\n/E /EDIT -E -EDIT E EDIT        --> Edit page with string or existing file\n/D /DELETE -D -DELETE D DELETE  --> Delete page\n/R /READ -R -READ R READ        --> Read page\n\nNOTE: If you don't have an user profile on IX.IO, it is going to automatically created!\nNOTE: You can't chose your own page ID\n\n [CREATE A PAGE]\n%s \"/CREATE\" \"FILE.txt\" \"{USERNAME}\" \"{PASSWORD}\"\n\n [EDIT A PAGE]\n%s \"edit\" \"SOME TEXTS\" \"{USERNAME}\" \"{PASSWORD}\" \"{ID}\"\n\n [DELETE A PAGE]\n%s \"-D\" \"{USERNAME}\" \"{PASSWORD}\" \"{ID}\"\n\n [READ A PAGE]\n%s /r \"{ID}\"\nOR\nFOR /F \"TOKENS=*\" %%%%# IN ('%s /READ \"{ID}\"') DO (ECHO %%%%#)\n\nYou can save the ID of your new page with:\n\nFOR /F %%%%# IN (\'%s /CREATE \"TEST\" \"USERNAME\" \"PASSWORD\"\') DO SET \"ID=%%%%#\"\nECHO %%ID%%\n",NAME,NAME,NAME,NAME,NAME,NAME,NAME); // "NAME"s for: if program's name is changed
exit(-1);
} // If parameters are less than 2 then send help message and exit from program

sprintf(A1,"%s",argv[1]);
sprintf(A2,"%s",argv[2]);

if(strcasecmp(A1,"/read")==0||strcasecmp(A1,"/r")==0||strcasecmp(A1,"-read")==0||strcasecmp(A1,"-r")==0||strcasecmp(A1,"read")==0||strcasecmp(A1,"r")==0){
//############## READ ##############
sprintf(BATCH,"CERTUTIL -urlcache -split -F \"http://ix.io/%s\" \"%%TMP%%\\DSOD.tmp\" >NUL",A2);
system(BATCH); //DOWNLOADING THE PAGE AS TEXT DECUMENT IN TEMP
system("TYPE \"%TMP%\\DSOD.tmp\""); //READING DOWNLOADED DOCUMENT
system("DEL /Q \"%TMP%\\DSOD.tmp\""); //DELETING DOWNLOADED DOCUMENT
return 0;
//############## READ END ##############
}

if(argc>=3){sprintf(A3,"%s",argv[3]);}
if(argc>=4){sprintf(A4,"%s",argv[4]);}

if(strcasecmp(A1,"/create")==0||strcasecmp(A1,"/c")==0||strcasecmp(A1,"-c")==0||strcasecmp(A1,"-create")==0||strcasecmp(A1,"c")==0||strcasecmp(A1,"create")==0){
//############## CREATE ##############
if(checkIfFileExists(A2)){ //CHECK IF GIVEN PARAMETER IS EXISTING FILE

sprintf(BATCH,"CURL -F \"f:1=^<%s\" \"%s:%s@ix.io\"",A2,A3,A4); // IF GIVEN PARAMETER IS EXISTING FILE THEN WRITE ON PAGE WITH FILE

system(BATCH);
return 0;
} else { //IF GIVEN PARAMETER IS NOT EXISTING FILE

sprintf(BATCH,"CURL -F \"f:1=%s\" \"%s:%s@ix.io\"",A2,A3,A4); // IF GIVEN PARAMETER IS JUST STRINGS THEN WRITE DIRECTLY ON PAGE

//############## CREATE END ##############
system(BATCH);
return 0;
}
}

if(strcasecmp(A1,"/edit")==0||strcasecmp(A1,"/e")==0||strcasecmp(A1,"-e")==0||strcasecmp(A1,"-edit")==0||strcasecmp(A1,"e")==0||strcasecmp(A1,"edit")==0){
//OVERWRITE
if(checkIfFileExists(A2)){ // IF GIVEN PARAMETER IS EXISTING FILE THEN WRITE ON PAGE WITH FILE

if(argc<=5){return 1;}
sprintf(A5,"%s",argv[5]);
sprintf(BATCH,"CURL -F \"f:1=^<%s\" -F \"id:1=%s\" \"%s:%s@ix.io\"",A2,A5,A3,A4);

system(BATCH);
return 0;
} else {

if(argc<=5){return 1;}
sprintf(A5,"%s",argv[5]);
sprintf(BATCH,"CURL -F \"f:1=%s\" -F \"id:1=%s\" \"%s:%s@ix.io\"",A2,A5,A3,A4);

//############## OVERWRITE END ##############
system(BATCH);
return 0;
}
}

if(strcasecmp(A1,"/delete")==0||strcasecmp(A1,"/d")==0||strcasecmp(A1,"/e")==0||strcasecmp(A1,"-delete")==0||strcasecmp(A1,"-d")==0||strcasecmp(A1,"delete")==0||strcasecmp(A1,"d")==0){
//############## DELETE ##############
if(argc<=4){return 1;}
sprintf(BATCH,"CURL -F \"rm=%s\" \"%s:%s@ix.io\"",A4,A2,A3);

//############## DELETE END ##############
system(BATCH);
return 0;
}

return 1;
}

int checkIfFileExists(const char * FILE_NAME){// (CHECK IF FILE IS EXIST) FUNCTION
FILE *FILE;
if(FILE=fopen(FILE_NAME,"r")){
fclose(FILE);
return 1;
}
return 0;
}