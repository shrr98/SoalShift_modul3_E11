
Code
Issues 0
Pull requests 0
Projects 0
Insights
Jawaban soal shift modul3 Sistem Operasi Kelompok E11
<h1>LAPORAN SOAL SHIFT MODUL 3</h1>
<div>
  <h3>KELOMPOK E 11</h3>
  <p>05111740000017 Shintya Rezky R.</p>
  <p>05111740000182 Arif Darma A.</p>
</div>

<hr>

<h3>Nomor 1</h3>
<ol>
  <li>
    <p align="justify">
    Membuat tipe data baru Pair untuk menyimpan pasangan angka (num) dan hasil faktorialnya (faktorial).
    </p>
    
```c

typedef struct {
    int num;
    unsigned long long faktorial;
} Pair;

```
  </li>
  <li>
    <p align="justify">
      Membuat fungsi untuk menghitung faktorial yang akan dijalankan thread dengan parameter bertipe Pair*.
    </p>
  
```c

void* faktorial(void* x){
    Pair *number =  (Pair*) x;
    unsigned long long fakt=1;
    int o;
    for(o=2; o <= number->num; o++){
        fakt*=o;
    }
    number->faktorial = fakt;
}

```

  </li>
  <li>
    <p align="justify">
      Membuat fungsi untuk mengurutkan pair secara ascending order.
    </p>

```c

void sort(Pair* number, int n){
    int i, o;
    for(i=0; i<n-1; i++){
        for(o=0; o<n-i-1; o++){
            if(number[o].num > number[o+1].num){
                Pair temp = number[o];
                number[o] = number[o+1];
                number[o+1] = temp;
            }
        }
    }
}

```

  </li>
  
  <li>
    <p align="justify">
      Membuat fungsi untuk menampilkan hasil faktorial pada array of Pair yang telah terurut.
    </p>
  
```c

void print(Pair* number, int n){
    int i;
    for(i=0; i<n; i++){
        printf("%d! = %llu\n", number[i].num, number[i].faktorial);
    }
}

```

  </li>
  
  <li>
    <p align="justify">
      Pada fungsi main, simpan arguments ke atribut num dari masing-masing element array bertipe Pair (yaitu variable number). Kemudian, buat thread sebanyak jumlah argumen yang masing-masing menjalankan fungsi faktorial dengan parameter number[i]. Join setiap thread pada fungsi main agar fungsi main menunggu seluruh thread selesai sebelum menjalankan baris berikutnya. Kemudian, urutkan hasil faktorial dan tampilkan hasilnya dengan memanggil fungsi print.
    </p>
  
```c

int main(int argc, char **argv){
    int n = argc - 1;
    Pair number[n];
    int i;
    pthread_t tid[n];

    for(i=0; i<n; i++){
        number[i].num = atoi(argv[i+1]);
        number[i].faktorial = 1;
        pthread_create(&tid[i], NULL, faktorial, &number[i]);
    }

    for(i=0; i<n; i++){
        pthread_join(tid[i], NULL);
    }

    sort(number, n);
    print(number, n);
    return 0;

}

```

  </li>
</ol>

<br>

<h3>Nomor 2</h3>
<ol>
  <li>
    <p align="justify">
    </p>
    
```c

```

  </li>
    <li>
    <p align="justify">
    </p>
    
```c

```

  </li>
</ol>

<br>

<h3>Nomor 3</h3>
<ol>
  <li>
    <p align="justify">
	    Inisiasi terdapat 3 buah thread yang selalu berjalan. Dimana tid[0] untuk thread yang menampilkan semua status, tid[1] untuk perintah Agmal Ayo Bangun, dan tid[3] untuk perintah Iraj Ayo Tidur.
    </p>
    
```c
    pthread_create(&(tid[0]),NULL,&savefile,NULL);
    pthread_create(&(tid[1]),NULL,&savefile,NULL);
    pthread_create(&(tid[2]),NULL,&savefile,NULL);
```

  </li>
    <li>
    <p align="justify">
	    Ketika tid[0] menampilkan status, tid[1] menambahkan WakeUp_Status sebesar 15 point, dan tid[2] mengurangi Spirit_Status sebesar 20 point.
    </p>
    
