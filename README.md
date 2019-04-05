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
<h5>Server Penjual</h5>
<ol>
  <li>
    <p align="justify">Menggunakan shared memory sebagai IPC dengan server pembeli. Inisialisasi shared memory dilakukan pada fungsi main. Kemudian buat 2 thread untuk menjalankan server dan printStock secara parallel. Kemudian join thread1 dan thread2.
    </p>
    
```c

int main(int argc, char const *argv[]) 
{ 
    pthread_t tid[2];

    key_t key = ftok("stok",65); 

    // shmget returns an identifier in shmid 
    shmid = shmget(key,1024,0666|IPC_CREAT); 
   

    //pthread_create(&tid[1], NULL, printStock, NULL);
    pthread_create(&tid[0], NULL, &server, NULL);
    pthread_create(&tid[1], NULL, printStock, NULL);
    
    pthread_join(tid[0], NULL);
} 

```

  </li>
    <li>
    <p align="justify">
	    Membuat fungsi server untuk koneksi ke socket sebagai IPC dengan client. Setiap ada query/message dari client, panggil fungsi 'jual' untuk melakukan proses penjualan.
    </p>
    
```c

void* server(void* x){
    int server_fd, client, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[8] = {0}; 
    char *respon[] = {"transaksi gagal", "transaksi berhasil"}; 

     // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    while(1){
        if (listen(server_fd, 1) < 0) 
        { 
            perror("listen"); 
            exit(EXIT_FAILURE); 
        } 
        if ((client = accept(server_fd, (struct sockaddr *)&address,  
                        (socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
            exit(EXIT_FAILURE); 
        } 
        valread = read( client , buffer, 8);
        int sukses = jual(buffer);
        send(client , respon[sukses] , strlen(respon[sukses]) , 0 ); 
        printf("%s\n", buffer);
        printf("%s\n", respon[sukses]); 
    }
    return NULL;
}

```

  </li>
  <li>
    <p align="justify">
	    Membuat fungsi jual untuk melakukan proses penjualan. jika query yang diterima adalah "tambah", maka attach ke shared memory untuk mengubah jumlah stock yang tersimpan pada shared memory.
    </p>
    
```c

int jual(char *buffer){
    if( (strcmp(buffer, "tambah"))==0 ){
        int *shared_mem = (int*) shmat(shmid,(void*)0,0); 

        // change stok
        if(shared_mem != NULL){
            *shared_mem = (*shared_mem) +1;
            shmdt(shared_mem); 
            return 1;
        }
        else printf("shared memory gagal");
    }
    return 0;
}

```

  </li>
  <li>
    <p align="justify">
	    Membuat fungsi printStock yang akan dijalankan thread 2. Pada fungsi printStock, attach ke shared memory untuk membaca jumlah stock untuk ditampilkan pada stdout.
    </p>
    
```c

void* printStock(void* x){
    int* shared_mem;
    while(1){
        shared_mem = (int*) shmat(shmid,(void*)0,0);
        if(shared_mem!=NULL){
            printf("Stok : %d\n", *shared_mem);
        }
        shmdt(shared_mem);
        sleep(5);
    }

    return NULL;
}

```

  </li>
</ol>

<h5>Server Pembeli</h5>
<ol>
  <li>
    <p align="justify">Menggunakan shared memory sebagai IPC dengan server penjual. Inisialisasi shared memory dilakukan pada fungsi main. Kemudian jalankan server.
    </p>
    
```c

int main(int argc, char const *argv[]) 
{ 
 

    key_t key = ftok("stok",65); 
  
    // shmget returns an identifier in shmid 
    shmid = shmget(key,1024,0666|IPC_CREAT); 
  
    server();
       
   
    return 0; 
} 

```

  </li>
    <li>
    <p align="justify">
	    Membuat fungsi server untuk koneksi ke socket sebagai IPC dengan client. Setiap ada query/message dari client, panggil fungsi 'beli' untuk melakukan proses penjualan.
    </p>
    
```c

void server(){
    int server_fd, client, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[5] = {0}; 
    char *respon[] = {"transaksi gagal", "transaksi berhasil"}; 

     // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    while(1){
        if (listen(server_fd, 1) < 0) 
        { 
            perror("listen"); 
            exit(EXIT_FAILURE); 
        } 
        if ((client = accept(server_fd, (struct sockaddr *)&address,  
                        (socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
            exit(EXIT_FAILURE); 
        } 
        valread = read( client , buffer, 5);
        int sukses = beli(buffer);
        send(client , respon[sukses] , strlen(respon[sukses]) , 0 ); 
        printf("%s\n", respon[sukses]); 
    }
}

```

  </li>
  <li>
    <p align="justify">
	    Membuat fungsi beli untuk melakukan transaksi pembelian. Jika query yang diterima adalah "beli", maka attach ke shared memory untuk mengubah jumlah stock yang tersimpan pada shared memory. Fungsi beli akan mengembalikan nilai 1 jika transaksi berhasil, yaitu jika stock masih tersedia.
    </p>
    
