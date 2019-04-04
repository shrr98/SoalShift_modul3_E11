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

<h3>Nomor 4</h3>
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