```c
if(pthread_equal(id,tid[0]))
	{   
        while(1){
            while(i!=0){}
            printf("WakeUp_Status :%d\nSpirit_Status :%d\n",WakeUp_Status,Spirit_Status);
            i=3;
        }
    }else if(pthread_equal(id,tid[1]))
	{
        while(1){
            while(i!=1){}
            if(cAgmal!=3){
                WakeUp_Status=WakeUp_Status+15;
                printf("WakeUp_Status :%d\n",WakeUp_Status);
		}
	}
    } else if(pthread_equal(id,tid[2]))
    {
        while(1){
            while(i!=2){}
            if(cIraj!=3){
                Spirit_Status=Spirit_Status-20;
                printf("Spirit_Status :%d\n",Spirit_Status);
		}
	}
     }
```

  </li>
    <li>
    <p align="justify">
	    Ketika Agmal Ayo Bangun dijalankan sebanyak 3 kali maka Iraj Ayo Tidur di disabled selama 10 s. Begitu pula sebaliknya. Maka di masing masing thread diberi counter agar ketika telah dijalankan sebanyak tiga kali maka thread lainnya di sleep selama 10 detik.
    </p>
    
```c
else if(pthread_equal(id,tid[1]))
	{
        while(1){
            while(i!=1){}
            if(cAgmal!=3){
                WakeUp_Status=WakeUp_Status+15;
                printf("WakeUp_Status :%d\n",WakeUp_Status);
                if(WakeUp_Status>=100){
                    i=3;
                }
                cIraj++;
                if(cIraj==3){
                    i=2;
                    continue;
                }
            } else if(cAgmal==3){
                cAgmal=0;
                printf("Iraj Ayo Tidur disabled 10 s\n");
                iBangun=1;
                i=3;
                sleep(10);
                iBangun=0;
            }i=3;
        }
    }
    else if(pthread_equal(id,tid[2]))
    {
        while(1){
            while(i!=2){}
            if(cIraj!=3){
                Spirit_Status=Spirit_Status-20;
                printf("Spirit_Status :%d\n",Spirit_Status);
                if(Spirit_Status<=0){
                    i=3;
                }
                cAgmal++;
                if(cAgmal==3){
                    i=1;
                    continue;
                }
            } else if(cIraj==3){
                printf("Agmal Ayo Bangun disabled 10 s\n");
                cIraj=0;
                aTidur=1;
                i=3;
                sleep(10);
                aTidur=0;
            }i=3;
        }
    }
```
  </li>
    <li>
    <p align="justify">
	    Jika WakeUp_Status lebih besar atau sama dengan 100 maka program keluar dan mengeprint "Agmal Terbangun,mereka bangun pagi dan berolahraga" atau jika Spirit_Status lebih kecil atau sama dengan 0 maka program keluar dan mengeprint "Iraj ikut tidur, dan bangun kesiangan bersama Agmal"
    </p>
    
```c
if(WakeUp_Status>=100){
            printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");
            break;
        }else if(Spirit_Status<=0){
            printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            break;
        }
```

  </li>
  <li>
    <p align="justify">
	    Disetiap thread diberi flag atau penanda agar thread mana yang akan diakses dan pada main diberi flag juga agar setiap setelah menjalankan thread kembali ke main lagi seperti dibawah ini
    </p>
    
```c
void* savefile(void *arg){
	pthread_t id=pthread_self();
	if(pthread_equal(id,tid[0]))
	{   
        while(1){
            while(i!=0){}
            printf("WakeUp_Status :%d\nSpirit_Status :%d\n",WakeUp_Status,Spirit_Status);
            i=3;
        }
    }
	else if(pthread_equal(id,tid[1]))
	{
        while(1){
            while(i!=1){}
            if(cAgmal!=3){
                WakeUp_Status=WakeUp_Status+15;
                printf("WakeUp_Status :%d\n",WakeUp_Status);
                if(WakeUp_Status>=100){
                    i=3;
                }
                cIraj++;
                if(cIraj==3){
                    i=2;
                    continue;
                }
            } else if(cAgmal==3){
                cAgmal=0;
                printf("Iraj Ayo Tidur disabled 10 s\n");
                iBangun=1;
                i=3;
                sleep(10);
                iBangun=0;
            }i=3;
        }
    }
    else if(pthread_equal(id,tid[2]))
    {
        while(1){
            while(i!=2){}
            if(cIraj!=3){
                Spirit_Status=Spirit_Status-20;
                printf("Spirit_Status :%d\n",Spirit_Status);
                if(Spirit_Status<=0){
                    i=3;
                }
                cAgmal++;
                if(cAgmal==3){
                    i=1;
                    continue;
                }
            } else if(cIraj==3){
                printf("Agmal Ayo Bangun disabled 10 s\n");
                cIraj=0;
                aTidur=1;
                i=3;
                sleep(10);
                aTidur=0;
            }i=3;
        }
    }	
}

int main() 
{
    i=3;
    int x;
    int counter1=0;
    int counter2=0;
	int err;
    pthread_create(&(tid[0]),NULL,&savefile,NULL);
    pthread_create(&(tid[1]),NULL,&savefile,NULL);
    pthread_create(&(tid[2]),NULL,&savefile,NULL);
    printf("1. All Status\n2. Agmal Ayo Bangun\n3. Iraj Ayo Tidur\n\nInput :");
	while(1) 
	{
        while(i!=3){}
        if(WakeUp_Status>=100){
            printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");
            break;
        }else if(Spirit_Status<=0){
            printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            break;
        }
        scanf("%d",&x);
        if(x==1){
            i=0;
        } else if(x==2 && !iBangun){
            i=1;
        } else if(x==3 && !aTidur){
            i=2;           
        }
	}
	exit(0);
	return 0;
}
```

  </li>