```c

int beli(char *buffer){
    if( (strcmp(buffer, "beli"))==0 ){
        int *shared_mem = (int*) shmat(shmid,(void*)0,0); 

        // change stok
        if(shared_mem != NULL && *shared_mem>0){
            *shared_mem = (*shared_mem) -1;
            shmdt(shared_mem); 
            return 1;
        }
    }
    return 0;
}

```

  </li>
</ol>

<h5>Client</h5>
<ol>
  <li>
    <p align="justify">
	    Client mengirimkan query yang diperoleh dari stdin. Jika query adalah 'tambah', maka client akan terkoneksi ke server penjual (PORT_J). Jika query adalah 'beli', maka client akan terkoneksi ke server pembeli (PORT_B). Jika query tidak valid, maka continue (ignored).
    </p>
    
```c

scanf("%s", query);
if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
{ 
    printf("\n Socket creation error \n"); 
    return -1; 
} 

memset(&serv_addr, '0', sizeof(serv_addr)); 

serv_addr.sin_family = AF_INET;
if( (strcmp(query, "beli"))==0 ){
    serv_addr.sin_port = htons(PORT_B); 
    valid = 1;
}
else if( (strcmp(query, "tambah"))==0 ){
    serv_addr.sin_port = htons(PORT_J); 
    valid = 1;
}


if (!valid)
    continue;
	
```

  </li>
    <li>
    <p align="justify">
	    Membuat koneksi ke socket dengan server sesuai query dan membaca message dari server kemudian menampilkannya ke stdout. Setelah itu, close connection dengan server agar dapat melakukan koneksi lain.
    </p>
    
```c

if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
{ 
    printf("\nInvalid address/ Address not supported \n"); 
    return -1; 
} 

if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
{ 
    printf("\nConnection Failed \n"); 
    return -1; 
} 
send(sock , query , strlen(query) , 0 );
valread = read( sock , buffer, sizeof(buffer)); 
printf("%s\n",buffer ); 
close(sock);
	
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
	    Membuat class Monster yang memiliki atribut:
    </p>
    
```c

typedef int Enemy;
typedef int* MarketStock;

class Monster {
    private:
        string name;
        int hygiene_stat,
            hunger_stat,
            health_stat,
            foodStock;
        const int damage = 20;
        int bath_isNotReady;
        Enemy enemy;
        MarketStock marketStock;
        

        pthread_t tid[6];
        
        // fungsi untuk threads
        static void* display(void*);		// dijalankan oleh thread, untuk mengatur tampilan pada stdout
        static void* regenerasi(void*);		// dijalankan oleh thread, untuk regenerasi health_stat monster
        static void* bathCoolDown(void*);	// dijalankna oleh thread, untuk mengatur cooldown bath
        static void* kelaparan(void*);		// dijalankan oleh thread, untuk mengupdate hunger_stat
        static void* hygieneDecrease(void*);	// dijalankan oleh thread, untuk mengupdate hygiene_stat
        static void* listenKeypress(void*);	// dijalankan oleh thread, untuk listen keypress dari stdin
        

        

    public:
        Monster(string nama);
        ~Monster();
        void play();
        // fungsi display
        void standby();
        void battle();
        void shop();


        void eat();
        void bath();
        void bathCooldown();

        void attack();
        void buy();

        // setter getter
        void addHealth(int);
        int getHealth();
        void addHunger(int);
        int getHunger();
        void addHygiene(int);
        int getHygiene();

        int status;
        bool isLiving;
        bool isRunning;
        string msg;
};

```

  </li>
    <li>
    <p align="justify">
	    Pada main untuk game monster, instansiasi object monster kemudian panggil method play. Pada method play, semua thread di-create dan menunggu terminasi.
    </p>
    
```c

int main(){
    char name[20];
    printf("Name > ");
    scanf("%s", name);
    Monster *monster = new Monster(name);
    monster->play();
    delete monster;
    return 0;
}

```

  </li>
  
  <li>
    <p align="justify">
	    Membuat program store (store.cpp) yang terhubung dengan game menggunakan shared memory.
    </p>
    
```c

int main(){
    key_t key = ftok("food store", 65);
    int market = shmget(key, 8, 0666 | IPC_CREAT);
    marketStock = (int*) shmat(market, (void*)0, 0);
    isRunning = true;
    pthread_t tid[2];
    
    pthread_create(&tid[0], NULL, display, NULL);
    pthread_create(&tid[1], NULL, listenKeypress, NULL);

    while(isRunning);

    pthread_cancel(tid[0]);
    pthread_cancel(tid[1]);

    shmdt(marketStock);
    shmctl(market, IPC_RMID, NULL);
    return 0;
}

```

  </li>
</ol>
