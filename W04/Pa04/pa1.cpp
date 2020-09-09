#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 4000

char *ip[MAX];
char *time[MAX];
char *url[MAX];
char *status[MAX];
char *time_cpy[MAX];

char *day_c, *mon_c, *year_c,
*hour_c, *min_c , *sec_c;
int year[MAX], mon[MAX], day[MAX], hour[MAX], min[MAX], sec[MAX];

char arr[MAX][200];      //전체 배열
int n = 0;

void s_date();
void s_ip();
char change_mon(char *);

int main(void) {
   char input[20], input2[20];
   char buffer[200];

   FILE *fp = fopen("webLog.csv", "r");
   while (!feof(fp)) {
      fgets(arr[n], sizeof(arr[n]), fp);
      n++;
   }
  fclose(fp);
   

   char *token;
   for (int i = 0; i < n; i++) {
      token = strtok(arr[i], ",");
      while (token != NULL) {
         ip[i] = token;
         token = strtok(NULL, ",");
         time[i] = token;
         token = strtok(NULL, ",");
         url[i] = token;
         token = strtok(NULL, ",");
         status[i] = token;
         token = strtok(NULL, ",");
      }
   }
   for (int i = 1; i < n-1; i++) {
      time_cpy[i] = strdup(time[i]);
   }
  
   for (int i = 1; i < n - 1; i++) {
	   token = strtok(time[i], "[:/]");   //날짜 년,월,일,시간 나누기
	   while (token != NULL) {
		   day_c = token;
		   token = strtok(NULL, "[:/]");
		   mon_c = token;
		   token = strtok(NULL, "[:/]");
		   year_c = token;
		   token = strtok(NULL, "[:/]");
		   hour_c = token;
		   token = strtok(NULL, "[:/]");
		   min_c = token;
		   token = strtok(NULL, "[:/]");
		   sec_c = token;
		   token = strtok(NULL, "[:/]");
	   }
	   year[i] = atoi(year_c);      //char형을 int형으로 바꾸기
	   mon[i] = change_mon(mon_c);   //바꾸고 각 날짜, 시간 배열에 넣기
	   day[i] = atoi(day_c);
	   hour[i] = atoi(hour_c);
	   min[i] = atoi(min_c);
	   sec[i] = atoi(sec_c);
   }
   //////////

   while (1) {
      printf("$ ");
      scanf("%s", input);

      if (strcmp(input, "search") == 0) {
         scanf("%s", input2);
         if (strcmp(input2, "-date") == 0)
            s_date();
         else if (strcmp(input2, "-ip") == 0)
            s_ip();
      }
      else if (strcmp(input, "exit") == 0)
         break;
   }
   return 0;
}

void s_date() {
   char *fir=(char*)malloc(200);
   char *sec=(char*)malloc(200);
   scanf("%s", fir);
   scanf("%s", sec);

   char *ttime3_c, *ttime1_c , *ttime2_c , *year_c , *mon_c , *day_c;
   char *year_cf , *mon_cf, *day_cf;
   char *year_cs, *mon_cs, *day_cs ;
   int year_f, mon_f, day_f;
   int year_s, mon_s, day_s;
   
   char *the_ip[MAX];
   int ip_num[MAX];
   int q = 0;

   char *token;
   token = strtok(fir, "/");   
   while (token != NULL) {      // 첫 날짜 년,월,일 나누기
      day_cf = token;
      token = strtok(NULL, "/");
      mon_cf = token;
      token = strtok(NULL, "/");
      year_cf = token;
      token = strtok(NULL, "/");
   }
   year_f = atoi(year_cf);   //char형을 int형으로 바꾸기
   mon_f = change_mon(mon_cf);
   day_f = atoi(day_cf);   

   token = strtok(sec, "/");
   while (token != NULL) {      // 둘째 날짜 년,월,일 나누기
      day_cs = token;
      token = strtok(NULL, "/");
      mon_cs = token;
      token = strtok(NULL, "/");
      year_cs = token;
      token = strtok(NULL, "/");
   }
   year_s = atoi(year_cs);      //char형을 int형으로 바꾸기
   mon_s = change_mon(mon_cs);
   day_s = atoi(day_cs);

   for (int i = 1; i < n - 1; i++) {
	   if ((year_f < year[i]) && (year[i] < year_s)) {   //날짜 사이에 있는 ip구하기 
		   the_ip[q++] = ip[i];
	   }
 	   else if ((year_f < year[i]) || ((year_f == year[i]) && (mon_f < mon[i])) || ((year_f == year[i]) && (mon_f == mon[i]) && (day_f <= day[i]))) {
		   if ((year[i] < year_s) || ((year[i] == year_s) && (mon[i] < mon_s)) || ((year[i] == year_s) && (mon[i] == mon_s) && (day[i] <= day_s))) {
			   the_ip[q++] = ip[i];
		   }
	   }
   }

   for (int i = 0; i < q; i++) {      //ip접속 횟수 구하기 
      ip_num[i] = 1;
   }
   for (int j = 0; j < q - 1; j++) {
      for (int k = j + 1; k < q; k++) {
         if (strcmp(the_ip[j], the_ip[k]) == 0) {
            ip_num[j]++;
            for (int z = k; z < q ; z++) {   //같은 거 배열에서 삭제
               the_ip[z] = the_ip[z + 1];
               ip_num[z] = ip_num[z + 1];
            }
			the_ip[q] = 0;
			ip_num[q] = '\0';
            q--; k--;
         }
      }
   }

   int tmp;
   char *ttmp;
   for (int i = 0; i < q; i++) {      //접속 횟수에 대한 내림차순 정렬
      for (int j = i + 1; j < q; j++) {
         if (ip_num[i] < ip_num[j]) {
            tmp = ip_num[i];
            ip_num[i] = ip_num[j];
            ip_num[j] = tmp;

            ttmp = the_ip[i];
            the_ip[i] = the_ip[j];
            the_ip[j] = ttmp;
         }
      }
   }

   int max;
   max = ip_num[0];
   for (int i = 0; i < q; i++) {      //접속 회수가 동일할때 ip주소의 사전식 정렬
      int idx = i;
      while (ip_num[idx] == max) {
         idx++;
      }
      for (int j = i; j < idx - 1; j++) {
         for (int k = j + 1; k < idx; k++) {
            if (strcmp(the_ip[j], the_ip[k]) > 0) {
               tmp = ip_num[j];
               ip_num[j] = ip_num[k];
               ip_num[k] = tmp;

               ttmp = the_ip[j];
               the_ip[j] = the_ip[k];
               the_ip[k] = ttmp;
            }
         }
      }
      max--;
      i = idx - 1;
   }

   printf("%d ips found:\n", q);
   for (int i = 0; i < q; i++)
      printf("   %s: %d\n", the_ip[i], ip_num[i]);


   return;
}

