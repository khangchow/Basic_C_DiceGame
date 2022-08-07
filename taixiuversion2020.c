#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>
#include<stdbool.h>
typedef struct{
	char ten[30];
	int tien;
	int chon;
	int dat;
}Nguoichoi;

static int stt = 1;

void buyCoin(Nguoichoi *so, int *check){
	int tien;
	char ask;
	do{
		printf("Do you want to buy coins y/n? ");
		ask = getchar();
		fflush(stdin);
		if(ask != 'y' && ask != 'n') printf("Please enter y(yes) or n(no)!\n");
	}while(ask != 'y' && ask != 'n');
	if(ask == 'y'){
		*check = 1;
		do{
			printf("Enter number of coin you want to buy(1 coin = 1000 VND): ");
			scanf("%d", &tien);
			fflush(stdin);
			if(tien < 20) printf("You must buy at least 20 coins once!\n");
		}while(tien < 20);
		so->tien += tien;
	}else if(ask == 'n') *check = 0;
}

void napTien(Nguoichoi *so, int n){
	int chon, i, count = 1, check = 1;
	do{
		printf("Enter player number to buy coins: ");
		scanf("%d", &chon);	
		fflush(stdin);
		if(chon <= 0 || chon > n) printf("Invalid input!!!\n");
	}while(chon <= 0 || chon > n);
	for(i = 0; i < n; i++){
		if(count == chon){
			buyCoin(&so[i], &check);
			if(check == 0) printf("Purchase cancelled!\n");
			break;
		}else count++;
	}
}

int checkMoney(char *money, bool *c){
	int i;
	for(i = 0; i < strlen(money); i++){
		if(!(money[i] >= '0' && money[i] <= '9')){
			printf("Invalid input!\n");
			return 0;
		}
	}
	*c = true;
	return atoi(money);
}

void themNguoiChoiMoi(Nguoichoi *so, int n, int check, int temp){
	int i, buy = 1;
	char money[10000];
	bool c = false;
	for(i = check; i < n; i++){
		printf("Enter ingame: ", stt++);
		gets(so[i].ten);
		fflush(stdin);
		do{
			do{
				printf("Enter number of coin you want to buy(1 coin = 1000 VND): ");
				gets(money);
				so[i].tien = checkMoney(money, &c);
			}while(c == false);
			if(so[i].tien < 20) printf("You must buy at least 20 coins once!\n");
		}while(so[i].tien < 20);  
		printf("\n");
	}
	stt = 1;
}

void datXeng(Nguoichoi *so, int n){
	int i;
	char check;
	for( i = 0; i < n; i++){
		do{
			printf("\n- %s's turn: please choose HIGH(1) or LOW(2): ", so[i].ten);
			scanf("%d", &so[i].chon);
			fflush(stdin);
		}while(so[i].chon != 1 && so[i].chon != 2);
		
		do{
			do{
				printf("GAMBLE ALL y/n? ");
				check = getchar();
				fflush(stdin);
				if(check != 'y' && check != 'n') printf("Please enter y(yes) or n(no)!\n");
			}while(check != 'y' && check != 'n');
			if(check == 'y'){
				so[i].dat = so[i].tien;
			}else{
				printf("Number of coins: ");
				scanf("%d", &so[i].dat);
				fflush(stdin);
			}
		}while(so[i].dat > so[i].tien || so[i].dat <= 0);
	}
}

bool checkSpecialCase(int sc, int *lac){
	int i;
	for(i = 0; i < 3; i++){
		if(lac[i] != sc) return false;
	}
	return true;
}

