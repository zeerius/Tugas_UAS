#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Data_Les{        
	char Nama[25];
	char Sekolah[25];
	int Kelas;
	char No_Hp[15];
	char Program[10];
	char Biaya[20];
	char Status[10];
}data;
data array[1000];           //array bertipe struct untuk menampung data dari file
int i_data;                 //sebagai indeks akhir array

int login();
void process();
void read(int , int);
int search(int);
void add();
void update(int);
void new_login();
void rewrite();
void deletee(int);

int main(int argc, char const *argv[])
{
    printf("\n\t      .:.  Selamat Datang  .:.\n");
    printf(">>>>>>>  Di Portal Data Pendaftaran Bimbel  <<<<<<<\n");
	printf("\nLOGIN :\n");
    while(1){
   		if(login()){           //jika username atau password salah, user harus login ulang
   			break;
    	}
    }
    printf("\n>>>>>>>  Selamat Datang Admin  <<<<<<<\n");
    process();
    int choice;

    Menu :
    printf("\n============ Menu ============\n");
    printf("1. Tampilkan Data\n");
    printf("2. Cari Data\n");
    printf("3. Tambah Data\n");
    printf("4. Hapus Data\n");
    printf("5. Ubah Data\n");
    printf("6. Ganti Username dan Password\n");
    printf("7. Selesai\n");
    printf("==============================\n");
    printf("\nPilihan : "); scanf("%d", &choice);
    int cek;
    switch(choice){
    	case 1 : read(0, i_data); goto Menu;
    	case 2 :  
            printf("\n#CARI DATA\n");
            if(!(cek = search(0))){
                printf("\n==! Data Tidak Ditemukan !==\n\n");
            }
            goto Menu;
    	case 3 : add(); goto Menu;
    	case 4 : 
            printf("\n#HAPUS DATA\n");
            if(!(cek = search(2))){     //mengecek apakah nama yang diinput ada dalam data atau tidak
                printf("\n==! Nama Tidak Ditemukan, Tidak Dapat Menghapus Data !==\n\n");
                goto Menu;
            }else{
                char pilih;
                printf("Yakin Ingin Menghapus %s? (y/n) : ", array[cek].Nama); scanf(" %c", &pilih);
                if(tolower(pilih) == 'y'){
                    deletee(cek); 
                }    
                goto Menu;
            }
    	case 5 : 
            printf("\n#UBAH DATA\n");
            if(!(cek = search(2))){     //mengecek apakah nama yang diinput ada dalam data atau tidak
                printf("\n==! Nama Tidak Ditemukan, Tidak Dapat Mengubah Data !==\n\n");
                goto Menu;
            }else{
                update(cek); 
                goto Menu;
            }  
    	case 6 : new_login(); goto Menu;
    	case 7 : printf("\nProgram Selesai\n"); break;
    	default : printf("\nPilihan tidak ditemukan\n"); goto Menu;
    }

    return 0;
}

int login(){        //melakukan proses login
    FILE * fbp = fopen("../UAS_1908107010028/data/login.bin", "rb");
    if(fbp == NULL){
    	printf("ERROR READING FILE!!!\n");
    	return 1;
    }
    char a[40], b[40], c[20];
    fread(a, sizeof(char), 40, fbp);

    printf("Username : "); scanf(" %[^\n]", b); strcat(b, " ");     //ditambahkan spasi karena format file binary ada spasi diantara  username dan password (Admin_Zaidan zzz310102)
    printf("Password : "); scanf(" %[^\n]", c); strcat(b, c);

    if(strcmp(a, b) != 0){      //inputan user dibandingkan dengan data yang ada dalam file binary
    	printf("Status\t : Username atau Password Salah\n\n");
    	return 0;
    }
    printf("Status\t : Login Berhasil\n");

    fclose(fbp);

    return 1;
}

void process(){     //memproses file txt dan ditampung ke dalam array bertipe struct
	FILE * read = fopen("../UAS_1908107010028/data/data.txt", "r");

	i_data = 0;
    char baris[100];
    char koma[3] = "#;";            //pada file txt, pemisahnya menggunakan '#' dan ';'
    char * pch;
    fgets(baris, 100, read);        //mengambil baris pertama yang tidak diperlukan
    int hitung;

    while(!feof(read)){
    	hitung = 1;
    	fgets(baris, 100, read);       //mengambil baris per baris
    	pch = strtok(baris, koma);     //memenggal berdasarkan pemisah '#' dan ';'
    	while(pch != NULL){
    		if(hitung == 1){
    			strcpy(array[i_data].Nama, pch);
    		}else if(hitung == 2){
    			strcpy(array[i_data].Sekolah, ++pch);    //pointer diincreament karena diawalnya masi ada spasi
    		}else if(hitung == 3){
    			array[i_data].Kelas = atoi(pch);
    		}else if(hitung == 4){
    			strcpy(array[i_data].No_Hp, ++pch);
    		}else if(hitung == 5){
    			strcpy(array[i_data].Program, ++pch);
    		}else if(hitung == 6){
    			strcpy(array[i_data].Biaya, ++pch);
    		}else if(hitung == 7){
    			strcpy(array[i_data].Status, ++pch);
    		}
        	pch = strtok(NULL, koma);
        	hitung++;
    	}
    	i_data++;
    }

    fclose(read);
}