void s_ip() {
   char *input_ip = (char*)malloc(200);
   scanf("%s", input_ip);

   int year_arr[MAX], mon_arr[MAX], day_arr[MAX], hour_arr[MAX], min_arr[MAX], sec_arr[MAX];

   int the_idx[MAX];         //ip가 같을 경우의 인덱스 배열
   int q = 0;
   for (int i = 1; i < n-1; i++) {      //ip가 같을 경우의 인덱스들을 배열에 저장
      if (strcmp(ip[i], input_ip) == 0) {
         the_idx[q] = i;
		 year_arr[q] = year[i];
		 mon_arr[q] = mon[i];
		 day_arr[q] = day[i];
		 hour_arr[q] = hour[i];
		 min_arr[q] = min[i];
		 sec_arr[q] = sec[i];
		 q++;
      }
   }

   //////////////////

   int tmp;
   for (int i = 0; i < q - 1 ; i++) {
      for (int j = i + 1; j < q; j++) {
         if ((year_arr[i] > year_arr[j]) || ((year_arr[i] == year_arr[j]) && (mon_arr[i] > mon_arr[j])) || ((year_arr[i] == year_arr[j]) && (mon_arr[i] == mon_arr[j]) && (day_arr[i] >= day_arr[j]))) {
            tmp = the_idx[i];
            the_idx[i] = the_idx[j];
            the_idx[j] = tmp;

            tmp = year_arr[i];
            year_arr[i] = year_arr[j];
            year_arr[j] = tmp;

            tmp = mon_arr[i];
            mon_arr[i] = mon_arr[j];
            mon_arr[j] = tmp;

            tmp = day_arr[i];
            day_arr[i] = day_arr[j];
            day_arr[j] = tmp;

            tmp = hour_arr[i];
            hour_arr[i] = hour_arr[j];
            hour_arr[j] = tmp;

            tmp = min_arr[i];
            min_arr[i] = min_arr[j];
            min_arr[j] = tmp;

            tmp = sec_arr[i];
            sec_arr[i] = sec_arr[j];
            sec_arr[j] = tmp;
         }
      }
   }
   for (int i = 0; i < q; i++) {         
      int idx = i;
      while ((year_arr[idx] == year_arr[idx + 1]) && (mon_arr[idx] == mon_arr[idx + 1]) && (day_arr[idx] == day_arr[idx + 1])) {
         idx++;
      }
      idx++;
      for (int j = i; j < idx - 1; j++) {
         for (int k = j + 1; k < idx; k++) {
            if ((hour_arr[j] > hour_arr[k]) || ((hour_arr[j] == hour_arr[k]) && (min_arr[j] > min_arr[k])) || ((hour_arr[j] == hour_arr[k]) && (min_arr[j] == min_arr[k]) && (sec_arr[j] >= sec_arr[k]))) {
               tmp = the_idx[j];
               the_idx[j] = the_idx[k];
               the_idx[k] = tmp;

               tmp = hour_arr[j];
               hour_arr[j] = hour_arr[k];
               hour_arr[k] = tmp;

               tmp = min_arr[j];
               min_arr[j] = min_arr[k];
               min_arr[k] = tmp;

               tmp = sec_arr[j];
               sec_arr[j] = sec_arr[k];
               sec_arr[k] = tmp;
            }
         }
      }
      i = idx - 1;
   }

   printf("%d logs found\n", q);
   for (int i = 0; i < q; i++) {
      printf("   %s,%s,%s", time_cpy[the_idx[i]], url[the_idx[i]], status[the_idx[i]]);
   }
   
   return;
}

char change_mon(char *mon_c) {
   int mon;
   if (strcmp(mon_c, "Jan")==0)
      mon = 1;
   else if (strcmp(mon_c, "Feb") == 0)
      mon = 2;
   else if (strcmp(mon_c, "Mar") == 0)
      mon = 3;
   else if (strcmp(mon_c, "Apr") == 0)
      mon = 4;
   else if (strcmp(mon_c, "May") == 0)
      mon = 5;
   else if (strcmp(mon_c, "Jun") == 0)
      mon = 6;
   else if (strcmp(mon_c, "Jul") == 0)
      mon = 7;
   else if (strcmp(mon_c, "Aug") == 0)
      mon = 8;
   else if (strcmp(mon_c, "Sep") == 0)
      mon = 9;
   else if (strcmp(mon_c, "Oct") == 0)
      mon = 10;
   else if (strcmp(mon_c, "Nov") == 0)
      mon = 11;
   else if (strcmp(mon_c, "Dec") == 0)
      mon = 12;

   return mon;
}