void lacXiNgauVaKetQua(Nguoichoi *so, int n, int *kq){
	int i, random, tong = 0, lac[3], sc;
	char kQ[3];
	system("cls");
	printf("SHAKING THE DICE . . . \n");
	for(i = 0; i < 3; i++){
		random = 1+rand()%6;
		sc = random;
		lac[i] = random;
		sleep(2);
		printf("______\n");
		printf("|    |\n");
		printf("| %d  |\n", random);
		printf("|____|\n\n");
		tong+= random;
	}
	
	if(tong >= 3 && tong <= 10){
		*kq = 2;
		strcpy(kQ, "LOW");
	}
	else if(tong >= 11 && tong <= 18) {
		*kq = 1;
		strcpy(kQ, "HIGH");
	}
	
	sleep(2);
	system("cls");
	printf("CALCULATING . . .");
	sleep(2);
	system("cls");
	
	printf("*********RESULT*********\n");
	printf("______\t______\t______\n");
	printf("|    |\t|    |\t|    |\n");
	printf("| %d  |\t| %d  |\t| %d  |\n", lac[0], lac[1], lac[2]);
	printf("|____|\t|____|\t|____|\n\n");
	
	if(checkSpecialCase(sc, lac) == true){
		printf("*********SPECIAL CASE*********\n");
		printf("------->House wins all\n");
		*kq = 0;
	}else printf("==========>[ %d ]==========>[ %s ]\n", tong, kQ);
	
	for( i = 0; i < n; i++){
		if(so[i].chon == *kq){
			printf("\nCONGRATZ '%s' for CORRECT choice!!!\n", so[i].ten);
			printf("Coin of '%s' = %d (+ %d) = ", so[i].ten, so[i].tien, so[i].dat);
			so[i].tien += so[i].dat;
			printf("%d\n", so[i].tien);
		}
		else if(so[i].chon != *kq){
			printf("\nSORRY '%s' for WRONG choice!!!\n", so[i].ten);
			printf("Coin of '%s' = %d (- %d) = ", so[i].ten, so[i].tien, so[i].dat);
			so[i].tien -= so[i].dat;
			printf("%d\n", so[i].tien);
		}
	}
}

void soTienHienTai(Nguoichoi *so, int n, int kq){
	int i;
	printf("\n-------------------------------RANKING-------------------------------\n");
	printf("|%-10s %-25s %-30s|\n", "Xep hang", "Ingame", "Tong so tien");
	for( i = 0; i < n; i++){
		
		printf("|%5d\t    %-25s %-13d", stt, so[i].ten, so[i].tien);
		if(kq == 0 || so[i].dat == 0) printf("\t\t    |\n");
		else if(so[i].dat > 0){
			if(so[i].chon == kq) printf("(+");
			else printf("(-");
			printf(" %-13d)|\n", so[i].dat);
		}
		stt++;
	}
	printf("|___________________________________________________________________|\n");
	stt = 1;
	for( i = 0; i < n; i++){
		so[i].dat = 0;
	}
}

void rank(Nguoichoi *so, int n){
	int i, j;
	Nguoichoi temp;
	for(i = 0; i < n-1; i++){
		for( j = i+1; j < n; j++){
			if(so[i].tien < so[j].tien){
				temp = so[i];
				so[i] = so[j];
				so[j] = temp;
			}
		}
	}
}

void loaiNguoiChoiHetTien(Nguoichoi *so, int *n){
	int i, count = 0, check = 1, dem = 0, num;
	for(i = 0; i < (*n); i++){
		if(so[i].tien == 0) count++;
	}
	do{
		printf("\nIn total, %d player(s) ran out of coins:\n", count);
		for(i = 0; i < (*n); i++){
			if(so[i].tien == 0) printf("(%d) %s\n", stt++, so[i].ten);  
		}
		do{
			printf("Enter number of player want to buy coin(0 to exit): ");
			scanf("%d", &num);
			fflush(stdin);
			if(num < 0 || num > count) printf("Invalid input!\n");
		}while(num < 0 || num > count);
		rank(so, *n);
		if(num == 0){
			*n -= count;
			stt = 1;
			break;
		}else{
			for(i = 0; i < (*n); i++){ 
				if(so[i].tien == 0){
					dem++;
					if(dem == num){
						buyCoin(&so[i], &check);
						if(check != 0){
							count -= 1;
						}
					}
				}
			}
		}
		dem = 0;
		stt = 1;
	}while(count > 0);
	printf("Remained player(s): %d\n", *n);
}

