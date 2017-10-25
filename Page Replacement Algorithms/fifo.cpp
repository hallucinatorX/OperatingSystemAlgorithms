#include<bits/stdc++.h>

using namespace std;

int currentSize=0;
int inMemeory[100],pageFaults = 0;
struct QNode
{
    int key;
    struct QNode *next;
};

struct Queue
{
    struct QNode *front, *rear;
};


struct QNode* newNode(int k)
{
    struct QNode *temp = new (QNode);
    temp->key = k;
    temp->next = NULL;

    currentSize++;
    return temp;
}

struct Queue *createQueue()
{
    struct Queue *q = new (Queue);
    q->front = q->rear = NULL;
    return q;
}


void enQueue(struct Queue *q, int k)
{

    struct QNode *temp = newNode(k);

    if (q->rear == NULL)
    {
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}

struct QNode *deQueue(struct Queue *q)
{

    if (q->front == NULL)
        return NULL;

    struct QNode *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    currentSize--;
    return temp;


}
void printCurrentFrame(struct Queue *q)
{
    struct QNode *temp = q->front;
    while(temp!=NULL)
    {
        cout<<temp->key<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

bool processSearch(struct Queue *q, int k)
{
    struct QNode *temp = q->front;
    while(temp!=NULL)
    {
        if(temp->key==k)
            return true;
        temp = temp->next;
    }
    return false;


}
bool isExists(int inMemeory[], int k)
{
    for(int i=0; i<sizeof(inMemeory)/sizeof(int); i++)
    {
        if(inMemeory[i]==k)
            return true;
    }
    return false;
}
int main()
{
    int processKey, frameSize,n;

    struct Queue *mem = createQueue();
    struct Queue *frame = createQueue();
    cout<<"Enter number of pages: ";
    cin>>n;
    cout<<"Enter frame size: ";
    cin>>frameSize;
    cout<<"Enter Process Key: "  ;
    for(int i=0; i<n; i++)
    {

        cin>>inMemeory[i];
    }


    for(int i=0; i<n; i++)
    {
        processKey= inMemeory[i];

        cout<<"For Page: "<<processKey<<endl;
        if(processSearch(frame,processKey))
        {
            cout<<"\tAlready in page frame, use it."<<endl;
        }
        else
        {
            pageFaults++;
            cout<<"\tPage Fault occurred "<<endl;
            if(currentSize<frameSize)
            {
                enQueue(frame, processKey);
            }
            else
            {
                deQueue(frame);
                enQueue(frame, processKey);

            }

        }
        cout<< "\tIn Frame: ";
        printCurrentFrame(frame);

    }
    //cout<<endl<<"Total Page Fault: "<<pageFaults<<endl;



    return 0;
}