void read(int awal, int batas){     //variabel awal sebagai data awal yang ditampilkan, variabel batas sebagai batas loop
    printf("\n#DATA\n");
    printf("+------+----------------------+---------------------+-------+---------------+-----------+-------------+--------+\n");
    printf("|  No  |         Nama         |       Sekolah       | Kelas |     No.HP     |  Program  |    Biaya    | Status |\n");
    printf("+------+----------------------+---------------------+-------+---------------+-----------+-------------+--------+\n");
    for(int m = awal; m < batas; m++){
        printf("| %-4d | %-20s | %-20s|   %-4d| %-14s| %-10s| %-12s| %-7s|\n", m+1, array[m].Nama, array[m].Sekolah, array[m].Kelas, array[m].No_Hp, array[m].Program, array[m].Biaya, array[m].Status);
    }	
    printf("+------+----------------------+---------------------+-------+---------------+-----------+-------------+--------+\n");
}

int search(int sign){       //variabel sign digunakan untuk membedakan kegunaan fungsi search 
	char Cari_Nama[50];
    printf("o> Nama Lengkap\t\t: "); scanf(" %[^\n]", Cari_Nama);
    for(int j = 0; j < i_data; j++){
    	if(strcmp(array[j].Nama, Cari_Nama) == 0){
            if(sign == 1){      //nilai sign = 1, berarti fungsi search() digunakan untuk fungsi add()
                return 1;
            }else if(sign == 2){    //nilai sign = 2, berarti fungsi search() digunakan untuk fungsi update() dan deletee()
                return j;
            }
            printf("\n=== Data Ditemukan ===\n\nHasil Pencarian :");        //nilai sign = 0, berarti fungsi search() digunakan pada menu 2
            read(j, j+1);
            return 2;
    	}
    }
    if(sign == 1){
        strcpy(array[i_data].Nama, Cari_Nama);
    }
    return 0;
}

void add(){         //melakukan penambahan data pada struct maupun file txt
    int cek;
	printf("\n#TAMBAH DATA\n");
    while(1){                           //ika namanya sama dengan nama yang ada di data, maka user akan diminta untuk menginput ulang nama yang akan di tambahkan
        if((cek = search(1))){          //berarti user tidak boleh menginput data dengan nama yang sama
            printf("==! Nama sudah ada, Silahkan input nama lain !==\n");
        }else{
            break;
        }
    }
    printf("o> Asal Sekolah\t\t: "); scanf(" %[^\n]", array[i_data].Sekolah);
    while(1){
        printf("o> Kelas (1-12)\t\t: "); scanf(" %d", &array[i_data].Kelas);
        if((array[i_data].Kelas >= 1) && (array[i_data].Kelas <= 12)){          //user harus menginput angka antar 1 sampai 12 untuk kelas
            break;
        }else{
            printf("==! Kelas Tidak Valid !==\n");
        }
    }
    printf("o> No Hp\t\t: "); scanf(" %[^\n]", array[i_data].No_Hp);
    printf("o> Program\t\t: "); scanf(" %[^\n]", array[i_data].Program);
    printf("o> Biaya\t\t: "); scanf(" %[^\n]", array[i_data].Biaya);
    printf("o> Status (Lunas/Kredit): "); scanf(" %[^\n]", array[i_data].Status);   

    FILE * tambah = fopen("../UAS_1908107010028/data/data.txt", "a");     //pada file akan di tambahkan data baru pada baris terakhir
    fprintf(tambah, "\n%s# %s# %d# %s# %s# %s# %s;", array[i_data].Nama, array[i_data].Sekolah, array[i_data].Kelas, array[i_data].No_Hp, array[i_data].Program, array[i_data].Biaya, array[i_data].Status);
    fclose(tambah);
    i_data++;

    printf("\n=== Data Berhasil Ditambahkan ===\n");
    read(0, i_data);
}