void luuFile(FILE *out, Nguoichoi *so, int n){	
	int i;
	out = fopen("data.txt", "w");
	if (n > 0) {
		fprintf(out, "%d\n", n);
		for( i = 0; i < n; i++){
			fprintf(out, "%d %s\n", so[i].tien, so[i].ten);
		}
	}
	fclose(out);
}

int main(){	
	printf("****WELCOME TO CHINESE DICE DEVELOPED BY KHANG****\n");
	int chon, n = 0, i, temp, check, kq = 0;
	FILE *in, *out;
	char useData, choice;
	Nguoichoi *so;
	bool getData = false, start = false;
	srand(time(NULL));
	
	in = fopen("data.txt", "r");
	if(in != NULL){
		fscanf(in, "%d", &n);
		if (n > 0) {
			do{
				printf("Continue with previous data y/n? ");
				useData = getchar();
				fflush(stdin);
				if(useData != 'y' && useData != 'n') printf("Please enter y(yes) or n(no)!\n");
			}while(useData != 'y' && useData != 'n');
			if(useData == 'y'){
				so = (Nguoichoi* )malloc(n*sizeof(Nguoichoi));
				for( i = 0; i < n; i++){
					fscanf(in, "%d %[^\n]", &so[i].tien, so[i].ten);
				}
				getData = true;
				soTienHienTai(so, n, kq);
			}
		}
	}
	if (getData == false) n = 0;
	fclose(in);
	
	do{
		printf("\n--------Menu--------\n");
		printf("1.Start.");
		if(getData == false && n <= 0) printf("(No player)\n");
		else printf("\n");
		printf("2.Add player.\n3.Save and exit.\n4.Buy coins\n");
		do{
			printf("Your choice: ");
			scanf("%c", &choice);
			fflush(stdin);
			if(!(choice >= '0' && choice <= '9')) printf("Please enter number!\n");
		}while(!(choice >= '0' && choice <= '9'));
		chon = choice - '0';
		printf("\n");
		switch(chon){
			case 1:
				system("cls");
				if(n == 0){
					printf("There must be at least 1 player to start the game!\n");
					break;
				}
				soTienHienTai(so, n, kq);
				datXeng(so, n);
				lacXiNgauVaKetQua(so, n, &kq);
				rank(so, n);
				loaiNguoiChoiHetTien(so, &n); 
				rank(so, n);
				soTienHienTai(so, n, kq);
				if(n > 0) luuFile(out, so, n);
				break;
					
			case 2:
				system("cls");
				do{
					printf("Number of player want to add: ");
					scanf("%d", &temp);
					fflush(stdin);
					if(temp <= 0) printf("You must add at lease 1 player!\n");
				}while(temp <= 0);
				check = n;
				n += temp;
				if(check == 0){
					so = (Nguoichoi*)malloc(n*sizeof(Nguoichoi));
				}else{
					so = (Nguoichoi*)realloc(so, n*sizeof(Nguoichoi));
				}
				themNguoiChoiMoi(so, n, check, temp);
				rank(so, n);
				soTienHienTai(so, n, kq);
				break;
					
			case 3:
				system("cls");
				luuFile(out, so, n);
				printf("Data saved\n");
				printf("Thank you for choosing our services! Hope to see you again <3");
				break;
					
			case 4:
				system("cls");
				if(n == 0){
					printf("There is no player!\n");
				}
				else{
					soTienHienTai(so, n, kq);
					napTien(so, n);
					rank(so, n);
					system("cls");
					soTienHienTai(so, n, kq);
				}
				break;
			
			default:
				if(chon != 3){
					system("cls");
					printf("Invalid choice!!! Please choose again!!!\n\n");
				}
		}
	}while(chon != 3);
	free(so);
	return 0;
}