</ol>

<br>

<h3>Nomor 4</h3>
<ol>
  <li>
    <p align="justify">
      Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Maka pertama-tama buat directory tujuan yaitu /home/[user]/Documents/FolderProses1 dan /home/[user]/Documents/FolderProses2. Berarti menggunakan ps -aux yang di pipe ke head disimpan pada SimpanProses1.txt pada folder FolderProses1 dan SimpanProses2.txt pada folder FolderProses2
    </p>
    
```c
system("mkdir /home/arifdarma/Documents/FolderProses1");
system("ps -aux | head > /home/arifdarma/Documents/FolderProses1/SimpanProses1.txt");

pada thread yang lain buat :

system("mkdir /home/arifdarma/Documents/FolderProses2");
system("ps -aux | head > /home/arifdarma/Documents/FolderProses1/SimpanProses2.txt");
```

  </li>
    <li>
    <p align="justify">
      Setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus
    </p>
    
```c
system("zip -jm /home/arifdarma/Documents/FolderProses1/KompresProses1.zip /home/arifdarma/Documents/FolderProses1/SimpanProses1.txt");

pada thread yang lain buat juga :

system("zip -jm /home/arifdarma/Documents/FolderProses2/KompresProses2.zip /home/arifdarma/Documents/FolderProses2/SimpanProses2.txt");
```

  </li>
    <li>
  <p align="justify">
  Setelah file di zip, program akan menunggu selama 15 detik dan setelah 15 detik file di unzip
  </p>

```c
 sleep(15);
 system("unzip /home/arifdarma/Documents/FolderProses1/KompresProses1.zip -d /home/arifdarma/Documents/FolderProses1/");
 
 Dan pada thread lain :
 sleep(15);
 system("unzip /home/arifdarma/Documents/FolderProses2/KompresProses2.zip -d /home/arifdarma/Documents/FolderProses2/");
```
  </li>
   <li>
  <p align="justify">
  Maka threadnya akan menjalankan program berikut. Jika id=1 maka thread tid[1] dijalankan dan jika id=2 maka thread tid[2] dijalankan.
  </p>

```c
if(pthread_equal(id,tid[0]))
	{
		system("mkdir /home/arifdarma/Documents/FolderProses1");
		system("ps -aux | head > /home/arifdarma/Documents/FolderProses1/SimpanProses1.txt");
		system("zip -jm /home/arifdarma/Documents/FolderProses1/KompresProses1.zip /home/arifdarma/Documents/FolderProses1/SimpanProses1.txt");
		sleep(15);
		system("unzip /home/arifdarma/Documents/FolderProses1/KompresProses1.zip -d /home/arifdarma/Documents/FolderProses1/");
	}
	else if(pthread_equal(id,tid[1]))
	{
		system("mkdir /home/arifdarma/Documents/FolderProses2");
		system("ps -aux | head > /home/arifdarma/Documents/FolderProses2/SimpanProses2.txt");
		system("zip -jm /home/arifdarma/Documents/FolderProses2/KompresProses2.zip /home/arifdarma/Documents/FolderProses2/SimpanProses2.txt");
		sleep(15);
		system("unzip /home/arifdarma/Documents/FolderProses2/KompresProses2.zip -d /home/arifdarma/Documents/FolderProses2/");
	}
```
  </li>
  <li>
  <p align="justify">
  Pada mainnya dilakukan pthread_join agar menunggu semua thread yang dijoin selesai terlebih dahulu agar id=1 dan id=2 bisa dijalankan bersamaan.
  </p>

```c
pthread_join(tid[0],NULL);
pthread_join(tid[1],NULL);
```
  </li>
</ol>

<br>

<h3>Nomor 5</h3>
<ol>
  <li>
    <p align="justify">
    </p>
    
```c

```

  </li>
    <li>
    <p align="justify">
    </p>
    
```c

```

  </li>
</ol>
