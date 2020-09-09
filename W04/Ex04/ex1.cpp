#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 300
#define BUFFER 100

typedef struct {
	int year, month, day, hour, minute, second;
	/* add other members if you want */
} MyDate;
MyDate dates[MAX]; /* MyDate 타입의 배열에 시간 데이터를 저장하라. */

char change_mon(char *mon_c);

int main(void) {
	int n;
	char input[BUFFER];
	char time[MAX][MAX];
	char *day_c, *mon_c, *year_c, *hour_c, *min_c, *sec_c;

	scanf("%d", &n);
	for (int i = -1; i < n; i++) {
		fgets(time[i], BUFFER, stdin);
		time[i][strlen(time[i]) - 1] = 0;
	}
	time[n][0] = '\0';
	char *token;
	for (int i = 0; i < n; i++) {
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
		dates[i].year = atoi(year_c);
		dates[i].month = change_mon(mon_c);
		dates[i].day = atoi(day_c);
		dates[i].hour = atoi(hour_c);
		dates[i].minute = atoi(min_c);
		dates[i].second = atoi(sec_c);
	}

	int tmp;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if ((dates[i].year > dates[j].year) || ((dates[i].year == dates[j].year) && (dates[i].month > dates[j].month)) || ((dates[i].year == dates[j].year) && (dates[i].month == dates[j].month) && (dates[i].day >= dates[j].day))) {
				tmp = dates[i].year;
				dates[i].year = dates[j].year;
				dates[j].year = tmp;

				tmp = dates[i].month;
				dates[i].month = dates[j].month;
				dates[j].month = tmp;

				tmp = dates[i].day;
				dates[i].day = dates[j].day;
				dates[j].day = tmp;

				tmp = dates[i].hour;
				dates[i].hour = dates[j].hour;
				dates[j].hour = tmp;

				tmp = dates[i].minute;
				dates[i].minute = dates[j].minute;
				dates[j].minute = tmp;

				tmp = dates[i].second;
				dates[i].second = dates[j].second;
				dates[j].second = tmp;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		int idx = i;
		while ((dates[idx].year == dates[idx + 1].year) && (dates[idx].month == dates[idx + 1].month) && (dates[idx].day == dates[idx + 1].day)) {
			idx++;
		}
		idx++;
		for (int j = i; j < idx - 1; j++) {
			for (int k = j + 1; k < idx; k++) {
				if ((dates[j].hour > dates[k].hour) || ((dates[j].hour == dates[k].hour) && (dates[j].minute > dates[k].minute)) || ((dates[j].hour == dates[k].hour) && (dates[j].minute == dates[k].minute) && (dates[j].second >= dates[k].second))) {
					tmp = dates[j].hour;
					dates[j].hour = dates[k].hour;
					dates[k].hour = tmp;

					tmp = dates[j].minute;
					dates[j].minute = dates[k].minute;
					dates[k].minute = tmp;

					tmp = dates[j].second;
					dates[j].second = dates[k].second;
					dates[k].second = tmp;
				}
			}
		}
		i = idx - 1;
	}

	for (int i = 0; i < n; i++) 
		printf("%02d-%02d-%02d:%02d:%02d:%02d\n", dates[i].year, dates[i].month, dates[i].day, dates[i].hour, dates[i].minute, dates[i].second);
	return 0;
}
char change_mon(char *mon_c) {
	int mon;
	if (strcmp(mon_c, "Jan") == 0)
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