void deletee(int i_hapus){          //menghapus data yang ada dalam struct
    for(; i_hapus < i_data; i_hapus++){
        array[i_hapus] = array[i_hapus+1];      //data yang akan dihapus akan ditimpa dengan data di bawahnya
    }                                           //semua data dibawahnya akan naik 1 baris
    i_data--;

    printf("\n=== Data Berhasil Dihapus ===\n");
    rewrite();          //menulis ulang data-data terbaru kedalam file txt 
    read(0, i_data);
}

void update(int i_ubah){            //mengubah data yang ada dalam struct
    char pilih;
    char sesuatu[50];
    int newclass;

    printf("\nApakah ingin mengubah Nama?    (y/n) : "); scanf(" %c", &pilih);
    if(tolower(pilih) == 'y'){
        printf("o> Nama Baru : "); scanf(" %[^\n]", sesuatu);
        strcpy(array[i_ubah].Nama, sesuatu);
    }
    printf("Apakah ingin mengubah Sekolah? (y/n) : "); scanf(" %c", &pilih);
    if(tolower(pilih) == 'y'){
        printf("o> Sekolah Baru : "); scanf(" %[^\n]", sesuatu);
        strcpy(array[i_ubah].Sekolah, sesuatu);
    }
    printf("Apakah ingin mengubah Kelas?   (y/n) : "); scanf(" %c", &pilih);
    if(tolower(pilih) == 'y'){
        while(1){
            printf("o> Kelas Baru (1-12) : "); scanf(" %d", &newclass);
            if((newclass >= 1) && (newclass <= 12)){
                break;
            }else{
                printf("==! Kelas Tidak Valid !==\n");
            }
        } 
        array[i_ubah].Kelas = newclass;
    }
    printf("Apakah ingin mengubah No_Hp?   (y/n) : "); scanf(" %c", &pilih);
    if(tolower(pilih) == 'y'){
        printf("o> No_Hp Baru : "); scanf(" %[^\n]", sesuatu);
        strcpy(array[i_ubah].No_Hp, sesuatu);
    }
    printf("Apakah ingin mengubah Program? (y/n) : "); scanf(" %c", &pilih);
    if(tolower(pilih) == 'y'){
        printf("o> Program Baru : "); scanf(" %[^\n]", sesuatu);
        strcpy(array[i_ubah].Program, sesuatu);
    }
    printf("Apakah ingin mengubah Biaya?   (y/n) : "); scanf(" %c", &pilih);
    if(tolower(pilih) == 'y'){
        printf("o> Biaya Baru : "); scanf(" %[^\n]", sesuatu);
        strcpy(array[i_ubah].Biaya, sesuatu);
    }
    printf("Apakah ingin mengubah Status?  (y/n) : "); scanf(" %c", &pilih);
    if(tolower(pilih) == 'y'){
        printf("o> Status Baru (Lunas/Kredit) : "); scanf(" %[^\n]", sesuatu);
        strcpy(array[i_ubah].Status, sesuatu);
    }
    printf("\n=== Data Berhasil Diubah ===\n");
    rewrite();              //menulis ulang data-data terbaru kedalam file txt
    read(0, i_data);
}

void new_login(){           //mengganti username dan password
    char baru[40], pass[20];
    printf("\n#Mengganti Username dan Password\n");
    printf("Masukkan Username Baru : "); scanf(" %[^\n]", baru); strcat(baru, " ");
    printf("Masukkan Password Baru : "); scanf(" %[^\n]", pass); strcat(baru, pass);

    FILE * neww = fopen("../UAS_1908107010028/data/login.bin", "wb");         
    fwrite(baru, sizeof(char), 40, neww);                           //menulis ulang data login terbaru ke dalam file binary
    fclose(neww);

    printf("\n=== Berhasil Mengganti Username dan Password ===\n");
    printf("\n=== Silahkan Login Ulang ===\n");

    while(1){
        if(login()){        //melakukan login ulang setelah mengganti data login
            break;
        }
    }
}

void rewrite(){             //menulis ulang data-data terbaru ke dalam file txt
	FILE * rewrite = fopen("../UAS_1908107010028/data/data.txt", "w");
    fputs("Nama# Sekolah# Kelas# No_Hp# Program# Biaya# Status;\n", rewrite);
    for(int ind = 0; ind < i_data; ind++){
    	fprintf(rewrite, "%s# %s# %d# %s# %s# %s# %s;", array[ind].Nama, array[ind].Sekolah, array[ind].Kelas, array[ind].No_Hp, array[ind].Program, array[ind].Biaya, array[ind].Status);
    	if(ind != i_data-1){
    		fputc('\n', rewrite);         //agar data terakhir tidak perlu ditambahkan newline diakhirnya
    	}
    }
    fclose(rewrite);
}