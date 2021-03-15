#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 10
typedef int ItemType;

typedef struct
{
  ItemType item[MAX];
  int count;
} Stack;

void InisialisasiStack(Stack *s)
{
  s->count = 0;
}

int StackKosong(Stack *s)
{
  return s->count == 0;
}

int StackPenuh(Stack *s)
{
  return s->count == MAX;
}

void Push(Stack *s, ItemType x)
{
  if (StackPenuh(s))
    printf("Stack penuh! Data tidak dapat masuk!\n");

  else
  {
    s->item[s->count] = x;
    s->count++;
  }
}

ItemType Pop(Stack *s)
{
  ItemType temp = -1;
  if (StackKosong(s))
    printf("Stack masih kosong!\n");

  else
  {
    s->count--;
    temp = s->item[s->count];
  }
  return temp;
}

////////////////////////////////////////////

typedef struct
{
  ItemType item[MAX];
  int front;
  int rear;
  int count;
} Queue;

int QueuePenuh(Queue *q)
{
  return (q->count == MAX);
}

int QueueKosong(Queue *q)
{
  return (q->count == 0);
}

void InisialisasiQueue(Queue *q)
{
  q->front = q->rear = q->count = 0;
}

void Enqueue(Queue *q, ItemType x)

{
  if (QueuePenuh(q))
    printf("Stack Penuh\n");

  else
  {
    q->item[q->rear] = x;
    q->rear = (q->rear + 1) % MAX;
    q->count++;
  }
}

ItemType Dequeue(Queue *q)
{
  ItemType temp = -1;

  if (QueueKosong(q))
    printf("Queue kosong\n");

  else
  {
    temp = q->item[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;
  }

  return temp;
}

void TampilQueue(Queue *q)
{
  int i = q->front;

  while (i != q->rear)
  {
    printf("%d ", q->item[i]);
    i = (i + 1) % MAX;
  }
}

int main()
{
  Queue q;
  Stack s;
  int i, input, pilih, no_parkir = 1; //i untuk loop, input untuk menampung inputan no parkir mobil yang ingin keluar
  //pilih untuk menampung inputan pilihan menu, dan no_parkir untuk menampung no parkir, dimulai dari 1
  char lagi = 'Y'; //input untuk mengulang loop do while

  InisialisasiQueue(&q); //tinggal baca
  InisialisasiStack(&s); //tinggal baca

  do
  {
    printf("\nPilih 1 untuk memasukkan mobil, 2 untuk mengeluarkan: ");
    scanf("%d", &pilih);
    fflush(stdin);

    if (pilih == 1)
    {
      printf("\nNo parkir %d masuk parkiran :voss", no_parkir);
      Enqueue(&q, no_parkir++); //no parkir dimasukkan ke q
    }

    else if (pilih == 2)
    {
      printf("\nMasukkan nomer parkir yang mau keluar :voss >> ");
      scanf("%d", &input);

      if (q.item[q.front] == input) //jika mobil yang ingin keluar ada di depan (no parkir yang paling depan)
        printf("no parkir %d keluar, depan sendiri lagi :'''voss", Dequeue(&q)); //keluarkan dari q secara langsung

      else //jika mobil yang ingin keluar bukan di depan
      {
        printf("no parkir %d keluar :voss", input);

        while (q.item[q.front] != input) //selama mobil paling depan yang ada di q bukan sesuai inputan user
          Push(&s, Dequeue(&q)); //keluarkan dari q lalu masukkan ke s (stack)

        input = Dequeue(&q); //loop sudah selesai, saat ini mobil paling depan di q sesuai inputan user
        //sekarang keluarkan mobil tsb lalu masukkan ke variabel input (hanya sebagai penampung agar mobil bisa hilang dari q)

        while (!StackKosong(&s)) //selama s tidak kosong (stack dikosongin)
        {
          q.item[(q.front - 1) % MAX] = Pop(&s); //pop dari s lalu masukkan kembali ke q secara manual lewat pengaksesan array
          q.front = (q.front - 1) % MAX; //front dikurangi karena maju ke depan
          q.count++; //karena q bertambah, tambah count (count artinya jumlah isi q)
        }
      }
    }

    else //jika inputan menu salah
      printf("\nsalah");

    printf("\n\nIsi parkir:\n");

    printf("Keluar <---\t");
    TampilQueue(&q); //print q
    printf("\t<--- Masuk");

    fflush(stdin);
    printf("\n\nlagi??? (Ya atau Tidak) ");
    scanf("%c", &lagi);
    fflush(stdin);
  } while (lagi == 'Y' || lagi == 'y'); //jika inputan user y atau Y maka akan mengulang

  return 0;
}
